class mystring {
private:
    char *str;
    int len;
public:
    mystring() {
        len = 0;
        str = nullptr;
    }
    
    virtual ~mystring() {
        delete str;
    }
    
    char *getStr() const {
        return str;
    }
    
    int getLen() const {
        return len;
    }
    
    void setStr(char *str) {
        mystring::str = str;
    }
    
    void setLen(int len) {
        mystring::len = len;
    }
    
    
    
};