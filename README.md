# BankClientApp

# 🏦 Bank Client Management System (C++)

A console-based banking system written in C++.
This project allows you to:
## 🖥️ System Overview
Displaying the main dashboard and the formatted client database.
![Main Menu and Client List](./BANK%201/screenshots/overview.png)

## ⚙️ Data Operations (Update)
The system ensures data integrity by searching for clients and asking for confirmation before any modification .
![Update Operations](./BANK%201/screenshots/operations.png)


- Add new clients
- Delete clients
- Update client information
- Find clients by account number
- Save & load data from file

## 💻 Technologies Used
- C++
- File Handling (fstream)
- Vectors
- Structs

## 📂 Project Structure
- Main.cpp
- Clients.txt (Data File)

## 🚀 How to Run

### 🪟 On Windows (CMD / PowerShell)
Compile:
g++ main.cpp -o bank.exe
Run:
bank.exe

### 🍎 On macOS / 🐧 Linux
Compile:
g++ main.cpp -o bank
Run:
./bank
