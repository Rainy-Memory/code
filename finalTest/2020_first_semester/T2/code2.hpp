#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>

using namespace std;

class CircleSet {
    
    friend istream &operator>>(istream &in, CircleSet &obj);

private:
    struct Circle {
        long long x, y, r;
        
        Circle(long long _x = 0, long long _y = 0, long long _r = 0) : x(_x), y(_y), r(_r) {}
    };
    
    int count;//集合中圆的数目
    Circle *circles;//集合中所有圆

public:
    CircleSet(int n) : count(n) {
        circles = new Circle[n];
    }
    
    ~CircleSet() {
        delete[] circles;
    }
    
    bool checkContaining(int p, int q) {
        int rp = circles[p].r, rq = circles[q].r;
        if (rp <= rq)return false;
        else {
            int dif_rad = rp > rq ? rp - rq : rq - rp;
            int dif_rad_square = dif_rad * dif_rad;
            int xp = circles[p].x, yp = circles[p].y, xq = circles[q].x, yq = circles[q].y;
            int dist = (xp - xq) * (xp - xq) + (yp - yq) * (yp - yq);
            if (dist >= dif_rad_square)return false;
            else return true;
        }
    }
    
    int getCircleContainingQ(int q) {
        int result = -1;
        for (int i = 0; i < count; i++) {
            if (checkContaining(i, q)) {
                if (result == -1 || result > circles[i].r)result = circles[i].r;
            }
        }
        return result;
    }
    
    long long &operator[](int position) {
        return circles[position].r;
    }
};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}
