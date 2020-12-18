#ifndef OCTREE
#define OCTREE

#include <bits/stdc++.h>

#include "CImg.h"
#include "Punto.h"
#include "funciones.h"

// el numero de imagenes de tipo .bmp
static const int M = 50;

struct nodo {
    Punto i;
    Punto f;
    int color;
    nodo* children[8];
    nodo(Punto i, Punto f): i{i}, f{f} {}
};

class Octree {
    nodo* root{0};
    CImg<float>* images[M];
public:
    Octree(const string& f) {
        ifstream file(f.c_str());
        if (file.is_open()) {
            string path;
            int i = 0;
            while (getline(file, path)) {                
                auto img = CImg<float>(path.c_str());
                images[i++] = binarizar(img, 128);
                if (i == M) break;
            }
            file.close();
        }
        Punto i = Punto(0, 0, 0);
        Punto final = Punto(512, 512, M-1);
        insert(i, final);
    }

    CImg<float> getCorte(Punto p1, Punto p2, Punto p3, Punto p4) {
        // retorna el slice unu
    }

    void insert(Punto i, Punto f) {
        insertHelper(root, i, f);
    }

    void insertHelper(nodo*& node, Punto i, Punto f) {
        cout << "insertHelper\n";
        // Z: 0 -> 344
        // Y: 0 -> 512
        // X: 0 -> 512
        // inicial (0, 0, 0)
        // final (344, 512, 512)
        Punto mid = Punto(i.x+f.x, i.y+f.y, i.z+f.z);
        mid.x = (int)(mid.x / 2);
        mid.y = (int)(mid.y / 2);
        mid.z = (int)(mid.z / 2);

        cout << "mid: " << mid.x << ", " << mid.y << ", " << mid.y << "\n";

        // Cubo 1 i -> mi
        Punto c1_i (i.x, i.y, i.z);
        Punto c1_f (mid.x, mid.y, mid.y);

        // Cubo 2 (mid.x+1, i.y, i.z) -> (f.x, mid.y, mid.z)
        Punto c2_i (mid.x+1, i.y, i.z);
        Punto c2_f (f.x, mid.y, mid.z);

        // Cubo 3 (i.x, mid.y+1, i.z) -> (mid.x, f.y, mid.z) 
        Punto c3_i (i.x, mid.y+1, i.z);
        Punto c3_f (mid.x, f.y, mid.z);

        // Cubo 4 (mid.x+1, mid.y+1, i.z) -> (f.x, f.y mid.z) 
        Punto c4_i (mid.x+1, mid.y+1, i.z);
        Punto c4_f (f.x, f.y, mid.z);

        // Cubo 5 (i.x, i.y, mid.z+1) -> (mid.x, mid.y, f.z) 
        Punto c5_i (i.x, i.y, mid.z+1);
        Punto c5_f (mid.x, mid.y, f.z);

        // Cubo 6 (mid.x+1, i.y, mid.z+1) -> (f.x, mid.y, f.z) 
        Punto c6_i (mid.x+1, i.y, mid.z+1);
        Punto c6_f (f.x, mid.y, f.z);

        // Cubo 7 (i.x, mid.y+1, mid.z+1) -> (mid.x, f.y, f.z)
        Punto c7_i (i.x, mid.y+1, mid.z+1);
        Punto c7_f (mid.x, f.y, f.z);

        // Cubo 8 mid+1 -> f
        Punto c8_i (mid.x+1, mid.y+1, mid.y+1);
        Punto c8_f (f.x, f.y, f.z);

        cout << "crearon los puntos\n";
        
        if (checkCube(c1_i, c1_f)) {
            node->children[0] = new nodo(c1_i, c1_f);
        } else {
            auto c1 = new nodo(c1_i, c1_f);
            insertHelper(c1, c1_i, c1_f);
            node->children[0] = c1;
        }
        cout << "checkCube1 done\n";

        if (checkCube(c2_i, c2_f)) {
            node->children[1] = new nodo(c2_i, c2_f);
        } else {
            auto c2 = new nodo(c2_i, c2_f);
            insertHelper(c2, c2_i, c2_f);
            node->children[1] = c2;
        }
        cout << "checkCube2 done\n";

        if (checkCube(c3_i, c3_f)) {
            node->children[2] = new nodo(c3_i, c3_f);
        } else {
            auto c3 = new nodo(c3_i, c3_f);
            insertHelper(c3, c3_i, c3_f);
            node->children[2] = c3;
        }
        cout << "checkCube3 done\n";

        if (checkCube(c4_i, c4_f)) {
            node->children[3] = new nodo(c4_i, c4_f);
        } else {
            auto c4 = new nodo(c4_i, c4_f);
            insertHelper(c4, c4_i, c4_f);
            node->children[3] = c4;
        }
        cout << "checkCube4 done\n";

        if (checkCube(c5_i, c5_f)) {
            node->children[4] = new nodo(c5_i, c5_f);
        } else {
            auto c5 = new nodo(c5_i, c5_f);
            insertHelper(c5, c5_i, c5_f);
            node->children[4] = c5;
        }
        cout << "checkCube5 done\n";

        if (checkCube(c6_i, c6_f)) {
            node->children[5] = new nodo(c6_i, c6_f);
        } else {
            auto c6 = new nodo(c6_i, c6_f);
            insertHelper(c6, c6_i, c6_f);
            node->children[5] = c6;
        }
        cout << "checkCube6 done\n";

        if (checkCube(c7_i, c7_f)) {
            node->children[6] = new nodo(c7_i, c7_f);
        } else {
            auto c7 = new nodo(c7_i, c7_f);
            insertHelper(c7, c7_i, c7_f);
            node->children[6] = c7;
        }
        cout << "checkCube7 done\n";

        if (checkCube(c8_i, c8_f)) {
            node->children[7] = new nodo(c8_i, c8_f);
        } else {
            auto c8 = new nodo(c8_i, c8_f);
            insertHelper(c8, c8_i, c8_f);
            node->children[7] = c8;
        }
        cout << "checkCube8 done\n";

    }

