#include <bits/stdc++.h>

// #include "Octree.h"
#include "CImg.h"
#include "Cubo.h"
#include "Octree.h"
#include "funciones.h"

using namespace std;


int main() {
    // Cubo* cubo = new Cubo("files.txt");

    // // cada imagen es 512x512

    // Punto p1 = Punto(0, 511, 2);
    // Punto p2 = Punto(0, 511, 2);
    // Punto p3 = Punto(0, 511, 2);
    // Punto p4 = Punto(0, 511, 2);

    // // cubo.getCorte(p1, p2, p3, p4).display();

    // delete cubo;

    Octree* octree = new Octree("files.txt");

    delete octree;

    return 0;
}
