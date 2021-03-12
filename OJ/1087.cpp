//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>
#include <cstddef>
#include <functional>
#include <cstring>
#include <string>

//using namespace std;

#define MAXN 6000007

int order[MAXN] = {0};
int w[MAXN] = {0};
int pre[MAXN] = {0};
int nxt[MAXN] = {0};
bool deleted[MAXN] = {false};
int ans[MAXN] = {0};//if(erase[i]) { ans[i] == erased element's weight }, -1 represent query max weight, others is ans.
bool invalid[MAXN] = {false};
bool erase[MAXN] = {false};//No.i operation is erase a number.

inline void read(int &o) {
    char c = getchar();
    bool negative = false;
    while (c > '9' || c < '0') {
        if (c == '-')negative = true;
        c = getchar();
    }
    o = 0;
    while (c <= '9' && c >= '0') {
        o = o * 10 + c - '0';
        c = getchar();
    }
    if (negative)o *= -1;
}

void solveBig(int n) {
    //todo debug... still WA, can only handle huge data
    int q;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
    }
    read(q);
    int op, x;
    for (int i = 1; i <= q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
                nxt[x] = -1;
                pre[x] = -1;
                ans[i] = w[x];
                erase[i] = true;
            }
            else invalid[i] = true;
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])invalid[i] = true;
                else ans[i] = pre[x];
            }
            else {
                if (deleted[x])invalid[i] = true;
                else ans[i] = nxt[x];
            }
        }
        else ans[i] = -1;
    }
    int maxNum = -1;
    for (int i = 1; i <= n; i++) {
        if (!deleted[i] && maxNum < w[i])maxNum = w[i];
    }
    for (int i = q; i > 0; i--) {
        if (!invalid[i]) {
            if (ans[i] == -1) {
                if (maxNum != -1)ans[i] = maxNum;
                else invalid[i] = true;
            }
            else if (erase[i]) {
                if (maxNum < ans[i])maxNum = ans[i];
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (invalid[i] && !erase[i])puts("Invalid.");
        else if (!erase[i])printf("%d\n", ans[i]);
    }
}

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

bool cmp(const int &a, const int &b) {
    return w[a] < w[b];
}

void solveSort(int n) {
    int tail = n;
    int q;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
        order[i] = i;
    }
    sort(order, 1, n, cmp);
    read(q);
    int op, x;
    for (int i = 0; i < q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
            }
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", pre[x]);
            }
            else {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", nxt[x]);
            }
        }
        else {
            while (tail > 0 && deleted[order[tail]])tail--;
            if (tail == 0)puts("Invalid.");
            else printf("%d\n", w[order[tail]]);
        }
    }
}

int main() {
    int n;
    read(n);
//    if (n <= 1000000)solveSort(n);
//    else solveBig(n);
    solveSort(n);
    return 0;
}