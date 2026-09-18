# Sterling Heritage Institute | Academic Records & DBMS Portal

A high-performance, dual-layer Student Management System featuring a custom **C++ Database Engine** with file-based persistence, paired with a modern **Python Flask & Tailwind CSS Web Portal**.

---

## 🏛️ System Architecture

This project bridges low-level systems programming with a clean, institutional web interface:
1. **The Core Database Engine (C++):** Handles student structs, secure role-based access control, targeted record updates, and persistent file input/output (`theory_marks.txt` and `practical_marks.txt`).
2. **The Integration Layer (Python Flask):** Acts as a bridge, parsing tab-separated flat files into JSON structures to serve dynamic endpoints.
3. **The User Interface (HTML / Tailwind CSS):** A responsive Single Page Application (SPA) designed with a professional private-institute aesthetic, featuring smooth client-side routing, interactive dashboards, and a live data-override portal.

---

## 🛠️ Features & Modules

* **Custom C++ Backend:** Built completely from scratch using object-oriented structures, linear search algorithms, and structured file streams (`ifstream`/`ofstream`).
* **Multi-Subject Tracking:** Manages scores across 5 core engineering subjects:
  * Artificial Intelligence (AI)
  * Object-Oriented Programming and Methodology (OOPM)
  * Introduction to Probability and Statistics (IPS)
  * Data Structures (DS)
  * Theory of Computation (TC)
* **Separation of Records:** Independent tracking systems for **Theory Marks** (out of 100) and **Practical & Internal Marks** (out of 50).
* **Role-Based Access Control (RBAC):**
  * **Students:** Secure credential login (`stdA1`, etc.) yielding a formatted marksheet with automated percentage and division calculation.
  * **Teachers:** Subject-specific administrative overrides (`admin_ai`, `admin_oopm`, etc.) with mid-session exit handlers (`-1`) to prevent data loss.
  * **Administrators / Devs:** Master database spreadsheet view protected by a 3-strike security lockout protocol (`dev_admin`).

---

## 🚀 Getting Started & Local Setup

### 1. Prerequisites
* A C++ compiler (`g++`)
* Python 3.x with Flask installed (`pip install flask`)

### 2. Running the C++ Engine (Optional CLI Mode)
If you wish to interact with the raw database engines directly via terminal:
```bash
g++ theory.cpp -o theory
./theory
```

### 3. Launching the Full-Stack Web Portal
1. Ensure your C++ engine has generated the local `.txt` database files in the root directory.
2. Start the Flask server:
   ```bash
   python app.py
Open your browser and navigate to:
[http://127.0.0.1:5000](http://127.0.0.1:5000)
🔒 Security & Git Configuration
To maintain a clean repository, compiled binaries (*.exe) and local production flat-files (*.txt) are strictly excluded via .gitignore.

*.exe
*.txt
*.tmp
__pycache__/   