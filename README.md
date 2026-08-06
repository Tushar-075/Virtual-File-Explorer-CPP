# 📁 Virtual File Explorer (C++)

A terminal-based **Virtual File Explorer** built using **Modern C++17** that simulates a hierarchical file system completely in memory. The project demonstrates Object-Oriented Programming (OOP), General Trees, Recursion, Dynamic Memory Management, and File Serialization without interacting with the operating system's real file system.

---

## 🚀 Features

- 📂 Create folders (`mkdir`)
- 📄 Create files (`touch`)
- ✍️ Write multi-line text to files (`write`)
- 📖 Read file contents (`read`)
- ➕ Append text to existing files (`append`)
- 📋 List files and folders (`ls`)
- 📁 Navigate directories (`cd`, `cd ..`, `cd /`)
- 🌳 Display the complete directory tree (`tree`)
- 📍 Display the current working directory (`pwd`)
- 🗑️ Delete files and folders recursively (`delete`)
- 💾 Automatic save/load using serialization
- 🔄 Persistent virtual filesystem across program executions

---

## 🛠️ Technologies Used

- C++17
- Standard Template Library (STL)
- Object-Oriented Programming
- File Handling
- Recursion

---

## 📚 Data Structures & Algorithms

This project demonstrates several important DSA concepts:

- 🌲 General Tree
- 🔁 Depth First Search (DFS)
- 🔄 Recursive Tree Traversal
- 🧠 Dynamic Memory Allocation
- 👨‍👦 Parent Pointer Navigation
- 💾 Recursive Serialization & Deserialization

---

## 📂 Project Structure

```
Virtual-File-Explorer-CPP/
│
├── main.cpp
├── FileSystem.cpp
├── FileSystem.h
├── Node.cpp
├── Node.h
├── README.md
└── .gitignore
```

---

## ⚙️ Supported Commands

| Command          | Description                       |
| ---------------- | --------------------------------- |
| `help`           | Show all commands                 |
| `mkdir <folder>` | Create a folder                   |
| `touch <file>`   | Create a file                     |
| `write <file>`   | Write text to a file              |
| `read <file>`    | Display file contents             |
| `append <file>`  | Append text to a file             |
| `ls`             | List current directory            |
| `cd <folder>`    | Enter a folder                    |
| `cd ..`          | Go to parent directory            |
| `cd /`           | Go to root directory              |
| `pwd`            | Print current path                |
| `tree`           | Display complete folder hierarchy |
| `delete <name>`  | Delete a file or folder           |
| `exit`           | Save and exit                     |

---

## 💻 Example Session

```text
C:\> mkdir Projects

C:\> cd Projects

C:\Projects> touch notes.txt

C:\Projects> write notes.txt

Enter file contents.
Type :wq on a new line to save.

Hello World
This is my first virtual file.
:wq

File saved.

C:\Projects> read notes.txt

-------------------------
Hello World
This is my first virtual file.
-------------------------

C:\Projects> tree

C:\
`-- Projects/
    `-- notes.txt
```

---

## 🏗️ How It Works

The project simulates a virtual filesystem using a **General Tree**.

- Each folder or file is represented as a **Node**.
- Folders can have unlimited child nodes.
- Every node maintains a pointer to its parent.
- Recursive algorithms are used for:
  - Tree traversal
  - Printing the directory hierarchy
  - Recursive deletion
  - Saving the filesystem
  - Loading the filesystem

The entire filesystem is stored in memory during execution and serialized to a file, allowing the virtual filesystem to persist between sessions.

---

## ▶️ Build & Run

Compile using:

```bash
g++ -std=c++17 main.cpp Node.cpp FileSystem.cpp -o VirtualFileExplorer
```

Run:

```bash
./VirtualFileExplorer
```

On Windows:

```powershell
VirtualFileExplorer.exe
```

---

## 🎯 Learning Outcomes

This project strengthened my understanding of:

- Object-Oriented Programming
- Trees and Hierarchical Data Structures
- Recursive Algorithms
- Dynamic Memory Management
- File Serialization
- Command-Line Interface Design
- Modular C++ Project Structure

---

## 🚀 Future Enhancements

- 🔍 Find files using DFS
- 📋 Copy files and folders
- 🚚 Move files and folders
- ✏️ Rename files and folders
- 📊 File metadata (timestamps, size)
- 🔎 Search text within files
- 🗂️ Multiple virtual drives

---

## 👨‍💻 Author

**Tushar Singh**

GitHub: https://github.com/Tushar-075

LinkedIn: https://www.linkedin.com/in/tushar075

---

⭐ If you found this project interesting, consider giving it a star!
