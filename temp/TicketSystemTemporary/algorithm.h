//
// Created by Rainy Memory on 2021/3/6.
//

#ifndef TICKETSYSTEM_AUTOMATA_ALGORITHM_H
#define TICKETSYSTEM_AUTOMATA_ALGORITHM_H

/*
 * algorithm.h
 * --------------------------------------------------------
 * A header implements [sort] using heuristic algorithm,
 * [lower_bound], [upper_bound] and [find] for BPlusTree.
 *
 */

namespace RainyMemory {
    template<class ptr, class T>
    ptr lower_bound(ptr first, ptr last, const T &val) {
        ptr now;
        int count = last - first, step;
        while (count > 0) {
            step = count >> 1;
            now = first + step;
            if (*now < val) {
                first = ++now;
                count -= step + 1;
            }
            else count = step;
        }
        return first;
    }
    
    template<class ptr, class T>
    ptr upper_bound(ptr first, ptr last, const T &val) {
        ptr now;
        int count = last - first, step;
        while (count > 0) {
            step = count >> 1;
            now = first + step;
            if (!(val < *now)) {
                first = ++now;
                count -= step + 1;
            }
            else count = step;
        }
        return first;
    }
    
    template<class ptr, class T>
    ptr find(ptr first, ptr last, const T &val) {
        int len = last - first;
        for (int i = 0; i < len; i++, first++) {
            if (!(val < *first) && !(*first < val)) return first;
        }
        return last;
    }
}

#endif //TICKETSYSTEM_AUTOMATA_ALGORITHM_H
