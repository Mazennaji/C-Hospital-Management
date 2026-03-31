<div align="center">

# 🏥 C Hospital Management System

[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Console-lightgrey?style=for-the-badge&logo=windows-terminal)](https://github.com)
[![IDE](https://img.shields.io/badge/IDE-CLion-black?style=for-the-badge&logo=clion)](https://www.jetbrains.com/clion/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

**A fully console-based Hospital Management System built in C.**  
Manage patients, doctors, and appointments with persistent file storage, a clean multi-file architecture, and modular design — all from the terminal.

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Data Storage](#-data-storage)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Technical Highlights](#-technical-highlights)
- [Contributing](#-contributing)

---

## 🔍 Overview

This project is a practical demonstration of core C programming concepts applied to a real-world domain. It uses **structs**, **arrays**, **file I/O**, and **modular function design** to build a working system that persists data across sessions using binary `.dat` files.

Ideal for students and developers learning:
- Multi-file C project organization
- Struct-based data modeling
- File handling with `fread` / `fwrite`
- Menu-driven console application design

---

## ✨ Features

### 👤 Patient Management
| Action | Description |
|---|---|
| ➕ Add Patient | Register a new patient with full details |
| 📋 View All Patients | Display a list of all registered patients |
| 🔍 Search by ID | Quickly look up a patient by their unique ID |
| ✏️ Edit Patient | Update an existing patient's information |
| 🗑️ Delete Patient | Remove a patient record from the system |

### 🩺 Doctor Management
| Action | Description |
|---|---|
| ➕ Add Doctor | Register a new doctor with specialty and contact info |
| 📋 View Doctors | List all available doctors |

### 📅 Appointment Management
| Action | Description |
|---|---|
| 📌 Book Appointment | Schedule an appointment linking a patient and doctor |
| 📋 View Appointments | Display all scheduled appointments |

---

## 📁 Project Structure

```
C-Hospital-Management/
│
├── main.c                  # Entry point & main menu
│
├── patients.c              # Patient logic implementation
├── patients.h              # Patient struct & function declarations
│
├── doctors.c               # Doctor logic implementation
├── doctors.h               # Doctor struct & function declarations
│
├── appointments.c          # Appointment logic implementation
├── appointments.h          # Appointment struct & function declarations
│
├── patients.dat            # Persistent patient records (binary)
├── doctors.dat             # Persistent doctor records (binary)
└── appointments.dat        # Persistent appointment records (binary)
```

---

## 💾 Data Storage

All records are persisted in **binary `.dat` files** using C's `fread`/`fwrite` for efficient struct serialization. Data survives between program runs automatically.

```
patients.dat       →  Stores Patient structs
doctors.dat        →  Stores Doctor structs
appointments.dat   →  Stores Appointment structs
```

> ⚠️ Do not manually edit `.dat` files — they are binary, not plain text.

---

## 🚀 Getting Started

### Prerequisites

- A **C compiler**: [GCC](https://gcc.gnu.org/) or [CLion](https://www.jetbrains.com/clion/)
- Git (to clone the repository)

### Installation

**1. Clone the repository**
```bash
git clone https://github.com/yourusername/C-Hospital-Management.git
cd C-Hospital-Management
```

**2a. Compile and run with GCC**
```bash
gcc main.c patients.c doctors.c appointments.c -o hospital
./hospital
```

**2b. Or open in CLion**
- Open the project folder in CLion
- CLion auto-detects the CMake/multi-file structure
- Click **Run** ▶️

---

## 🖥️ Usage

When launched, the application presents an interactive menu:

```
╔══════════════════════════════╗
║   🏥  Hospital Management    ║
╠══════════════════════════════╣
║  1. Add Patient              ║
║  2. View All Patients        ║
║  3. Search Patient by ID     ║
║  4. Edit Patient             ║
║  5. Delete Patient           ║
╠══════════════════════════════╣
║  6. Add Doctor               ║
║  7. View Doctors             ║
╠══════════════════════════════╣
║  8. Book Appointment         ║
║  9. View Appointments        ║
╠══════════════════════════════╣
║  0. Exit                     ║
╚══════════════════════════════╝
Enter your choice:
```

Navigate by entering the corresponding number and pressing `Enter`.

---

## 🛠️ Technical Highlights

- **Modular Architecture** — Logic is split across `.c`/`.h` file pairs for clean separation of concerns
- **Struct-Based Modeling** — `Patient`, `Doctor`, and `Appointment` structs model real-world entities
- **Binary File I/O** — Uses `fread`/`fwrite` for fast, compact persistent storage
- **Array-Based In-Memory Storage** — Records are loaded into arrays for fast runtime access
- **Pure C (C99/C11)** — No external libraries required; compiles anywhere GCC is available

---

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/your-feature`
3. Commit your changes: `git commit -m "Add your feature"`
4. Push to the branch: `git push origin feature/your-feature`
5. Open a Pull Request

---

<div align="center">

Made with ❤️ in C &nbsp;|&nbsp; Console-based &nbsp;|&nbsp; No dependencies

</div>
