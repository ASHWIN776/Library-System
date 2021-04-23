#include <iostream>
#include <algorithm>
#define MAX_BOOKS 100
#define MAX_USERS 20
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
};

struct user{
    int id;
    string name;

    user(){
        id = -1;
    }

    void add(int _id, string _name)
    {
        id = _id;
        name = _name;
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

int main()
{
    book books[MAX_BOOKS];
    user users[MAX_USERS];

    cout<<"\t\tLIBRARY SYSTEM\n\n";
    
    while(true){
        cout<<" 1. Add a book\n 2. Search books by prefix\n 3. Print Library by id\n 4. Print Library by name\n 5. Add a user\n 6. Exit\n Choose your option: ";
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
            
            case 6: return 0;

            default: cout<<"Invalid Option, Try again";

        }
        cout<<"\n\n";
    }
    return 0;
}