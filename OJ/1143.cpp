//
// Created by Rainy Memory on 2021/4/29.
//

#include <iostream>

using namespace std;

#define maxn 40000

namespace RM {
    namespace inner {
        enum threshold {
            THRESHOLD = 16
        };
        
        inline int _lg(int n) {
            int k;
            for (k = 0; n > 1; n >>= 1)k++;
            return k;
        }
        
        template<class T>
        inline void _swap(T &o1, T &o2) {
            T temp(o1);
            o1 = o2, o2 = temp;
        }
        
        template<class T>
        void _make_heap(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            for (int i = low; i <= high; i++) {
                int index = i - low + 1;
                while ((index >> 1) >= 1 && compare(array[(index >> 1) + low - 1], array[index + low - 1])) _swap(array[index + low - 1], array[(index >> 1) + low - 1]), index >>= 1;
            }
        }
        
        template<class T>
        void _pop_heap(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            _swap(array[low], array[high]), high--;
            int now = 1, child;
            while ((now << 1) + low - 1 <= high) {
                child = (now << 1 | 1) + low - 1 <= high && compare(array[(now << 1) + low - 1], array[(now << 1 | 1) + low - 1]) ? now << 1 | 1 : now << 1;
                if (compare(array[now + low - 1], array[child + low - 1])) _swap(array[now + low - 1], array[child + low - 1]), now = child;
                else break;
            }
        }
        
        template<class T>
        void _sort_heap(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            for (int i = high; i > low; i--) {
                _pop_heap(array, low, i, compare);
            }
        }
        
        template<class T>
        int _quick_sort_partition(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            T temp = array[low];
            while (low < high) {
                while (low < high && !(compare(array[high], temp))) high--;
                if (low < high) array[low] = array[high], low++;
                while (low < high && (compare(array[low], temp) || (!compare(array[low], temp) && !compare(temp, array[low])))) low++;
                if (low < high) array[high] = array[low], high--;
            }
            array[low] = temp;
            return low;
        }
        
        template<class T>
        void insertion_sort(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            T temp;
            int j;
            for (int i = low + 1; i <= high; i++) {
                temp = array[i];
                j = i - 1;
                while (j >= low && compare(temp, array[j])) array[j + 1] = array[j], j--;
                array[j + 1] = temp;
            }
        }
        
        template<class T>
        void quick_sort(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            if (low >= high) return;
            int mid = _quick_sort_partition(array, low, high, compare);
            quick_sort(array, low, mid - 1, compare);
            quick_sort(array, mid + 1, high, compare);
        }
        
        template<class T>
        void heap_sort(T *array, int low, int high, bool (*compare)(const T &, const T &)) {
            _make_heap(array, low, high, compare);
            _sort_heap(array, low, high, compare);
        }
        
        template<class T>
        void intro_sort(T *array, int low, int high, bool (*compare)(const T &, const T &), int depth_limitation) {
            if (depth_limitation == 0) heap_sort(array, low, high, compare);
            else if (high - low < THRESHOLD) insertion_sort(array, low, high, compare);
            else {
                int mid = _quick_sort_partition(array, low, high, compare);
                intro_sort(array, low, mid - 1, compare, depth_limitation - 1);
                intro_sort(array, mid + 1, high, compare, depth_limitation - 1);
            }
        }
    }
    
    template<class T>
    void sort(T *array, int start, int end, bool (*compare)(const T &, const T &) = [](const T &o1, const T &o2) -> bool { return o1 < o2; }) {
        inner::intro_sort(array, start, end, compare, inner::_lg(end - start) * 2);
    }
}

struct tree_node {
    int x = -1;
    int y = -1;
    int num = 1;
    
    bool operator<(const tree_node &o) const {
        if (x == o.x)return y < o.y;
        return x < o.x;
    }
    
    bool operator==(const tree_node &o) const {
        return x == o.x && y == o.y;
    }
};

template<class T>
class BinaryIndexTree {
private:
    T *tree = nullptr;
    int size;
    
    static int lowbit(int x) {
        return x & -x;
    }

public:
    BinaryIndexTree(const T *a, int s) : size(s) {
        tree = new T[size + 1];
        for (int i = 1; i <= size; i++)tree[i] = 0;
        for (int i = 1; i <= size; i++) {
            tree[i] += a[i];
            int j = i + lowbit(i);
            if (j <= size)tree[j] += tree[i];
        }
    }
    
    ~BinaryIndexTree() {
        delete[] tree;
    }
    
    void update(int index, T delta) {
        while (index <= size) {
            tree[index] += delta;
            index += lowbit(index);
        }
    }
    
    T prefixSum(int index) const { // a[1] + a[2] + ... + a[index]
        T ret {0};
        while (index > 0) {
            ret += tree[index];
            index -= lowbit(index);
        }
        return ret;
    }
};

int n, ans[maxn] = {0}, bit_arr[maxn] = {0}, cnt = 0;
tree_node original_trench[maxn], trench[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)cin >> original_trench[i].x >> original_trench[i].y;
    RM::sort(original_trench, 0, n - 1);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            trench[cnt++] = original_trench[i];
            continue;
        }
        if (original_trench[i] == original_trench[i - 1])trench[cnt - 1].num++;
        else trench[cnt++] = original_trench[i];
    }
    BinaryIndexTree<int> bit(bit_arr, maxn);
    for (int i = 0; i < cnt; i++) {
        int num = bit.prefixSum(trench[i].y);//same position's trench cannot protect each other...
        ans[num] += trench[i].num;//if can, ans[num + trench[i].num - 1] += trench[i].num;
        bit.update(trench[i].y, trench[i].num);
    }
    for (int i = 0; i < n; i++)cout << ans[i] << endl;
    return 0;
}