#ifndef OCTREE
#define OCTREE

#include <bits/stdc++.h>

#include "CImg.h"

class Octree {

public:
    CImg<char> getCorte(3-upla p1, 3-upla p2, 3-upla p3, 3-upla p4) {
        // retorna el slice unu
    }

    void insert(CImg<char>* img[], int n, Point i, Point f) {
        // Z: 0 -> 344
        // Y: 0 -> 512
        // X: 0 -> 512
        // inicial (0, 0, 0)
        // final (344, 512, 512)
        Point mid = (i+f)/2;
        i -> mid // 1
        (mid.x+1, i.y, i.z) -> (f.x, mid.y, mid.z) // 2
        (i.x, mid.y+1, i.z) -> (mid.x, f.y, mid.z) // 3
        (mid.x, mid.y, i.z) -> (f.x, f.y mid.z) // 4
        (i.x, i.y, mid.z) -> (mid.x, mid.y, f.z) // 5
        (mid.x, i.y, mid.z) -> (f.x, mid.y, f.z) // 6
        (i.x, mid.y, mid.z) -> (mid.x, f.y, f.z) // 7
        mid+1 -> f // 8
    }

};

#endif