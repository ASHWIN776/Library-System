#include <iostream>
#include <algorithm>
#define MAX_BOOKS 100
#define MAX_USERS 20
#define MAX_BOOKS_BORROW 5
using namespace std;

int book_idx{};
int user_idx{};

struct book{
    int id;
    string name;
    int qty;
    int borrowed;

    book(){
        id = -1;
        qty = 0;
        borrowed = 0;
    }

    void add(int _id, string _name, int _qty)
    {
        id = _id;
        name = _name;
        qty = _qty;
        borrowed = 0;
    }

    void print()
    {
        cout<<"id = "<<id<<"\tBook Name = "<<name<<"\tTotal Quantity = "<<qty<<"\tTotal  Borrowed = "<<borrowed<<"\n";
    }

    bool is_prefix(string _prefix){
        int input_len = name.size();
        int prefix_len = _prefix.size();

        if(input_len < prefix_len) return false;

        for(int i = 0; i < prefix_len; ++i)
            if(name[i] != _prefix[i])
                return false;
        return true;
    }

    bool borrow_book()
    {   
        if(borrowed == qty)
            return false;
        ++borrowed;
        return true;
    }

    void return_book()
    {   
        --borrowed;
    }
};

struct user{
    int id;
    string name;
    string borrowed_books[MAX_BOOKS_BORROW];
    int borrowed;

    user(){
        id = -1;
        borrowed = 0;
    }

    void add(int _id, string _name)
    {
        id = _id;
        name = _name;
    }

    bool borrow_book(string book_name)
    {   
        if(borrowed == MAX_BOOKS_BORROW)
            return false;
        borrowed_books[borrowed++] = book_name;
        return true;
    }

    void return_book()
    {
        --borrowed;
    }
};

void add_book(book &b){
    int id, qty;
    string name;

    cout<<"Enter book info: Id, name and total quantity: ";
    cin>>id>>name>>qty;

    b.add(id, name, qty);
    ++book_idx;
    cout<<"Book successfully added to the library!";
}

void search_by_prefix(book b[])
{   
    string prefix;
    cout<<"Enter book name prefix: ";
    cin>>prefix;

    for(int i = 0; i < book_idx; ++i)
        if(b[i].is_prefix(prefix))
            cout<<b[i].name<<"\n";
}

// used to print books after they are sorted
void print_books(book b[])
{
    for(int i = 0; i < book_idx; ++i)
        b[i].print();
}

// For sorting the array based on id
bool cmp_by_id(book &b1, book &b2)
{
    return b1.id < b2.id;
}

// For sorting the array based on name
bool cmp_by_name(book &b1, book &b2)
{
    return b1.name < b2.name;
}

void add_user(user &u)
{
    int id;
    string name;

    cout<<"Enter User info: Id and Name: ";
    cin>>id>>name;

    u.add(id, name);
    ++user_idx;
    cout<<"User successfully added to the library!";
}

void user_borrow_book(book b[], user u[])
{
    string user_name, book_name;
    cout<<"Enter username and Book name: ";
    cin>>user_name>>book_name;

    // search if book is present in the library
    int i;
    for(i = 0; i < book_idx; ++i)
    {
        if(b[i].name == book_name)
            break;
    }
    
    if(i == book_idx)
    {
        cout<<"Book not found :(";
        return;
    }

    // search if user is present in the library
    int j;
    for(j = 0; j < user_idx; ++j)
    {
        if(u[j].name == user_name)
            break;
    }

    if(j == user_idx)
    {
        cout<<"User not found :(";
        return;
    }
    
    // Borrow
    /*
    1. Check if book is present
    2. Check is user can borrow this book
    */
    if(b[i].borrow_book())
    {
        if(u[j].borrow_book(book_name))
            cout<<user_name<<" has successfully borrowed "<<book_name;
        else
            cout<<user_name<<" cant borrow this book as he/she has exausted the borrowing limit";
    }
    else    
        cout<<"The given book is currently unavailable";
}

void user_return_book(book b[], user u[])
{
    string user_name, book_name;
    cout<<"Enter username and Book name: ";
    cin>>user_name>>book_name;

    // search if book is present in the library
    int i;
    for(i = 0; i < book_idx; ++i)
    {
        if(b[i].name == book_name)
            break;
    }
    
    if(i == book_idx)
    {
        cout<<"Book not found :(";
        return;
    }

    // search if user is present in the library
    int j;
    for(j = 0; j < user_idx; ++j)
    {
        
        if(u[j].name == user_name)
        {
            // Search if user has borrowed the book
            int k;
            for(k = 0; k < u[j].borrowed; ++k)
            {
                if(u[j].borrowed_books[k] == book_name)
                    break;
            }
            if(k == u[j].borrowed)
            {
                cout<<"User has not borrowed this book, please check again";
                return;
            }
            else
            {
                // Return the book
                for(int a = k; a < u[j].borrowed; ++a)
                {
                    u[j].borrowed_books[a] = u[j].borrowed_books[a + 1];
                }
                u[j].return_book();
                b[i].return_book();
            }
        }
            break;
    }

    if(j == user_idx)
    {
        cout<<"User not found :(";
        return;
    }
    else
        cout<<book_name<<" returned successfully by "<<user_name;
}

int main()
{
    book books[MAX_BOOKS];
    user users[MAX_USERS];

    cout<<"\t\tLIBRARY SYSTEM\n\n";
    
    while(true){
        cout<<" 1. Add a book\n 2. Search books by prefix\n 3. Print Library by id\n 4. Print Library by name\n 5. Add a user\n 6 Borrow a book\n 7. Return a book\n 8. Exit\nChoose your option: ";
        int option;
        cin>>option;

        switch(option)
        {
            case 1: add_book(books[book_idx]);
            break;
            
            case 2: search_by_prefix(books);
            break;

            case 3: sort(books, books + book_idx, cmp_by_id); 
                    print_books(books);
            break;

            case 4: sort(books, books + book_idx, cmp_by_name);
                    print_books(books);
            break;

            case 5: add_user(users[user_idx]);
            break;

            case 6: user_borrow_book(books, users); 
            break;

            case 7: user_return_book(books, users);
            break;

            case 8: return 0;

            default: cout<<"Invalid Option, Try again";

        }
        cout<<"\n\n";
    }
    return 0;
}