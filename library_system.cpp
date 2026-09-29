#include <iostream>
#include <string>
#include <vector>
#include <limits> 
using namespace std;

// general purpose helper function to validate inputs
int getValidInt(string prompt) {
    int value;

    //loop indefinitely until user puts valid input
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a whole number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return value;
}

struct Book {
    int bookID;
    string title;
    string author;
    int publicationYear;
    int copiesAvailable;
};

vector<Book> library;

// first version of addBook that takes individual params and adds to the library vector
void addBook(int bookID, string title, string author, int publicationYear, int copiesAvailable) {
    // Checking for a duplicate ID by looping over the library vector
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            cout << "Error: A book with ID " << bookID << " already exists." << endl;
            return;
        }
    }

    Book newBook;
    newBook.bookID = bookID;
    newBook.title = title;
    newBook.author = author;
    newBook.publicationYear = publicationYear;
    newBook.copiesAvailable = copiesAvailable;

    library.push_back(newBook);
    cout << "Book added successfully." << endl;
}

// overload of addBook that takes a Book instance instead of individual params
void addBook(Book newBook) {
    addBook(newBook.bookID, newBook.title, newBook.author, newBook.publicationYear, newBook.copiesAvailable);
}

// displayBooks overload function that gives you three choices, all books, by ID, or by author
void displayBooks() {
    // handling no books issue
    if (library.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    
    // first function that accepts no inputs and displays all details of all books by
    // indexing through the whole vector one book at a time
    for (int i = 0; i < library.size(); i++) {
        cout << "ID: " << library[i].bookID
             << ", Title: " << library[i].title
             << ", Author: " << library[i].author 
             << ", Publication Year: " << library[i].publicationYear
             << ", Copies Available: " << library[i].copiesAvailable << endl;
    }
}

// second overload that filters by BookID
void displayBooks(int bookID) {
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            cout << "ID: " << library[i].bookID
                 << ", Title: " << library[i].title
                 << ", Author: " << library[i].author
                 << ", Publication Year: " << library[i].publicationYear
                 << ", Copies Available: " << library[i].copiesAvailable << endl;
            return;
        }
    }
    cout << "No book found with ID " << bookID << "." << endl;
}

// third overload that filters by author
void displayBooks(string author) {
    bool found = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].author == author) {
            cout << "Book ID: " << library[i].bookID
                 << ", Title: " << library[i].title
                 << ", Author: " << library[i].author
                 << ", Publication Year: " << library[i].publicationYear
                 << ", Copies Available: " << library[i].copiesAvailable << endl;
        found = true;
        }
    }
    if (!found) {
        cout << "No books found by author " << author << "." << endl;
    }
}

// updateBooks function takes 4 params and updates existing data
void updateBooks(int bookID, string title, string author, int publicationYear) {
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            library[i].title = title;
            library[i].author = author;
            library[i].publicationYear = publicationYear;
            cout << "Book " << bookID << " has been updated!" << endl;
            return; 
        }
    } 
    cout << "No book found with ID " << bookID << "." << endl;
}

// pass-by-reference instance
// searchBook takes bookID uses a reference to state whether the book exists or not
Book searchBook(int bookID, bool &found) {
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            found = true;
            return library[i];
        }
    }

    found = false;
    Book empty;
    return empty;
}

// deleteBook matches bookID to remove a book
void deleteBook(int bookID) {
    for (int i = 0; i < library.size(); i++) {
        if(library[i].bookID == bookID) {
            library.erase(library.begin() + i);
            cout << "Book deleted successfully." << endl;
            return;
        }
    }
    cout << "No book found with ID " << bookID << "." << endl;
}

// default parameter instance if someone entered one parameter like (101) 
// the default copies would be set to 1
// borrowBook takes book ID and adds to inventory
void borrowBook(int bookID, int copies = 1) {
    if (copies <= 0) {
        cout << "Invalid number of copies." << endl;
        return;
    }
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            if (library[i].copiesAvailable >= copies) {
                library[i].copiesAvailable -= copies;
                cout << "Book borrowed successfully." << endl;
            } else {
                cout << "Not enough copies available to borrow." << endl;
            }
            return;
        }
    }
    cout << "No book found with ID " << bookID << "." << endl;
}

// default parameter instance
// returnBook takes bookID and returns to inventory
void returnBook(int bookID, int copies = 1) {
    if (copies <= 0) {
        cout << "Invalid number of copies." << endl;
        return;
    }
    for (int i = 0; i < library.size(); i++) {
        if (library[i].bookID == bookID) {
            library[i].copiesAvailable += copies;
            cout << "Book returned successfully." << endl;
            return;
        }
    }
    cout << "No book found with ID " << bookID << "." << endl;
}

// main function with a do while loop to ensure the menu displays at least once
// 7 choices with a 0 choice for quit
// switch wired up to move execute each case based on user input
int main() {
    int choice;

    do {
        cout << "\n--- Library menu ---" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Update Book" << endl;
        cout << "4. Search Book" << endl;
        cout << "5. Delete Book" << endl;
        cout << "6. Borrow Book" << endl;
        cout << "7. Return Book" << endl;
        cout << "0. Quit" << endl;
        choice = getValidInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                int bookID = getValidInt("Enter Book ID: ");
                string title, author;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                int publicationYear = getValidInt("Enter Publication Year: ");
                int copiesAvailable = getValidInt("Enter Copies Available: ");
                addBook(bookID, title, author, publicationYear, copiesAvailable);
                break;
            }
            case 2: {
                cout << "1. Display all books" << endl;
                cout << "2. Display book by ID" << endl;
                cout << "3. Display books by author" << endl;
                int displayChoice = getValidInt("Enter your choice: ");

                if (displayChoice  == 1){
                    displayBooks();
                } else if (displayChoice == 2) {
                    int bookID = getValidInt("Enter Book ID: ");
                    displayBooks(bookID);
                } else if (displayChoice == 3) {
                    string author;
                    cout << "Enter Author: ";
                    cin.ignore();
                    getline(cin, author);
                    displayBooks(author);
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            }
            case 3: {
                int bookID = getValidInt("Enter Book ID: ");
                string title, author;

                cin.ignore();
                cout << "Enter updated Title: ";
                getline(cin, title);
                cout << "Enter updated Author: ";
                getline(cin, author);
                int publicationYear = getValidInt("Enter updated Publication Year: ");

                updateBooks(bookID, title, author, publicationYear);
                break;
            }
            case 4: {
                int bookID = getValidInt("Enter Book ID: ");

                bool found;
                Book result = searchBook(bookID, found);

                if (found) {
                    cout << "ID: " << result.bookID
                         << ", Title: " << result.title
                         << ", Author: " << result.author
                         << ", Publication Year: " << result.publicationYear
                         << ", Copies Available: " << result.copiesAvailable << endl;
                } else {
                    cout << "No book found with ID " << bookID << "." << endl;
                }
                break;
            }
            case 5: {
                int bookID = getValidInt("Enter Book ID: ");
                deleteBook(bookID);
                break;
            }
            case 6: {
                int bookID = getValidInt("Enter Book ID: ");
                int copies = getValidInt("Enter number of copies to borrow (default 1): ");
                borrowBook(bookID, copies);
                break;
            }
            case 7: {
                int bookID = getValidInt("Enter Book ID: ");
                int copies = getValidInt("Enter number of copies to return (default 1): ");
                returnBook(bookID, copies);
                break;
            }
            case 0: {
                cout << "Exiting program..." << endl;
                break;
            }
            default: { 
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}