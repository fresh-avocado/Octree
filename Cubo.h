#ifndef CUBO
#define CUBO

#include <bits/stdc++.h>
#include "CImg.h"
#include "Punto.h"
#include "funciones.h"

using namespace std;
using namespace cimg_library;

// el numero de imagenes de tipo .bmp
static const int N = 345;

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
                images[i++] = binarizar(img, 128);
            }
            file.close();
        }
    }

    CImg<float>& getCorte(Punto p1, Punto p2, Punto p3, Punto p4) {
        Plano p(p1, p2, p3, p4);

        CImg<float>* result = new CImg<float>(N, N);

        // result->display();
        // return result;
        
        int zi = p.getMaxZ();
        int zf = p.getMinZ();

        if (zi == zf) {
            // la imagen en la posicion z
            return *images[zi];
        }

        for (int i = zi; i <= zf; ++i) {
            CImg<float> img = *images[i];
            // TODO: pintar la linea

        }
        return *result;
    }

    ~Cubo() {
        printf("Destruyendo cubo\n");
        for (int i = 0; i < 345; ++i) {
            if (images[i]) {
                printf("Destroying %d image\n", i);
                delete images[i];
            } else {
                printf("Image %d is null\n", i);
            }
        }
    }
};

#endif