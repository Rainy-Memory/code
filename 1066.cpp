//
// Created by Rainy Memory on 2020/12/1.
//

#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class mystring {
private:
    char *ch = nullptr;
    int len = 0;

public:
    
    mystring() {
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = 'a';
        }
    }
    
    mystring(int _len, int c) {
        len = _len;
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c;
        }
    }
    
    mystring(string &c) {
        len = c.length();
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c[i];
        }
    }
    
    ~mystring() {
        delete[] ch;
        len = 0;
        ch = nullptr;
    }
    
    void out() {
        for (int i = 0; i < len; i++) {
            cout << ch[i];
        }
    }
    
    void ADD(const mystring &temp) {
        int temp_len = len + temp.len;
        char *temp_string = new char[temp_len];
        for (int i = 0; i < temp_len; i++) {
            temp_string[i] = ((i < len) ? ch[i] : temp.ch[i - len]);
        }
        len = temp_len;
        delete[] ch;
        ch = temp_string;
        temp_string = nullptr;
    }
    
    int get_len() {
        return len;
    }
    
    bool operator<(const mystring &temp) {
        int min_len = len < temp.len ? len : temp.len;
        for (int i = 0; i < min_len; i++) {
            if (ch[i] < temp.ch[i]) {
                return true;
            }
            else if (ch[i] > temp.ch[i]) {
                return false;
            }
        }
        if (len < temp.len)return true;
        else return false;
    }
    
    char &operator[](int position) {
        if (position < len && position >= 0)return ch[position];
        static char temp_ = '0';
        return temp_;
    }
};

string str_in1, str_in2;
int n, id;

int main() {
    cin >> id;
    if (id == 1) {
        mystring str1(100, 'a');
        str1.out();
        puts("");
        // cout << str1 << endl;
    }
    else if (id == 2) {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str2[x] << endl;
        }
    }
    else if (id == 3) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int) (str2 < str3) << endl;
    }
    else if (id == 4) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        str2.out();
        puts("");
        // cout << str2 << endl;
    }
    else {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str3[x] << endl;
        }
        cout << str2.get_len() << " " << str3.get_len() << endl;
        cout << (int) (str2 < str3) << endl;
        str2.ADD(str3);
        str2.out();
        puts("");
        // cout << str2 << endl;
        cout << str2.get_len() << endl;
    }
    return 0;
}