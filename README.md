# Library-Management-System
## Project Outline: Library Management System

### Core Classes

1. **Book**
   - Attributes: title, author, ISBN, status (available/borrowed), etc.
   - Methods: display info, update status, etc.

2. **Member**
   - Attributes: name, member ID, list of borrowed books, etc.
   - Methods: borrow book, return book, display info, etc.

3. **Library**
   - Attributes: collection of books, list of members.
   - Methods: add/remove books, register/remove members, search books, manage borrowing/returning.

---

### Basic System Goals

- Add new books to the library.
- Register new members.
- Allow members to borrow and return books.
- Track which books are available or borrowed.
- Display lists of all books and all members.
- Search for books by title, author, or ISBN.

---

### Additional (Stretch) Goals

- Implement due dates and overdue book tracking.
- Add fines for overdue books.
- Allow members to reserve books that are currently borrowed.
- Support for multiple copies of the same book.
- Save and load library data from a file (persistence).
- Implement a simple command-line or graphical user interface.