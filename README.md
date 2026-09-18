# Sterling Heritage Institute | Student Management System

A full-stack Student Management System built around a custom **C++ file-based data management engine**, a **Python Flask integration layer**, and a **HTML + Tailwind CSS web portal**.

The project explores how student records can be represented, searched, updated, authenticated, and persisted without relying on a conventional database system.

> **Current Version:** C++ + flat-file persistence  
> **Future Direction:** SQL-backed database architecture

---

## 🏛️ Architecture

```text
┌─────────────────────────────┐
│       Web Interface         │
│      HTML + Tailwind        │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│       Flask Backend         │
│   Reads • Parses • Serves   │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│    C++ Data Management      │
│ Search • Auth • Updates     │
│ Calculations • File I/O     │
└──────────────┬──────────────┘
               │
               ▼
        Persistent Files
   theory_marks.txt
   practical_marks.txt

## C++ Core

The C++ programs manage the underlying academic records using:

struct-based student records
Arrays for in-memory storage
Linear-search record retrieval
Student authentication
Subject-specific teacher access
Targeted mark updates
Total and percentage calculations
ifstream / ofstream for persistent storage
## Flask Integration

The Flask layer acts as the bridge between the stored records and the browser.

It:

Reads tab-separated data files
Parses records into Python structures
Exposes data through web endpoints
Supplies JSON-compatible data to the frontend
Web Interface

The frontend provides:

Student dashboard
Academic performance display
Teacher/admin interfaces
Dynamic data loading
Responsive styling
Client-side navigation
📁 Project Structure
Student-Management-System/
│
├── theory.cpp
├── practical.cpp
│
├── theory_marks.txt
├── practical_marks.txt
│
├── app.py
├── index.html
│
└── README.md
Academic Records

The system maintains separate datasets for theory and practical marks:

theory.cpp → theory_marks.txt
practical.cpp → practical_marks.txt

Each student record contains:

Name
Section
Roll number
Password
Subject marks
Total
Percentage

Supported subjects:

AI • OOPM • IPS • DS • TC

The current system supports up to 100 students, divided between Section A and Section B.

## 🔐 Authentication & Access Control

The system provides three main access levels:

| Role | Access |
|---|---|
| Student |	View personal academic records |
| Teacher	| Update marks for their assigned subject |
| Admin | Access administrative functions |

Teachers use subject-specific credentials, while the admin portal uses a master credential with a three-attempt login limit.

Security Note

This project demonstrates authentication and access-control logic for learning purposes.

Credentials are currently hardcoded in the source code and are not securely hashed. The security-alert email functionality is also simulated rather than connected to a real email service.

It should therefore not be considered production-grade authentication.

💾 Data Persistence

The current version uses tab-separated text files instead of a dedicated database server.

Program Start
     │
     ▼
Read Text File
     │
     ▼
Student Records in Memory
     │
     ├── Search
     ├── Authenticate
     ├── View
     └── Update
     │
     ▼
Write Updated Records
     │
     ▼
Persistent Text File

This provides persistent storage without requiring an external database.

## ✨ Features
Student login
Subject-specific teacher access
Admin portal
Student record search
Theory/practical record separation
Subject mark updates
Automatic total and percentage calculation
Persistent file-based storage
Flask web interface
Responsive Tailwind CSS frontend
🛠️ Technology Stack
| Layer | Technology |
|---|---|
| Core / Data Management | C++ |
| Storage | Tab-separated text files |
| Web Backend | Python + Flask |
| Frontend | HTML + Tailwind CSS |
| Compiler | g++ |


## 🚀 Running the Project
 C++ Engine

 Compile the theory and practical programs using:

 g++ theory.cpp -o theory
 g++ practical.cpp -o practical

 Run the required executable:

./theory

or

./practical
## Web Portal

Install Flask:

pip install flask

Then start the application:

python app.py

Open the local address provided by Flask in your browser.

## 📌 Project Status

This is a learning-focused implementation of a student academic record management system.

The current version uses custom C++ data structures and file-based persistence rather than a dedicated SQL database.

Future Direction

The next major upgrade is to replace the flat-file storage layer with a relational database such as MySQL or PostgreSQL, while retaining the core application concept.

This would move the project from custom flat-file data management toward a conventional database-backed architecture.   