// Library Management - LLD starter stub (C++).
#include <bits/stdc++.h>
using namespace std;

struct Book { string isbn,title; int total,available; };

class Library {
    static const int LOAN_DAYS=14, FINE_PER_DAY=5, MAX_BOOKS=3;
    unordered_map<string,Book> books;
    // loans: (isbn,member)-> dueDay
    map<pair<string,string>,int> loans;
    map<string,int> heldByMember;
public:
    void addBook(const Book& b){ books[b.isbn]=b; }
    void borrow(const string& isbn, const string& member, int today){
        // TODO: check availability + member limit; create loan(due=today+LOAN_DAYS); available--
        throw logic_error("TODO");
    }
    int returnBook(const string& isbn, const string& member, int today){
        // TODO: find loan; available++; return fine = max(0, today-due)*FINE_PER_DAY
        throw logic_error("TODO");
    }
};

int main(){
    Library lib; lib.addBook({"111","DDIA",1,1});
    lib.borrow("111","vansh",0);
    assert(lib.returnBook("111","vansh",20)==30); // 6 days late *5
    cout<<"PASS\n";
}
// PASSING: borrow respects availability+limit; correct late fine; restock; (bonus) reservation+notify.
