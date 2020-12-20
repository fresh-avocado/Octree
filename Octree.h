#ifndef OCTREE
#define OCTREE

#include <bits/stdc++.h>

#include "CImg.h"
#include "Punto.h"
#include "funciones.h"

// el numero de imagenes de tipo .bmp
static const int M = 36;

class Octree {
    nodo* root{0};
    CImg<float>* images[M];
    int leafCount{0};
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
        root = new nodo(i, final);
        insert(i, final);
    }

    CImg<float>* getCorte(Punto p1, Punto p2, Punto p3, Punto p4) {
        Plano* plano = new Plano(p1, p2, p3, p4);

        CImg<float>* result = new CImg<float>(512, 512);

        search(root, result, plano);

        delete plano;
        return result;
    }

    void search(nodo*& node, CImg<float>*& result, Plano*& plano) {
        if (node->isLeaf) {
            // FIXME: qué pasa si solo intersecta en 1, 2 o 3 puntos?
            // vector<Punto> puntos = plano->intersects(node).second;

            // FIXME: caso analogo al de Cubo.h
            // TODO: falta el caso cuando el plano esta inclinado
            // PREGUNTA:
            // si el plano intersecta con este nodo, simplemente
            // pinto todos los pixeles entre (xi, fi) y (xf, yf)
            // (coordenadas en x y y del nodo) del color del nodo
            // en la imagen original? si es así, creo que lo de abajo está mal
            // sí

            // int minX = INT_MAX;
            // int maxX = INT_MIN;
            // int minY = INT_MAX;
            // int maxY = INT_MIN;

            // for (const auto& punto : puntos) {
            //     minX = min(minX, (int)punto.x);
            //     minY = min(minY, (int)punto.y);
            //     maxX = max(maxX, (int)punto.x);
            //     maxY = max(maxY, (int)punto.y);
            // }

            int minX = node->i.x;
            int maxX = node->f.x;
            int minY = node->i.y;
            int maxY = node->f.y;

            // FIXME: arreglar con lo de pasto
            for (int i = minX; i <= maxX; ++i) {
                for (int j = minY; j <= maxY; ++j) {
                    // puede ser que en result no se tenga que pintar en (i, j)
                    (*result)(i, j) = node->color;
                }
            }
        }
        for (int i = 0; i < 8; ++i) { // optmizacion del octree
            if (plano->intersects(node->children[i])) {
                search(node->children[i], result, plano);
            }
        }
    }

    void insert(Punto i, Punto f) {
        insertHelper(this->root, i, f);
    }

    void insertHelper(nodo*& node, Punto i, Punto f) {
        if (i.x > f.x || i.y > f.y || i.z > f.z) {
            return;
        }
        pair<bool, bool> checkCubeResult = checkCube(i, f);
        if (checkCubeResult.first) {
            // 255 = blanco
            // 0 = negro

            // blanco = true
            // negro = false

            node->color = checkCubeResult.second;
            node->isLeaf = true;
            ++leafCount;
            return;
        }

        //cout << "insertHelper\n";
        // Z: 0 -> 344
        // Y: 0 -> 512
        // X: 0 -> 512
        // inicial (0, 0, 0)
        // final (344, 512, 512)
        Punto mid = Punto(i.x + f.x, i.y + f.y, i.z + f.z);

        mid.x = floor(mid.x / 2);
        mid.y = floor(mid.y / 2);
        mid.z = floor(mid.z / 2);
        int midZ = mid.z;
        int finalZ = f.z;

        bool unaImagen = false;
        //cout << "mid: " << mid.x << ", " << mid.y << ", " << mid.z << "\n";

        // FIXME: quizas estos casos estan mal
        if (abs(f.z - i.z) == 1) {
            midZ = i.z;
            finalZ = f.z;
        } else if (abs(f.z - i.z) == 0) {
            unaImagen = true;
            midZ = i.z;
        }

        // Cubo 1 i -> mi
        Punto c1_i (i.x, i.y, i.z);
        Punto c1_f (mid.x, mid.y, midZ);

        // Cubo 2 (mid.x+1, i.y, i.z) -> (f.x, mid.y, mid.z)
        Punto c2_i (mid.x+1, i.y, i.z);
        Punto c2_f (f.x, mid.y, midZ);

        // Cubo 3 (i.x, mid.y+1, i.z) -> (mid.x, f.y, mid.z) 
        Punto c3_i (i.x, mid.y+1, i.z);
        Punto c3_f (mid.x, f.y, midZ);

        // Cubo 4 (mid.x+1, mid.y+1, i.z) -> (f.x, f.y mid.z) 
        Punto c4_i (mid.x+1, mid.y+1, i.z);
        Punto c4_f (f.x, f.y, midZ);

        // Cubo 5 (i.x, i.y, mid.z+1) -> (mid.x, mid.y, f.z) 
        Punto c5_i (i.x, i.y, mid.z+1);
        Punto c5_f (mid.x, mid.y, finalZ);

        // Cubo 6 (mid.x+1, i.y, mid.z+1) -> (f.x, mid.y, f.z) 
        Punto c6_i (mid.x+1, i.y, mid.z+1);
        Punto c6_f (f.x, mid.y, finalZ);

        // Cubo 7 (i.x, mid.y+1, mid.z+1) -> (mid.x, f.y, f.z)
        Punto c7_i (i.x, mid.y+1, mid.z+1);
        Punto c7_f (mid.x, f.y, finalZ);

        // Cubo 8 mid+1 -> f
        Punto c8_i (mid.x+1, mid.y+1, mid.z+1);
        Punto c8_f (f.x, f.y, finalZ);

        //cout << "crearon los puntos\n";
        
        node->children[0] = new nodo (c1_i, c1_f);
        insertHelper(node->children[0], c1_i, c1_f);

        //cout << "checkCube1 done\n";

        node->children[1] = new nodo (c2_i, c2_f);
        insertHelper(node->children[1], c2_i, c2_f);
        
        //cout << "checkCube2 done\n";

        node->children[2] = new nodo (c3_i, c3_f);
        insertHelper(node->children[2], c3_i, c3_f);

        //cout << "checkCube3 done\n";

        node->children[3] = new nodo (c4_i, c4_f);
        insertHelper(node->children[3], c4_i, c4_f);

        if (!unaImagen) {
            //cout << "checkCube4 done\n";

            node->children[4] = new nodo (c5_i, c5_f);
            insertHelper(node->children[4], c5_i, c5_f);

            //cout << "checkCube5 done\n";

            node->children[5] = new nodo (c6_i, c6_f);
            insertHelper(node->children[5], c6_i, c6_f);

            //cout << "checkCube6 done\n";

            node->children[6] = new nodo (c7_i, c7_f);
            insertHelper(node->children[6], c7_i, c7_f);

            //cout << "checkCube7 done\n";

            node->children[7] = new nodo (c8_i, c8_f);
            insertHelper(node->children[7], c8_i, c8_f);

            ////cout << "checkCube8 done\n";
        }

    }

    pair<bool, bool> checkCube(Punto i, Punto f) {
        //cout << "checkCube\n";
        //cout << "i: " << i.x << ", " << i.y << ", " << i.z << "\n";
        //cout << "f: " << f.x << ", " << f.y << ", " << f.z << "\n";
        // por cada imagen, chequear que el cuadrante delimitado por las coordenadas X y Y
        // tengan el mismo color
        if (i.x == f.x && i.y == f.y && i.z == f.z) {
            return make_pair(true, (*images[(int)i.z])(i.x, i.y, 0) == 255);
        }
        int firstImgIndex = (int)min(i.z, f.z);
        int lastImgIndex = (int)max(i.z, f.z);

        //cout << "firstImgIndex: " << firstImgIndex << "\n";
        //cout << "lastImgIndex: " << lastImgIndex << "\n";

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

        //cout << "se agarro el R, G y B\n";
        
        for (int i = firstImgIndex; i <= lastImgIndex; ++i) {
            for (int j = x; j <= xF; ++j) {
                for (int k = y; k <= yF; ++k) {
                    if ( (*images[i])(j, k, 0) != R && (*images[i])(j, k, 1) != G && (*images[i])(j, k, 2) != B ) {
                        return make_pair(false, false);
                    }
                }
            }
        }
        //cout << "retornando del for\n";
        return make_pair(true, (*images[firstImgIndex])(x, y, 0) == 255);
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