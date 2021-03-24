//
// Created by Rainy Memory on 2021/3/14.
//

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int stack[10007] = {0};//1-based
int top = 0, now = 0, num = 0, result;

int main() {
    string s;
    getline(cin, s);
    while (s[now] != '@') {
        if (s[now] <= '9' && s[now] >= '0') {
            num = (num << 3) + (num << 1) + s[now] - '0';
        }
        else {
            switch (s[now]) {
                case '.': {
                    stack[++top] = num, num = 0;
                    break;
                }
                case '+': {
                    result = stack[top - 1] + stack[top];
                    stack[--top] = result;
                    break;
                }
                case '-': {
                    result = stack[top - 1] - stack[top];
                    stack[--top] = result;
                    break;
                }
                case '*': {
                    result = stack[top - 1] * stack[top];
                    stack[--top] = result;
                    break;
                }
                case '/': {
                    result = stack[top - 1] / stack[top];
                    stack[--top] = result;
                    break;
                }
            }
        }
        now++;
    }
    printf("%d\n", stack[1]);
    return 0;
}