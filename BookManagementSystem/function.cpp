//
// Created by Rainy Memory on 2020/12/28.
//

#include "function.h"

void Initialize() {
    fstream outfile("book_message", fstream::out);
    int number = 0;
    outfile.write(reinterpret_cast<const char *>(&number), sizeof(int));
    outfile.close();
    cout << "[Info]Complete initialize." << endl;
}

void AddBook() {
    cout << "[Info]Start book adding." << endl;
    char ch[40];
    Book *bp;
    int no;
    fstream outfile("book_message");
    //get book number now
    outfile.seekg(0);
    outfile.read(reinterpret_cast<char *>(&no), sizeof(int));
    //generate new book info
    no++;
    cout << "Input book name:" << endl;
    cin.getline(ch,40,'\n');
    bp = new Book(ch, no);
    //write in file
    outfile.seekp(0, ios::end);
    outfile.write(reinterpret_cast<const char *>(bp), sizeof(Book));
    delete bp;
    //update book number
    outfile.seekp(0);
    outfile.write(reinterpret_cast<const char *>(&no), sizeof(int));
    //end
    outfile.close();
    cout << "[Info]Complete book adding." << endl;
}

void BorrowBook() {
    cout << "[Info]Start book borrowing." << endl;
    int bookNo, readerNo;
    fstream iofile("book_message");
    Book bk;
    cout << "Input book number and reader number:" << endl;
    cin >> bookNo >> readerNo;
    iofile.seekg((bookNo - 1) * sizeof(Book) + sizeof(int));
    iofile.read(reinterpret_cast<char *>(&bk), sizeof(Book));
    bk.Borrow(readerNo);
    iofile.seekp((bookNo - 1) * sizeof(Book) + sizeof(int));
    iofile.write(reinterpret_cast<const char *>(&bk), sizeof(Book));
    iofile.close();
    //cout << "[Info]Complete book borrowing." << endl;
}

void ReturnBook() {
    cout << "[Info]Start book returning." << endl;
    int bookNo;
    fstream iofile("book_message");
    Book bk;
    cout << "Input book number:" << endl;
    cin >> bookNo;
    iofile.seekg((bookNo - 1) * sizeof(Book) + sizeof(int));
    iofile.read(reinterpret_cast<char *>(&bk), sizeof(Book));
    bk.Return();
    iofile.seekp((bookNo - 1) * sizeof(Book) + sizeof(int));
    iofile.write(reinterpret_cast<const char *>(&bk), sizeof(Book));
    iofile.close();
    //cout << "[Info]Complete book returning." << endl;
}

void QueryBook() {
    cout << "[Info]Start book querying." << endl;
    cout << setw(10) << left << "Book No" << setw(20) << left << "Book name" << setw(10) << left << "Book borrower" << endl;
    fstream infile("book_message", fstream::in);
    Book bk;
    infile.seekg(sizeof(int));
    infile.read(reinterpret_cast<char *>(&bk), sizeof(Book));
    while (!infile.eof()) {
        bk.Display();
        infile.read(reinterpret_cast<char *>(&bk), sizeof(Book));
    }
    infile.close();
    cout << "[Info]Complete book querying." << endl;
}


























