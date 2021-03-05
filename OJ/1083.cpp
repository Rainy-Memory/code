//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>
#include <cstring>

using namespace std;

enum atomType {
    SET, LIST, SUBLIST, ELEMENT, SUBELEMENT
};

//-1: not checked, 0: false, 1: true
int isElement[207][207];
int isSubList[207][207];
string s;

bool check(atomType type, int start, int end) {
    string target;
    for (int i = start; i < end; i++)target += s[i];
    if (type == SET) {
        if (target[0] != '{' || target[target.length() - 1] != '}')return false;
        return check(LIST, start + 1, end - 1);
    }
    else if (type == LIST) {
        if (target.empty())return true;
        return check(SUBLIST, start, end);
    }
    else if (type == SUBLIST) {
        if (isSubList[start][end] >= 0)return isSubList[start][end] == 1;
        int pos[100] = {0};
        int cnt = 0;
        for (int i = 0; i < target.size(); i++) {
            if (target[i] == ',')pos[cnt++] = i + start;
        }
        if (check(ELEMENT, start, end))return true;
        for (int i = 0; i < cnt; i++) {
            int checkPos = pos[i];
            isSubList[start][end] = (check(ELEMENT, start, checkPos) && check(SUBLIST, checkPos + 1, end)) ? 1 : 0;
            if (isSubList[start][end] == 1)return true;
        }
        return false;
    }
    else if (type == ELEMENT) {
        if (isElement[start][end] >= 0)return isElement[start][end] == 1;
        isElement[start][end] = (check(SUBELEMENT, start, end) || check(SET, start, end)) ? 1 : 0;
        return isElement[start][end] == 1;
    }
    else if (type == SUBELEMENT) {
        if (target.size() != 1)return false;
        if (target[0] == '{' || target[0] == '}' || target[0] == ',')return true;
        else return false;
    }
    else return false;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> s;
        memset(isElement, -1, sizeof(isElement));
        memset(isSubList, -1, sizeof(isSubList));
        cout << "Word #" << i + 1 << ": " << (check(SET, 0, s.length()) ? "" : "No ") << "Set" << endl;
    }
    return 0;
}