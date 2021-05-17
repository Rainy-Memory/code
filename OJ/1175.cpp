//
// Created by Rainy Memory on 2021/5/10.
//

#include <iostream>

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

using std::cin;
using std::cout;
using std::endl;
using std::ios;

#define maxn 100007
#define maxm 1000007

template<class T>
T min(T a, T b) {
    return a > b ? b : a;
}

template<class T>
T max(T a, T b) {
    return a < b ? b : a;
}

long long l[maxn], male[maxm], female[maxm];

int main() {
    ios::sync_with_stdio(false);
    int n, m, cnt_male = 0, cnt_female = 0, gender;
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> l[i];
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> gender;
        if (gender == 1)cin >> male[cnt_male++];
        else cin >> female[cnt_female++];
    }
    RainyMemory::sort(male, 0, cnt_male - 1);
    RainyMemory::sort(female, 0, cnt_female - 1);
    long long tot_male = 0, tot_female = 0, now_time = 0;
    int ptr = 1, now_person = 0;
    while (ptr < n) {
        for (; max(male[now_person], female[now_person]) <= now_time && now_person < min(cnt_male, cnt_female); now_person++) {
            tot_male += now_time - male[now_person], tot_female += now_time - female[now_person];
        }
        now_time += l[ptr++];
    }
    for (int i = now_person; i < cnt_male; i++)tot_male += now_time - male[i];
    for (int i = now_person; i < cnt_female; i++)tot_female += now_time - female[i];
    double avg_male, avg_female;
    avg_male = double(tot_male) / double(cnt_male);
    avg_female = double(tot_female) / double(cnt_female);
    printf("%.2lf %.2lf\n", avg_male, avg_female);
    return 0;
}