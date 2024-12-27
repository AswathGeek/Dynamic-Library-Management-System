#include <iostream>
#include <vector>
#include <algorithm>
class Library
{
public:
    struct User
    {
        int id;
        std::string name;
        std::vector<int> borrowedBooks;
    };

    struct Book
    {
        int id;
        std::string title;
        bool isAvailable;
    };

    void addUser(int userId, std::string userName)
    {
        User newUser = {userId, userName, {}};
        users.push_back(newUser);
    }

    void addBook(int bookId, std::string bookTitle)
    {
        Book newBook = {bookId, bookTitle, true};
        books.push_back(newBook);
    }

    void borrowBook(int userId, int bookId)
    {
        User &user = findUserById(userId);
        Book &book = findBookById(bookId);

        if (book.isAvailable)
        {
            user.borrowedBooks.push_back(bookId);
            book.isAvailable = false;
            std::cout << user.name << " borrowed " << book.title << std::endl;
        }
        else
        {
            std::cout << "The book is not available." << std::endl;
        }
    }

    void returnBook(int userId, int bookId)
    {
        User &user = findUserById(userId);
        Book &book = findBookById(bookId);

        auto it = std::remove(user.borrowedBooks.begin(), user.borrowedBooks.end(), bookId);
        if (it != user.borrowedBooks.end())
        {
            user.borrowedBooks.erase(it, user.borrowedBooks.end());
            book.isAvailable = true; // Mark the book as available
            std::cout << user.name << " returned " << book.title << std::endl;
        }
        else
        {
            std::cout << "This book was not borrowed by the user." << std::endl;
        }
    }

    void displayBooks()
    {
        for (const auto &book : books)
        {
            std::cout << "Book ID: " << book.id << ", Title: " << book.title
                      << ", Available: " << (book.isAvailable ? "Yes" : "No") << std::endl;
        }
    }

    void displayUsers()
    {
        for (const auto &user : users)
        {
            std::cout << "User ID: " << user.id << ", Name: " << user.name << std::endl;
            std::cout << "Borrowed Books: ";
            if (user.borrowedBooks.empty())
            {
                std::cout << "None" << std::endl;
            }
            else
            {
                for (const auto &bookId : user.borrowedBooks)
                {
                    std::cout << bookId << " ";
                }
                std::cout << std::endl;
            }
        }
    }

private:
    std::vector<User> users;
    std::vector<Book> books;

    User &findUserById(int userId)
    {
        for (auto &user : users)
        {
            if (user.id == userId)
            {
                return user;
            }
        }
        throw std::invalid_argument("User not found");
    }

    Book &findBookById(int bookId)
    {
        for (auto &book : books)
        {
            if (book.id == bookId)
            {
                return book;
            }
        }
        throw std::invalid_argument("Book not found");
    }
};

int main()
{
    Library library;

    library.addUser(1, "Alice");
    library.addUser(2, "Bob");

    library.addBook(101, "The Great Gatsby");
    library.addBook(102, "1984");
    library.addBook(103, "To Kill a Mockingbird");

    std::cout << "Initial library status:" << std::endl;
    library.displayUsers();
    library.displayBooks();

    library.borrowBook(1, 101);

    library.borrowBook(2, 102);

    std::cout << "\nUpdated library status:" << std::endl;
    library.displayUsers();
    library.displayBooks();

    library.returnBook(1, 101);

    std::cout << "\nLibrary status after return:" << std::endl;
    library.displayUsers();
    library.displayBooks();

    return 0;
}
