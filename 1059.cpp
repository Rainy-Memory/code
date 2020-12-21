//
// Created by Rainy Memory on 2020/12/17.
//

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

class str {
private:
    char *storage = nullptr;
    size_t length = 0;

public:
    str() : length(0) {
        storage = new char[1];
        storage[0] = '\0';
    }
    
    str(const char &c) {
        storage = new char[2];
        storage[0] = c;
        storage[1] = '\0';
        length = 1;
    }
    
    str(const char *&&s_) {
        length = strlen(s_);
        storage = new char[length + 1];
        strcpy(storage, s_);
        storage[length] = '\0';
    }
    
    str(char *s) {
        length = strlen(s);
        storage = new char[length + 1];
        strcpy(storage, s);
        storage[length] = '\0';
    }
    
    str &operator=(const char *&&s_) {
        if (storage != nullptr)delete[] storage;
        length = strlen(s_);
        storage = new char[length + 1];
        strcpy(storage, s_);
        storage[length] = '\0';
        return *this;
    }
    
    str(const str &other) {
        length = other.length;
        storage = new char[length + 1];
        strcpy(storage, other.storage);
        storage[length] = '\0';
    }
    
    str &operator=(const str &other) {
        if (storage != nullptr)delete[] storage;
        length = other.length;
        storage = new char[length + 1];
        strcpy(storage, other.storage);
        storage[length] = '\0';
        return *this;
    }
    
    char &operator[](size_t pos) {
        return storage[pos];
    }
    
    const char &operator[](size_t pos) const {
        return storage[pos];
    }
    
    size_t len() const {
        return length;
    }
    
    str join(const std::vector<str> &strs) const {
        int total_len = 0;
        int num = strs.size();
        for (int i = 0; i < num; i++) {
            total_len += ((i == num - 1) ? (strs[i].len() + 1) : (strs[i].len() + length));
        }
        char *ptr = new char[total_len];
        size_t pos = 0;
        for (int i = 0; i < num; i++) {
            int start_pos_1 = pos;
            int end_pos = start_pos_1 + strs[i].len();
            for (; pos < end_pos; pos++) {
                ptr[pos] = strs[i][pos - start_pos_1];
            }
            int start_pos_2 = pos;
            for (; pos < end_pos + length; pos++) {
                ptr[pos] = storage[pos - start_pos_2];
                if (pos == total_len - 1)break;
            }
        }
        ptr[pos] = '\0';
        str temp(ptr);
        delete[] ptr;
        return temp;
    }
    
    str slice(size_t l, size_t r) const {
        char *ptr = new char[r - l + 1];
        for (int i = l; i < r; i++) {
            ptr[i - l] = storage[i];
        }
        ptr[r - l] = '\0';
        str temp(ptr);
        delete[] ptr;
        return temp;
    }
    
    ~str() {
        if (storage != nullptr)delete[] storage;
    }
};