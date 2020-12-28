//
// Created by Rainy Memory on 2020/12/28.
//

#include "book.h"
#include "function.h"


int main() {
    int selector;
    cout << "Welcome to book management system!"<<endl;
    cout << "This system is written by Rainy Memory." << endl;
    cout << "0: Quit." << endl;
    cout << "1: Initialize file." << endl;
    cout << "2: Add book." << endl;
    cout << "3: Borrow book." << endl;
    cout << "4: Return book." << endl;
    cout << "5: Show book message." << endl;
    while (cin >> selector) {
        getchar();
        switch (selector) {
            case 0:
                exit(0);
            case 1:
                Initialize();
                break;
            case 2:
                AddBook();
                break;
            case 3:
                BorrowBook();
                break;
            case 4:
                ReturnBook();
                break;
            case 5:
                QueryBook();
                break;
        }
    }
    return 0;
}