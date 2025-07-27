/**
 * @file      main.cpp
 * @author    Your Name (your-email@example.com)
 * @brief     your file's description
 * @version   0.1
 * @date      07-07-2025
 * @copyright 2025, your company / association / school
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <unordered_map>

struct mem_book_Hasher{
    std::size_t operator()(const std::string& isbn) const {
        std::size_t hash = 0;
        for (char c : isbn) {
            hash = hash * 31 + c; // Simple hash function
        }
        return hash;
    }
};

struct mem_book_Equal {
    bool operator()(const std::string& isbn1, const std::string& isbn2) const {
        return isbn1 == isbn2;
    }
};

class Book {
    public:
    std::string m_title;
    std::string m_author;
    int m_publicationYear;
    bool m_isAvailable;
    std::string m_isbn;

    Book(const std::string& title, const std::string& author, const std::string& isbn, int publicationYear) {
        m_title = title;
        m_author = author;
        m_isbn = isbn;
        m_publicationYear = publicationYear;
        m_isAvailable = true; // By default, a book is available when created
    }
    bool operator==(const Book& other) const {
        return m_isbn == other.m_isbn; // Compare by ISBN
    }
    void printDetails() {
        std::cout << "Title: " << m_title << ", Author: " << m_author 
                  << ", ISBN: " << m_isbn << ", Year: " << m_publicationYear 
                  << ", Available: " << (m_isAvailable ? "Yes" : "No") << std::endl;
    }
};

class Member {
    public:
    std::string m_name;
    std::string m_memberId;
    std::vector<std::string> m_borrowedBooks;

    Member(const std::string& name, const std::string& memberId) {
        m_name = name;
        m_memberId = memberId;
    }
    void printName() {
        std::cout << "Member Name: " << m_name << std::endl;
    }
    void borrowBook(const Book& book) {
        m_borrowedBooks.push_back(book.m_isbn); // Store the book's ISBN
        std::cout << m_name << " borrowed the book: " << book.m_title << std::endl;
    }
    void returnBook(const Book& book) {
        auto it = std::find(m_borrowedBooks.begin(), m_borrowedBooks.end(), book.m_isbn);
        if (it != m_borrowedBooks.end()) {
            m_borrowedBooks.erase(it);
            std::cout << m_name << " returned the book: " << book.m_title << std::endl;
        } else {
            // Optional: Handle the case where the member tries to return a book they don't have.
            std::cout << "Error: " << m_name << " did not borrow this book." << std::endl;
        }
    }
};

class Library {
    // TO-DO change both to std::map for faster lookups
    std::unordered_map<std::string, Member, mem_book_Hasher, mem_book_Equal> m_members;
    std::unordered_map<std::string, Book, mem_book_Hasher, mem_book_Equal> m_books;
    public:
    Library() {}
    void addMember(const Member& member) {
        m_members.insert({member.m_memberId, member});
    }
    void addBook(const Book& book) {
        m_books.insert({book.m_isbn, book});
    }
    bool searchBook(std::string title) {
        for(auto& book : m_books) {
            return (book.second.m_title == title);
        }
    }
    Member* findMemberById(const std::string& memberId) {
       auto it = m_members.find(memberId); // Find the member
        if (it != m_members.end()) {
            return &it->second; // Return the address of the found member
        }
        return nullptr; // Return null if not found
    }
    Book* findBookByIsbn(const std::string& isbn) {
        auto it = m_books.find(isbn); // Find the book
        if (it != m_books.end()) {
            return &it->second; // Return the address of the found book
        }
        return nullptr; // Return null if not found
    }
    void returnBook(Member& member, Book& book) {
        book.m_isAvailable = true; // Mark the book as available
        member.returnBook(book);
    }
    void borrowBook(Member& member, Book& book) {
        if(book.m_isAvailable == false) {
            std::cout << "Book is not available for borrowing." << std::endl;
            return;
        }

        book.m_isAvailable = false; // Mark the book as borrowed
        member.borrowBook(book);
    }
    void printMembers() {
        for(auto& it : m_members) {
            it.second.printName();
        }
    }
};

void printMenu() {
    std::cout << "\n--- Library Management System ---\n";
    std::cout << "1. Add New Book\n";
    std::cout << "2. Add New Member\n";
    std::cout << "3. Borrow a Book\n";
    std::cout << "4. Return a Book\n";
    /* std::cout << "5. List All Books\n";
    std::cout << "6. List All Members\n"; */
    std::cout << "5. Exit\n";
    std::cout << "---------------------------------\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Library library;

    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;

        // Handle non-integer input
        if (std::cin.fail()) {
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            choice = 0; // Set to a default invalid choice
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the rest of the line

        switch (choice) {
            case 1: { // Add New Book
                std::string title, author, isbn;
                int year;
                
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter publication year: ";
                std::cin >> year;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                library.addBook(Book(title, author, isbn, year));
                std::cout << "Book added successfully!\n";
                break;
            }
            case 2: {
                std::string name, memberId;
                std::cout << "Enter member name: ";
                std::getline(std::cin, name);
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);

                library.addMember(Member(name, memberId));
                std::cout << "Member added successfully!\n";
                break;
            }
            case 3: {
                std::string memberId, isbn;
                std::cout << "Enter your member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter ISBN of the book to borrow: ";
                std::getline(std::cin, isbn);

                Member* member = library.findMemberById(memberId);
                Book* book = library.findBookByIsbn(isbn);

                if (member && book) {
                    library.borrowBook(*member, *book);
                } else {
                    std::cout << "Error: Invalid Member ID or Book ISBN.\n";
                }
                break;
            }
            case 4: { // Return a Book
                std::string memberId, isbn;
                std::cout << "Enter your member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter ISBN of the book to return: ";
                std::getline(std::cin, isbn);

                Member* member = library.findMemberById(memberId);
                Book* book = library.findBookByIsbn(isbn);

                if (member && book) {
                    library.returnBook(*member, *book);
                    // Success message moved inside the Library::returnBook method for better logic.
                } else {
                    std::cout << "Error: Invalid Member ID or Book ISBN.\n";
                }
                break;
            }case 5: // Exit
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
