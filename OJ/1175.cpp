//
// Created by Rainy Memory on 2021/5/10.
//

#include <iostream>

namespace RainyMemory {
    namespace inner_sort {
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
    void old_sort(T *array, int start, int end, bool (*compare)(const T &, const T &) = [](const T &o1, const T &o2) -> bool { return o1 < o2; }) {
        inner_sort::intro_sort(array, start, end, compare, inner_sort::_lg(end - start) * 2);
    }
    
    template<class ForwardIterator, class T>
    ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &val) {
        ForwardIterator middle;
        int len = last - first, half;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (*middle < val) {
                first = middle + 1;
                len = len - half - 1;
            }
            else len = half;
        }
        return first;
    }
    
    template<class ForwardIterator, class T>
    ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T &val) {
        ForwardIterator middle;
        int len = last - first, half;
        while (len > 0) {
            half = len >> 1;
            middle = first + half;
            if (val < *middle) len = half;
            else {
                first = middle + 1;
                len = len - half - 1;
            }
        }
        return first;
    }
    
    template<class InputIterator, class T>
    InputIterator find(InputIterator first, InputIterator last, const T &val) {
        while (first != last && *first != val)first++;
        return last;
    }
    
    namespace sort_assist {
        template<class RandomAccessIterator, class T>
        void _adjust_heap(RandomAccessIterator first, int holeIndex, int len, const T &val) {
            int secondChild = (holeIndex + 1) << 1;
            while (secondChild < len) {
                if (*(first + secondChild) < *(first + (secondChild - 1)))secondChild--;
                *(first + holeIndex) = *(first + secondChild);
                holeIndex = secondChild;
                secondChild = (secondChild + 1) << 1;
            }
            if (secondChild == len) {
                *(first + holeIndex) = *(first + (secondChild - 1));
                holeIndex = secondChild - 1;
            }
            *(first + holeIndex) = val;
        }
        
        template<class RandomAccessIterator, class T>
        void _pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, const T &val) {
            *result = *first;
            _adjust_heap(first, 0, last - first, val);
        }
        
        template<class RandomAccessIterator>
        void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
            _pop_heap(first, last - 1, last - 1, *(last - 1));
        }
        
        template<class RandomAccessIterator>
        void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
            while (last - first > 1) {
                pop_heap(first, last--);
            }
        }
        
        template<class RandomAccessIterator>
        void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
            if (last - first < 2)return;
            int len = last - first;
            int parent = (len - 2) >> 1;
            while (true) {
                _adjust_heap(first, parent, len, *(first + parent));
                if (parent == 0)return;
                parent--;
            }
        }
        
        template<class RandomAccessIterator, class T>
        void _partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, const T &) {
            make_heap(first, middle);
            for (RandomAccessIterator i = middle; i < last; i++) {
                if (*i < *first) {
                    _pop_heap(first, middle, i, T(*i));
                }
            }
            sort_heap(first, middle);
        }
        
        template<class RandomAccessIterator>
        inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
            _partial_sort(first, middle, last, *first);
        }
        
        template<class RandomAccessIterator, class T>
        void _unguarded_linear_insert(RandomAccessIterator last, const T &val) {
            RandomAccessIterator next = last;
            next--;
            while (val < *next) {
                *last = *next;
                last = next;
                --next;
            }
            *last = val;
        }
        
        template<class RandomAccessIterator, class T>
        inline void _linear_insert(RandomAccessIterator first, RandomAccessIterator last, const T &) {
            T val = *last;
            if (val < *first) {
                RandomAccessIterator d_last = last + 1;
                while (first != last) {
                    *(--d_last) = *(--last);
                }
                *first = val;
            }
            else _unguarded_linear_insert(last, val);
        }
        
        template<class RandomAccessIterator>
        void _insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
            if (first == last)return;
            for (RandomAccessIterator i = first + 1; i != last; i++) {
                _linear_insert(first, i, *first);
            }
        }
        
        template<class T>
        inline const T &_median(const T &a, const T &b, const T &c) {
            if (a < b) {
                if (b < c)return b;
                else if (a < c)return c;
                else return a;
            }
            else if (a < c)return a;
            else if (b < c)return c;
            else return b;
        }
        
        template<class RandomAccessIterator, class T>
        RandomAccessIterator _unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, const T &pivot) {
            while (true) {
                while (*first < pivot)first++;
                last--;
                while (pivot < *last)last--;
                if (!(first < last))return first;
                std::swap(*first, *last);
                first++;
            }
        }
        
        template<class Size>
        inline Size _lg(Size n) {
            Size k;
            for (k = 0; n > 1; n >>= 1)k++;
            return k;
        }
        
        enum coefficient {
            _threshold = 16
        };
        
        template<class RandomAccessIterator, class T, class Size>
        void _intro_sort_loop(RandomAccessIterator first, RandomAccessIterator last, const T &, Size depth_limit) {
            while (last - first > _threshold) {
                if (depth_limit == 0) {
                    partial_sort(first, last, last);
                    return;
                }
                depth_limit--;
                RandomAccessIterator cut = _unguarded_partition(first, last, T(_median(*first, *(first + (last - first) / 2), *(last - 1))));
                _intro_sort_loop(cut, last, *first, depth_limit);
                last = cut;
            }
        }
        
        template<class RandomAccessIterator, class T>
        inline void _unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last, const T &) {
            for (RandomAccessIterator i = first; i != last; i++) {
                _unguarded_linear_insert(i, T(*i));
            }
        }
        
        template<class RandomAccessIterator>
        void _final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
            if (last - first > _threshold) {
                _insertion_sort(first, first + _threshold);
                _unguarded_insertion_sort(first + _threshold, last, *first);
            }
            else _insertion_sort(first, last);
        }
    }
    
    template<class RandomAccessIterator>
    inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
        if (first != last) {
            sort_assist::_intro_sort_loop(first, last, *first, sort_assist::_lg(last - first) * 2);
            sort_assist::_final_insertion_sort(first, last);
        }
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
    RainyMemory::sort(male, male + cnt_male);
    RainyMemory::sort(female, female + cnt_female);
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
