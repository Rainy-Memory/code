//
// Created by Rainy Memory on 2021/5/14.
//

#include <iostream>

using namespace std;
typedef long long ll;

namespace RainyMemory {
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

#define maxn 1000007
int n;
ll k;
ll a[maxn], b[maxn], tree[maxn];

struct t {
    ll val;
    int loc;
    int original_loc;
} prefix[maxn];

ll max(ll c, ll d) {
    return c > d ? c : d;
}

int lowbit(int x) {
    return x & -x;
}

void update(int index, ll delta) {
    while (index <= n) {
        tree[index] += delta;
        index += lowbit(index);
    }
}

ll query(int index) {
    ll ret = 0;
    while (index >= 1) {
        ret += tree[index];
        index -= lowbit(index);
    }
    return ret;
}

//return number of ranges that has average bigger or equal to x
ll rangeNum(ll x) {
    tree[1] = 0;
    for (int i = 2; i <= n + 1; i++)b[i] = a[i - 1] - x, tree[i] = 0;
    prefix[1].val = 0;
    for (int i = 2; i <= n + 1; i++)prefix[i].val = prefix[i - 1].val + b[i], prefix[i].original_loc = i;
    RainyMemory::sort<t>(prefix, 1, n + 1, [](const t &o1, const t &o2) -> bool { return o1.val < o2.val; });
    int cnt = 1;
    for (int i = 1; i <= n + 1; i++) {
        if (i > 1 && prefix[i].val == prefix[i - 1].val)prefix[i].loc = prefix[i - 1].loc;
        else prefix[i].loc = cnt++;
    }
    RainyMemory::sort<t>(prefix, 1, n + 1, [](const t &o1, const t &o2) -> bool { return o1.original_loc < o2.original_loc; });
    ll ret = 0;
    for (int i = 1; i <= n + 1; i++) {
        ret += query(prefix[i].loc - 1);
        update(prefix[i].loc, 1);
    }
    return ret;
}

int main() {
    scanf("%d %lld", &n, &k);
    ll max_num = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        a[i] *= 10000;
        max_num = max(max_num, a[i]);
    }
    ll r = max_num, l = 0;
    while (r - l > 1) {
        ll mid = (l + r) >> 1;
        ll num = rangeNum(mid);
        if (num >= k)l = mid;
        else r = mid;
    }
    ll res = r;
    printf("%.3lf", double(res) / 10000);
    return 0;
}