    void search() {
        // TODO:
    }

    bool checkCube(Punto i, Punto f) {
        cout << "checkCube\n";
        cout << "i: " << i.x << ", " << i.y << ", " << i.z << "\n";
        cout << "f: " << f.x << ", " << f.y << ", " << f.z << "\n";
        // por cada imagen, chequear que el cuadrante delimitado por las coordenadas X y Y
        // tengan el mismo color
        if (i.x == f.x && i.y == f.y && i.z == f.z) {
            return true;
        }
        int firstImgIndex = (int)min(i.z, f.z);
        int lastImgIndex = (int)max(i.z, f.z);

        cout << "firstImgIndex: " << firstImgIndex << "\n";
        cout << "lastImgIndex: " << lastImgIndex << "\n";

        if (lastImgIndex >= M) {
            lastImgIndex = M-1;
        }
        if (firstImgIndex >= M) {
            firstImgIndex = M-1;
        }

        // itero sobre cada imagen que confirma el cubo
        int x = (int)min(i.x, f.x);
        int y = (int)min(i.y, f.y);
        int xF = (int)max(i.x, f.x);
        int yF = (int)max(i.y, f.y);

        int R = (*images[firstImgIndex])(x, y, 0);
        int G = (*images[firstImgIndex])(x, y, 1);
        int B = (*images[firstImgIndex])(x, y, 2);
        // int color = (R+G+B)/3;

        cout << "se agarro el R, G y B\n";
        
        for (int i = firstImgIndex; i <= lastImgIndex; ++i) {
            for (int j = x; j <= xF; ++j) {
                for (int k = y; k <= yF; ++k) {
                    if ( (*images[i])(j, k, 0) != R && (*images[i])(j, k, 1) != G && (*images[i])(j, k, 2) != B ) {
                        return false;
                    }
                }
            }
        }
        cout << "retornando del for\n";
        return true;
    }

    void destroy(nodo* aux) {
        if (!aux) return;
        for (int i = 0; i < 8; ++i) {
            destroy(aux->children[i]);
        }
        delete aux;
    }

    ~Octree() {
        destroy(root);
    }

};

#endif