#include <iostream>
#include <memory>
#include <string>

class Book; // Forward declaration

class Patron {
public:
    std::string name;
    std::shared_ptr<Book> borrowedBook; // Owning reference

    Patron(const std::string& n) : name(n) {
        std::cout << "Patron " << name << " created.\n";
    }
    ~Patron() {
        std::cout << "Patron " << name << " destroyed.\n";
    }
};

class Book {
public:
    std::string title;
    // Non-owning reference: does not keep Patron alive
    std::weak_ptr<Patron> lastPatron;

    Book(const std::string& t) : title(t) {
        std::cout << "Book " << title << " created.\n";
    }
    ~Book() {
        std::cout << "Book " << title << " destroyed.\n";
    }

    void displayLastPatron() {
        // Must convert weak_ptr to shared_ptr to safely access the object
        if (std::shared_ptr<Patron> p = lastPatron.lock()) {
            std::cout << "Last patron was: " << p->name << std::endl;
        } else {
            std::cout << "The last patron record has expired (object deleted).\n";
        }
    }
};

int main() {
    {
        std::shared_ptr<Patron> patron1 = std::make_shared<Patron>("Alice");
        std::shared_ptr<Book> book1 = std::make_shared<Book>("C++ Primer");

        // Establish the link
        patron1->borrowedBook = book1;
        book1->lastPatron = patron1; // Assign weak_ptr from shared_ptr

        // Display info
        book1->displayLastPatron(); //

        // When the block ends, patron1 and book1 shared_ptrs go out of scope.
        // Because the reference from Book to Patron is weak, it doesn't prevent
        // the Patron from being destroyed. The reference counts drop to zero,
        // and both objects are properly destroyed.
    } // Scope ends here.
    return 0;
}
