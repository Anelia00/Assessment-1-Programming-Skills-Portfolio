#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// This book class stores information about each book
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    // This is a constructor to create a book
    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    // This displays the book information
    void display() {
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "ID: " << id << endl;
        cout << "Status: " << (borrowed ? "Borrowed" : "Available") << endl;
    }
};

// This reads books from the text file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");
    string title, author, pages, id, status;

    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt" << endl;
        return books;
    }

    // This reads each field separated by commas
    while (getline(file, title, ',')) {
        getline(file, author, ',');
        getline(file, pages, ',');
        getline(file, id, ',');
        getline(file, status);

        books.push_back(Book(title, author, stoi(pages),
                             id, status == "true"));
    }

    file.close();
    return books;
}

// This saves any changes to the text file
void saveBooks(const vector<Book>& books) {
    ofstream file("bookData.txt");

    for (const Book& book : books) {
        file << book.title << "," << book.author << ","
             << book.pages << "," << book.id << ","
             << (book.borrowed ? "true" : "false") << endl;
    }

    file.close();
}

// This finds a book using its ID
int findBook(const vector<Book>& books, string id) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "No books found. Program closing." << endl;
        return 1;
    }

    cout << "==================================" << endl;
    cout << "         Library Book Manager     " << endl;
    cout << "==================================" << endl;
    cout << "\nWelcome to the Library Book Manager!" << endl;

    int choice;

    // This keeps showing the menu until the user exits
    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. View all books" << endl;
        cout << "2. View a book by ID" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Display all books in the library
            for (Book& book : books) {
                book.display();
            }
        }
        else if (choice >= 2 && choice <= 4) {
            string id;
            cout << "Enter book ID (e.g. 001): ";
            cin >> id;

            int index = findBook(books, id);

            if (index == -1) {
                cout << "Book not found!" << endl;
            }
            else if (choice == 2) {
                books[index].display();
            }
            else if (choice == 3) {
                if (books[index].borrowed) {
                    cout << "This book is already borrowed." << endl;
                }
                else {
                    books[index].borrowed = true;
                    saveBooks(books);
                    cout << "Book borrowed successfully!" << endl;
                }
            }
            else if (choice == 4) {
                if (!books[index].borrowed) {
                    cout << "This book is already available." << endl;
                }
                else {
                    books[index].borrowed = false;
                    saveBooks(books);
                    cout << "Book returned successfully!" << endl;
                }
            }
        }
        else if (choice == 5) {
            cout << "\nThank you for using the Book Manager!" << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
