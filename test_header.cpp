//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include "test_header.h"
using namespace std;

test::test(){
    value=1;
}

test::test(test &b) {
    value=b.value;
}

test::test(test &&b){
    value=b.value;
}

test::test(int i) {
    value=i;
}

void test::change(int i) {
    value=i;
}

void test::change(int &i) {
    value=i;
}


void test::print() {
    cout<<value<<endl;
}

test test::temp_value() {
    test a(3);
    return a;
}