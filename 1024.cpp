//
// Created by Rainy Memory on 2020/12/17.
//

#include <cstring>

using namespace std;

class MemoryPoolManager {
private:
    char *head;
    /*
        head: the position of the first free block
    */
    size_t block_size, block_cnt;
    /*
        block_size: the size of each block (in bytes, at least 8);
        block_cnt: the maximum number of blocks
    */
public:
    MemoryPoolManager(char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_) {
        //todo: code whatever you want here to initialize
        for (int i = 0; i < block_cnt - 1; i++) {
            *reinterpret_cast<void **>(head + i * block_size) = reinterpret_cast<void **>(head + (i + 1) * block_size);
        }
        *reinterpret_cast<void **>(head + (block_cnt - 1) * block_size) = nullptr;
    }
    
    void *allocate() {
        //todo: return a pointer pointing at a free block (nullptr if no free block left)
        if (head == nullptr)return nullptr;
        void *temp = reinterpret_cast<void *>(head);
        head = reinterpret_cast<char *>(*reinterpret_cast<void **>(head));
        return temp;
    }
    
    void free(void *ptr) {
        //todo: make a block ready for reuse (we will guarantee that ptr is a block acquired by previous allocation)
        void *temp=reinterpret_cast<void*>(head);
        head=reinterpret_cast<char*>(ptr);
        *reinterpret_cast<void**>(ptr)=temp;
    }
};