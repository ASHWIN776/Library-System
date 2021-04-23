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

    void print()
    {
        cout<<"user: "<<name<<", id : "<<id<<", Borrowed Books: ";

        // If the user has not borrowed any books, it must show "Nil"
        if(borrowed == 0)   cout<<"Nil";
        

        for(int i = 0; i < borrowed; ++i)
            cout<<borrowed_books[i]<<" ";
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

    bool is_present(string book_name)
    {
        for(int i = 0; i < borrowed; ++i)
            if(borrowed_books[i] == book_name)
                return true;
        return false;
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
        {
            cout<<b[i].name<<"\n";
            return;
        }

    // if there are no books
    cout<<"Sorry there were no search results, check your spelling or try different prefixes";
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

// for getting the index of the object which has the given book
int book_exists(book b[], string book_name)
{
    int idx;
    for(idx = 0; idx < book_idx; ++idx)
    {
        if(b[idx].name == book_name)
            break;
    }
    
    if(idx == book_idx)
        return -1;
    
    return idx;
}
// for getting the index of the object which has the given user
int user_exists(user u[], string user_name)
{
    int idx;
    for(idx = 0; idx < user_idx; ++idx)
    {
        if(u[idx].name == user_name)
            break;
    }

    if(idx == user_idx)
       return -1;
    return idx;
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

    // search if book Exists return its index
    int book_exists_idx = book_exists(b, book_name);

    if(book_exists_idx == -1)
    {
        cout<<"Book not found :(";
        return;
    }

    // search if user Exists and return its index
    int user_exists_idx = user_exists(u, user_name);
    
    if(user_exists_idx == -1)
    {
        cout<<"User not found :(";
        return;
    }

    // Borrow
    /*
    1. Check if book is present
    2. Check if user can borrow this book
    */
    if(b[book_exists_idx].borrow_book())
    {
        if(u[user_exists_idx].borrow_book(book_name))
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
    int book_exists_idx = book_exists(b, book_name);

    if(book_exists_idx == -1)
    {
        cout<<"Book not found :(";
        return;
    }

    // search if user is present in the library
    int user_exists_idx = user_exists(u, user_name);
    
    if(user_exists_idx == -1)
    {
        cout<<"User not found :(";
        return;
    }

    // Search if user has borrowed the book
    int k;
    for(k = 0; k < u[user_exists_idx].borrowed; ++k)
    {
        if(u[user_exists_idx].borrowed_books[k] == book_name)
            break;
    }

    if(k == u[user_exists_idx].borrowed)
    {
        cout<<"User has not borrowed this book, please check again";
        return;
    }

    else
    {
        // Return the book
        for(int a = k; a < u[user_exists_idx].borrowed; ++a)
        {
            u[user_exists_idx].borrowed_books[a] = u[user_exists_idx].borrowed_books[a + 1];
        }
        u[user_exists_idx].return_book();
        b[book_exists_idx].return_book();
    }
    cout<<book_name<<" returned successfully by "<<user_name;
}

void print_who_borrowed_book_by_name(book b[], user u[])
{
    string book_name;
    cout<<"Enter the book name: ";
    cin>>book_name;

    //Search if book exists
    int book_exists_idx = book_exists(b, book_name);

    // Search if a user has that book borrowed
    for(int i = 0; i < user_idx; ++i)
        if(u[i].is_present(book_name))
            cout<<u[i].name<<" ";
}

void print_users(user u[])
{
    for(int i = 0; i < user_idx; ++i)
    {
        u[i].print();
        cout<<"\n";
    }
}

int main()
{
    book books[MAX_BOOKS];
    user users[MAX_USERS];

    cout<<"\t\tLIBRARY SYSTEM\n\n";
    
    while(true){
        cout<<" 1. Add a book\n 2. Search books by prefix\n 3. Print Library by id\n 4. Print Library by name\n 5. Add a user\n 6. Borrow a book\n 7. Return a book\n 8. Who all borrowed a book?\n 9. Print Users\n 10. Exit\n Choose your option: ";
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

            case 8: print_who_borrowed_book_by_name(books, users);
            break;

            case 9: print_users(users);
            break;

            case 10: return 0;


            default: cout<<"Invalid Option, Try again";

        }
        cout<<"\n\n";
    }
    return 0;
}