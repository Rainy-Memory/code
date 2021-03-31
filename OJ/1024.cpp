//
// Created by Rainy Memory on 2020/12/17.
//

#include <cstring>

class MemoryPoolManager {
private:
    char *head;
    size_t block_size, block_cnt;
public:
    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_) {
        for (int i = 0; i < block_cnt - 1; i++) {
            *reinterpret_cast<void **>(head + i * block_size) = reinterpret_cast<void *>(head + (i + 1) * block_size);
        }
        *reinterpret_cast<void **>(head + (block_cnt - 1) * block_size) = nullptr;
    }
    
    void *allocate() {
        if (head == nullptr)return nullptr;
        void *ptr = reinterpret_cast<void *>(head);
        head = reinterpret_cast<char *>(*reinterpret_cast<void **>(head));
        return ptr;
    }
    
    void free(void *ptr) {
        *reinterpret_cast<void **>(ptr) = head;
        head = reinterpret_cast<char *>(ptr);
    }
};