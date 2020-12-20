#ifndef CUBO_H
#define CUBO_H

#include <bits/stdc++.h>
#include "CImg.h"
#include "Punto.h"
#include "funciones.h"

using namespace std;
using namespace cimg_library;

// el numero de imagenes de tipo .bmp
static const int N = 40;

class Cubo {
    CImg<float>* images[N];
public: 
    Cubo(const string& f) {
        ifstream file(f.c_str());
        if (file.is_open()) {
            string path;
            int i = 0;
            while (getline(file, path)) {                
                auto img = CImg<float>(path.c_str());
                cout << path << endl;
                images[i++] = binarizar(img, 128);
            }
            file.close();
        }
    }

    CImg<float>* getCorte(Punto p1, Punto p2, Punto p3, Punto p4) {
        Plano p(p1, p2, p3, p4);
        
        int zi = p.getMinZ();
        int zf = p.getMaxZ();
        int xi = p.getMinX();
        int xf = p.getMaxX();
        int yi = p.getMinY();
        int yf = p.getMaxY();

        int limit1, limit2;

        if (yi == yf) { 
            limit1 = 512;
            limit2 = zf-zi;
        } else if (zi == zf) { 
            limit1 = 512;
            limit2 = 512;
        } else if (xi == xf) {
            limit1 = 512;
            limit2 = zf-zi;
        } else {
            // inclinado
            // chequear qué planos atraviesa
            // De derecha a izquierda
            if (zf-zi < yf - yi || zf-zi < xf - xi) {
                limit1 = 512;
                limit2 = zf-zi;
            } 
            // De arriba a abajo
            else {
                limit1 = 512;
                limit2 = zf-zi;
            }
            cout << "plano inclinado\n";
        }

        CImg<float>* result = new CImg<float>(512, 512);

        if (zi == zf) {
            // la imagen en la posicion z
            return images[zi];
        }

        cout << "zi: " << zi << " zf: " << zf << " xi: " << xi << " xf: " << xf << " yi: " << yi << " yf: " << yf << endl;

        // zi: 0 zf: 39 xi: 255 xf: 255 yi: 0 yf: 511    da error    

        // return result;
        int cont_x = 0;
        int cont_y = 0;
        // Creemos que este código está de másx
        for (int i = zi; i <= zf; ++i) {
            CImg<float>* img = images[i];
            for (int j = xi; j <= xf; ++j) {
                for (int k = yi; k <= yf; ++k) {
                    (*result)(cont_x, cont_y) = (*img)(j, k);
                    // (*result)(j-xi, i-zi) = (*img)(j, k);
                    // cout << "x: " << j << ", y: " << k << ", z: " << i << '\n';
                    if (xf-xi == 0) {
                        cont_x++;
                    }
                }
                if (yf-yi == 0) {
                    cont_x++;
                }
                // cont_y = 0;
            }
            cont_x = 0;
            cont_y++;
            // cont_x++;
        }
        cout << "cont_x: " << cont_x << " cont_y: " << cont_y << endl;

        // hallar puntos de interseccion entre imagen y el plano
        // hallar m y b a partir de esos dos puntos

        // Caso amarillo 
        // for (int i = zi; i <= zf; ++i) {
        //     CImg<float>* img = images[i];
        //     Punto p1 (0, 0, i);
        //     Punto p2 (512, 512, i);
        //     Punto p3 (0, 512, i);
        //     Punto p4 (512, 0, i);
        //     Plano p_img (p1, p2, p3, p4);

        //     auto inter = interseccion(p_img, p);
        //     auto m_b = m_y_b(inter);
        //     int m = m_b.first;
        //     int b = m_b.second;

        //     for (int j = xi; j <= xf; ++j) {
        //         int y = m*j + b;
        //         (*result)(j, y) = (*img)(j, y);
        //     }
        // }

        return result;
    }

    ~Cubo() {
        // printf("Destruyendo cubo\n");
        for (int i = 0; i < N; ++i) {
            if (images[i]) {
                // printf("Destroying %d image\n", i);
                delete images[i];
            } else {
                printf("Image %d is null\n", i);
            }
        }
    }
};

#endif