#include <functional>
#include <stack>

using std::function;
using std::stack;

class Defer {
private:
    stack<function<void()>> funcStack;

public:
    Defer(function<void()> func) {
        funcStack.push(func);
    }
    
    void operator()(function<void()> func) {
        funcStack.push(func);
    }
    
    ~Defer() {
        while (!funcStack.empty()) {
            function<void()> func = funcStack.top();
            funcStack.pop();
            func();
        }
    }
    
};