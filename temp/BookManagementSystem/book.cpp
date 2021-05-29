//
// Created by Rainy Memory on 2020/12/28.
//
#include "book.h"

Book::Book(const char *s, int total_no) : no(total_no), borrowed(0) {
    strcpy(name, s);
}

void Book::Borrow(int readerNo) {
    if (borrowed != 0)cerr << "[Error]Borrow failed: This book has been borrowed!" << endl;
    else {
        cout << "[Info]Complete book borrowing." << endl;
        borrowed = readerNo;
    }
}

void Book::Return() {
    if (borrowed == 0)cerr << "[Error]Return failed: This book hasn't been borrowed!" << endl;
    else {
        cout << "[Info]Complete book returning." << endl;
        borrowed = 0;
    }
}

void Book::Query() const {
    cout << "[Info]Complete query." << endl;
    cout << "Book No: " << no << endl;
    cout << "Book name: " << name << endl;
    if (borrowed == 0)cout << "This book has not been borrowed now." << endl;
    else cout << "This book has been borrowed by Reader " << borrowed << "." << endl;
}

void Book::Display() const {
    cout << setw(10) << left << no << setw(20) << left << name << setw(10) << left << borrowed << endl;
}

int Book::GetNo() const {
    return no;
}