#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "CImg.h"

using namespace cimg_library;

CImg<float>* binarizar(CImg<float>& img, int umbral) {
    CImg<float>* R = new CImg<float>(img.width(), img.height()); 
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j< img.height(); j++) {
            int r = img(i, j, 0);
            int g = img(i, j, 1);
            int b = img(i, j, 2);
            if ((r+g+b)/3  > umbral) 
                (*R)(i,j) = 255;
            else
                (*R)(i,j) = 0;
        }
    }
    return R; 
} 

enum Color {
    ROJO = 31,
    VERDE = 32,
    AMARILLO = 33,
    AZUL = 34,
};

void print_with_color(Color color, const string& str) {
    cout << "\033[1;" << color << "m"<< str << "\033[0m\n";
}

void print_colorful(Color color, const string& str) {
    cout << "\033[1;" << color << "m"<< str << "\033[0m";
}

#endif