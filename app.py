import math
import os
import re
import threading
from functools import wraps
from flask import Flask, jsonify, request, send_from_directory, session

# --------------------------------------------------------------------------- #
# Configuration
# --------------------------------------------------------------------------- #
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
FILES = {
    "theory": os.path.join(BASE_DIR, "theory_marks.txt"),
    "practical": os.path.join(BASE_DIR, "practical_marks.txt"),
}

INSTITUTE = "Sterling Heritage Institute"
SUBJECTS = ["AI", "OOPM", "IPS", "DS", "TC"]
SUBJECT_NAMES = {
    "AI": "Artificial Intelligence",
    "OOPM": "Object Oriented Programming and Methodology",
    "IPS": "Introduction to Probability and Statistics",
    "DS": "Data Structures",
    "TC": "Technical Communication",
}

MAX_MARKS = {"theory": 100, "practical": 50}
MAX_MARKS["combined"] = 150
KINDS = ("theory", "practical", "combined")
PASS_PERCENT = 40

LOCK = threading.RLock()

app = Flask(__name__, static_folder=None)
app.secret_key = "sterling-heritage-dev-secret"

# --------------------------------------------------------------------------- #
# File Parsing Logic
# --------------------------------------------------------------------------- #
def _norm(text):
    return re.sub(r"[\s._\-]+", "", text.strip().lower())

ALIASES = {
    "roll": "roll", "rollno": "roll", "id": "roll",
    "name": "name", "sec": "sec", "section": "sec",
    "total": "total", "percent": "percent", "pass": "pass"
}
for _code in SUBJECTS:
    ALIASES[_code.lower()] = _code

def _num(text):
    try:
        value = float(str(text).strip())
        return int(value) if value.is_integer() else round(value, 2)
    except (TypeError, ValueError):
        return None

def _clean(value):
    value = round(value, 2)
    return int(value) if float(value).is_integer() else value

def fmt_mark(value):
    return str(_clean(value))

def _read_table(path):
    if not os.path.exists(path):
        return None, [], {}
    with open(path, "r", encoding="utf-8-sig", newline="") as fh:
        lines = [ln.rstrip("\r\n") for ln in fh if ln.strip()]
    if not lines:
        return None, [], {}

    cells = [ln.split("\t") for ln in lines]
    first = [_norm(c) for c in cells[0]]

    if any(c in ALIASES for c in first):
        header, body, colmap = cells[0], cells[1:], {}
        for idx, c in enumerate(first):
            if c in ALIASES and ALIASES[c] not in colmap:
                colmap[ALIASES[c]] = idx
    else:
        header, body = None, cells
        fields = ["roll", "sec"] + SUBJECTS
        colmap = {field: idx for idx, field in enumerate(fields)}
    return header, body, colmap

def _cell(row, colmap, key):
    idx = colmap.get(key)
    return row[idx].strip() if idx is not None and idx < len(row) else ""

def parse_marks_file(path):
    _, body, colmap = _read_table(path)
    records = {}
    for row in body:
        roll = _cell(row, colmap, "roll")
        if not roll:
            continue
        records[roll] = {
            "roll": roll,
            "name": _cell(row, colmap, "name"),
            "sec": _cell(row, colmap, "sec"),
            "marks": {s: _num(_cell(row, colmap, s)) for s in SUBJECTS},
        }
    return records

def load_all():
    with LOCK:
        theory = parse_marks_file(FILES["theory"])
        practical = parse_marks_file(FILES["practical"])
    people = {}
    for source in (theory, practical):
        for roll, rec in source.items():
            person = people.setdefault(roll, {"roll": roll, "name": "", "sec": ""})
            person["name"] = person["name"] or rec["name"]
            person["sec"] = person["sec"] or rec["sec"]
    for roll, person in people.items():
        person["name"] = person["name"] or f"Student {roll}"
        person["sec"] = person["sec"] or "-"
    
    theory_marks = {r: v["marks"] for r, v in theory.items()}
    practical_marks = {r: v["marks"] for r, v in practical.items()}
    return people, theory_marks, practical_marks

def marks_for(kind, roll, theory, practical):
    if kind == "theory":
        return theory.get(roll, {})
    if kind == "practical":
        return practical.get(roll, {})
    return {}

# --------------------------------------------------------------------------- #
# Math Engine
# --------------------------------------------------------------------------- #
def division(percent, passed):
    if not passed: return "Not qualified"
    if percent >= 75: return "Distinction"
    if percent >= 60: return "First Class"
    if percent >= 50: return "Second Class"
    return "Pass Class"

def evaluate(marks, kind):
    per_max = MAX_MARKS[kind]
    values = {s: marks.get(s) for s in SUBJECTS}
    total = sum(v or 0 for v in values.values())
    max_total = per_max * len(SUBJECTS)
    percent = round(total / max_total * 100, 2) if max_total else 0
    pass_mark = per_max * PASS_PERCENT / 100
    failed = [s for s in SUBJECTS if (values[s] or 0) < pass_mark]
    passed = not failed
    return {
        "marks": values, "total": _clean(total), "maxTotal": max_total,
        "maxPerSubject": per_max, "passMark": _clean(pass_mark),
        "percent": _clean(percent), "passed": passed, "division": division(percent, passed),
    }

def _sync_derived(row, colmap, kind):
    values = {}
    for s in SUBJECTS:
        idx = colmap.get(s)
        values[s] = _num(row[idx]) if idx is not None and idx < len(row) else None
    result = evaluate(values, kind)

    def put(key, text):
        idx = colmap.get(key)
        if idx is not None:
            while len(row) <= idx: row.append("")
            row[idx] = text

    put("total", fmt_mark(result["total"]))
    put("percent", fmt_mark(result["percent"]))

