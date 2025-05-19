# autocomplete-system
# 🔍 AutoComplete System

## 📌 Overview
This is a C++ autocomplete system based on the **Trie data structure**, designed to suggest words based on user-input prefixes. The system supports different sorting methods for suggestions and includes a graphical interface using **Qt**.

## 🧠 Features
- 🔤 **Prefix search** using Trie
- ✔️ **Exact match highlighting**
- 🔡 **Alphabetical sorting (DFS)**
- 🔢 **Shortest word first (BFS)**
- 🔁 **Most frequent word suggestion**
- ➕ Add / Delete words and prefixes
- 🧠 Automatically adds searched words after 3 uses
- ❌ Input validation (e.g., invalid characters)
- 🔠 **Case-insensitive search**
- 💾 Loads from file at start, saves on exit
- 🖼️ **GUI built with Qt** for better usability

## 💻 Technologies Used
- C++
- Qt Framework (for GUI)
- Standard Template Library (STL)

## 🖥️ How to Run

### 🔧 Console Version
1. Compile all `.cpp` files using a C++ compiler (e.g., g++, Visual Studio).
2. Run the executable and follow the prompts to search/add/delete words.

### 🎨 GUI Version (Qt)
1. Open the project in Qt Creator.
2. Build the project and run.
3. Use the GUI to interact with the autocomplete system:
   - Enter a prefix
   - Choose sorting method from dropdown
   - View suggestions
   - Add/Delete words through buttons


