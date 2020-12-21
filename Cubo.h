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
                //cout << path << endl;
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

        // De arriba a abajo
        limit1 = 512;
        limit2 = N;

        // CImg<float>* result = new CImg<float>(limit1, limit2);
        CImg<float>* result = new CImg<float>("./black.BMP");

        if (zi == zf) {
            // la imagen en la posicion z
            return images[zi];
        }

        //cout << "zi: " << zi << " zf: " << zf << " xi: " << xi << " xf: " << xf << " yi: " << yi << " yf: " << yf << endl;

        // TODO: calcular "inclinado"
        bool inclinado = !(xi == xf || yi == yf || zi == zf);

        if (inclinado) {
            for (int i = zi; i <= zf; ++i) {
                CImg<float>* img = images[i];
                // i = z

                auto m_b = p.find_line_given_z(i);
                long double m = m_b.first;
                long double b = m_b.second;

                //cout << "m: " << m << ", b: " << b << "\n";
                //cout << "i: " << i << '\n';

                if (m == -9999) {
                    // agarrar todos los y's con el 'b' como offset de 'x'
                    // TODO: hacer este caso
                    for (int j = yi; j <= yf; ++j) {
                        //cout << "x: " << b << ", y: " << j << "\n";
                        (*result)(b, j) = (*img)(b, j);
                    }
                } else {
                    for (int j = xi; j <= xf; ++j) {
                        int y = m*j + b;
                        //cout << "x: " << j << ", y: " << y << "\n";
                        (*result)(j, y) = (*img)(j, y);
                    }
                }
            }
        } else {
            int cont_x = 0;
            int cont_y = 0;
            // Creemos que este código está de más
            for (int i = zi; i <= zf; ++i) {
                CImg<float>* img = images[i];
                for (int j = xi; j <= xf; ++j) {
                    for (int k = yi; k <= yf; ++k) {
                        (*result)(cont_x, cont_y) = (*img)(j, k);
                        // (*result)(j-xi, i-zi) = (*img)(j, k);
                        // //cout << "x: " << j << ", y: " << k << ", z: " << i << '\n';
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
            //cout << "cont_x: " << cont_x << " cont_y: " << cont_y << endl;
        }

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