def update_mark(kind, roll, subject, value):
    path = FILES[kind]
    with LOCK:
        header, body, colmap = _read_table(path)
        col, roll_col = colmap.get(subject), colmap.get("roll")
        if col is None or roll_col is None:
            raise ValueError(f"Column for {subject} missing in {os.path.basename(path)}.")
        for row in body:
            if len(row) > roll_col and row[roll_col].strip() == roll:
                while len(row) <= col: row.append("")
                previous = _num(row[col])
                row[col] = fmt_mark(value)
                _sync_derived(row, colmap, kind)
                break
        else:
            raise KeyError(roll)

        lines = (["\t".join(header)] if header else []) + ["\t".join(r) for r in body]
        tmp_path = path + ".tmp"
        with open(tmp_path, "w", encoding="utf-8", newline="") as fh:
            fh.write("\n".join(lines) + "\n")
        os.replace(tmp_path, path)
        return previous

# --------------------------------------------------------------------------- #
# Routing & API
# --------------------------------------------------------------------------- #
def require_role(*roles):
    def decorator(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            if "role" not in session: return jsonify(error="Session expired."), 401
            if session["role"] not in roles: return jsonify(error="Permission denied."), 403
            return fn(*args, **kwargs)
        return wrapper
    return decorator

@app.route("/")
def index(): return send_from_directory(BASE_DIR, "index.html")

@app.route("/api/me")
def api_me():
    if "role" not in session: return jsonify(authenticated=False)
    return jsonify(authenticated=True, role=session["role"], id=session["uid"], name=session["name"])

@app.route("/api/logout", methods=["POST"])
def api_logout():
    session.clear()
    return jsonify(ok=True)

@app.route("/api/login", methods=["POST"])
def api_login():
    data = request.get_json(silent=True) or {}
    role = str(data.get("role", "")).lower()
    uid = str(data.get("id", "")).strip()
    password = str(data.get("password", ""))

    user = None
    if role == "student":
        # Scans your real C++ text file to find the generated password
        _, body, colmap = _read_table(FILES["theory"])
        roll_col, pass_col = colmap.get("roll"), colmap.get("pass")
        
        if roll_col is not None and pass_col is not None:
            for row in body:
                if len(row) > max(roll_col, pass_col):
                    if row[roll_col].strip().lower() == uid.lower() and row[pass_col].strip() == password:
                        user = {"id": uid, "name": f"Student Roll: {uid}"}
                        break
                        
    elif role == "teacher":
        valid = ["admin_ai", "admin_oopm", "admin_ips", "admin_ds", "admin_tc"]
        if password in valid:
            user = {"id": uid.upper(), "name": f"Prof. {uid}"}
            
    elif role == "admin":
        if password == "dev_admin":
            user = {"id": "admin", "name": "Master Registrar"}

    if not user:
        return jsonify(error="Access Denied. Invalid ID or Password."), 401

    session.clear()
    session.update(role=role, uid=user["id"], name=user["name"])
    return jsonify(authenticated=True, role=role, id=user["id"], name=user["name"])

@app.route("/api/student/<roll>")
@require_role("student", "teacher", "admin")
def api_student(roll):
    people, theory, practical = load_all()
    if roll not in people: return jsonify(error="Student not found."), 404
    return jsonify(
        roll=roll, name=people[roll]["name"], sec=people[roll]["sec"],
        subjects=[{"code": s, "name": SUBJECT_NAMES[s]} for s in SUBJECTS],
        theory=evaluate(marks_for("theory", roll, theory, practical), "theory"),
        practical=evaluate(marks_for("practical", roll, theory, practical), "practical"),
    )

@app.route("/api/admin/all")
@require_role("admin")
def api_admin_all():
    kind = request.args.get("kind", "theory")
    people, theory, practical = load_all()
    rows = []
    for roll in sorted(people.keys(), key=lambda x: int(x) if x.isdigit() else x):
        result = evaluate(marks_for(kind, roll, theory, practical), kind)
        rows.append({
            "roll": roll, "name": people[roll]["name"], "sec": people[roll]["sec"],
            "passed": result["passed"], "marks": result["marks"],
            "total": result["total"], "percent": result["percent"],
        })
    return jsonify(kind=kind, rows=rows)

@app.route("/api/teacher/mark", methods=["GET"])
@require_role("teacher", "admin")
def api_teacher_get_mark():
    kind = str(request.args.get("kind", "theory"))
    sub = str(request.args.get("subject", ""))
    roll = str(request.args.get("roll", ""))
    
    people, theory, practical = load_all()
    if roll not in people: return jsonify(error="Student not found."), 404
    mark = marks_for(kind, roll, theory, practical).get(sub)
    return jsonify(roll=roll, name=people[roll]["name"], sec=people[roll]["sec"], mark=mark, maxMarks=MAX_MARKS.get(kind, 100))

@app.route("/api/teacher/mark", methods=["POST"])
@require_role("teacher", "admin")
def api_teacher_set_mark():
    data = request.get_json(silent=True) or {}
    try:
        val_raw = data.get("mark")
        if val_raw is None: raise ValueError("Mark cannot be empty")
        
        val = float(val_raw)
        update_mark(str(data.get("kind", "theory")), str(data.get("roll", "")), str(data.get("subject", "")), val)
        return jsonify(ok=True)
    except Exception as e:
        return jsonify(error=str(e)), 500

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)