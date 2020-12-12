//
// Created by Rainy Memory on 2020/12/4.
//

#ifndef CODE_TEST_HEADER_H
#define CODE_TEST_HEADER_H

class test {
private:
    int value = 0;

public:
    test();
    
    test(test &);
    
    test(test &&);
    
    test(int);
    
    test temp_value();
    
    void print();
    
    void change(int);
    
    void change(int &);
    
};

#endif //CODE_TEST_HEADER_H
