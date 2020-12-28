//
// Created by Rainy Memory on 2020/12/28.
//

#ifndef CODE_BOOK_H
#define CODE_BOOK_H

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>

using namespace std;

class Book {
private:
    int no;
    char name[40];
    int borrowed;//If borrowed==0->not borrowed. Else borrowed==readerNo.
public:
    Book(const char *s = "", int total_no = 0);
    
    void Borrow(int readerNo);
    
    void Return();
    
    void Query() const;
    
    void Display() const;
    
    int GetNo() const;
};

#endif //CODE_BOOK_H
