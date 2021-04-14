//
// Created by Rainy Memory on 2021/4/6.
//

//still wa... **the f word**

#include <cstdio>
#include <iostream>
#include <sstream>
#include <set>
#include <cstring>

using namespace std;

template<class T>
inline void read(T &o, bool check_n = false) {
    char c = getchar();
    bool have_n = false;
    while (c < '0' || c > '9') {
        if (c == 'n')have_n = true;
        c = getchar();
    }
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
    if (check_n && !have_n)o = 0;
}

enum cmdType {
    FOR, END
};

struct for_t {
    string var;
    bool is_o_n = false;
    bool inexecution = false;
    
    for_t(const string &v, bool is, bool in) : var(v), is_o_n(is), inexecution(in) {}
    
    for_t() = default;
};

string cmd, arg[3];
set<string> global;
cmdType type;
int top = 0, res, t, l, w, res_w, max_top = 0;
int inexecution_layer = -1;
for_t stack[100];
int visit[100] = {0};//1: visited and o(n), -1: visited and o(1), 0: unvisited
int max_w[100] = {0};

cmdType get_line() {
    getline(cin, cmd);
    if (cmd[0] == 'F')return FOR;
    else return END;
}

bool judge_inexecution() {
    if (arg[2] == "n")return false;
    if (arg[1] == "n")return true;
    stringstream ss(cmd);
    ss >> arg[0] >> arg[0];
    int a, b;
    ss >> a >> b;
    return a > b;
}

int calc() {
    memset(visit, 0, sizeof(visit));
    memset(max_w, 0, sizeof(max_w));
    read(l), read(w, true);
    getchar();
    res = top = max_top = 0, inexecution_layer = -1;
    while (l--) {
        type = get_line();
        if (type == FOR) {
            if (visit[top] != 0)res--;
            stringstream ss(cmd);
            ss >> arg[0];
            ss >> arg[0] >> arg[1] >> arg[2];
            if (global.count(arg[0]) != 0)throw exception();
            global.insert(arg[0]);
            for_t f(arg[0], false, false);
            if (arg[2] == "n" && arg[1] != "n")f.is_o_n = true;
            if (judge_inexecution()) {
                f.inexecution = true;
                if (inexecution_layer == -1)inexecution_layer = top;
            }
            stack[top++] = f;
            if (max_top < top)max_top = top;
        }
        else {
            if (top == 0)throw exception();
            if (stack[top - 1].is_o_n) {
                if (visit[top - 1] != 1) {
                    if (inexecution_layer == -1)res++;
                    if (max_w[top - 1] < res)max_w[top - 1] = res;
                    
                }
                visit[top - 1] = 1;
            }
            else {
                if (visit[top - 1] == 0) {
                    visit[top - 1] = -1;
                }
            }
            global.erase(stack[top - 1].var);
            if (inexecution_layer == top - 1)inexecution_layer = -1;
            top--;
        }
    }
    if (top != 0)throw exception();
    int r = 0;
    for (int i = 0; i < max_top; i++) {
        if (r < max_w[i])r = max_w[i];
    }
    return r;
}

int main() {
    read(t);
    while (t--) {
        try {
            res_w = calc();
            if (res_w == w)cout << "Yes" << endl;
            else cout << "No" << endl;
            cout<<w<<" "<<res_w<<endl;
        } catch (...) {
            cout << "ERR" << endl;
        }
        global.clear();
    }
    return 0;
}