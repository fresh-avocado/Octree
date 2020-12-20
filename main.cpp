#include <bits/stdc++.h>

#include "CImg.h"
#include "Cubo.h"
#include "Octree.h"
#include "funciones.h"

using namespace std;


int main() {

    // Cubo* cubo = new Cubo("files.txt");

    // cada imagen es 512x512

    Punto p1 = Punto(0, 255, 35);
    Punto p2 = Punto(511, 255, 35);
    Punto p3 = Punto(0, 255, 0);
    Punto p4 = Punto(511, 255, 0);

    // cubo->getCorte(p1, p2, p3, p4)->display();

    // delete cubo;

    Octree* octree = new Octree("files.txt");
    octree->getCorte(p1, p2, p3, p4)->display(); // corte transversal
    delete octree;

    // Plano* plano = new Plano(p1, p2, p3, p4);

    // Punto i = Punto(2, 2, 2);
    // Punto f = Punto(400, 400, 400);

    // Punto i = Punto(255, 255, 0);
    // Punto f = Punto(512, 512, 5);

    // nodo* node = new nodo(i, f);

    // cout << plano->intersects(node) << '\n';

    // delete plano;

    return 0;
}

// 20 PUNTOS RANDOM:

// PARALELOS A LA CARA FRONTAL

Punto p1 = Punto(0, 128, 35);
Punto p2 = Punto(511, 128, 35);
Punto p3 = Punto(0, 128, 0);
Punto p4 = Punto(511, 128, 0);
Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 255, 35);
// Punto p2 = Punto(511, 255, 35);
// Punto p3 = Punto(0, 255, 0);
// Punto p4 = Punto(511, 255, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 383, 35);
// Punto p2 = Punto(511, 383, 35);
// Punto p3 = Punto(0, 383, 0);
// Punto p4 = Punto(511, 383, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 200, 35);
// Punto p2 = Punto(511, 200, 35);
// Punto p3 = Punto(0, 200, 0);
// Punto p4 = Punto(511, 200, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 400, 35);
// Punto p2 = Punto(511, 400, 35);
// Punto p3 = Punto(0, 400, 0);
// Punto p4 = Punto(511, 400, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 100, 35);
// Punto p2 = Punto(511, 100, 35);
// Punto p3 = Punto(0, 100, 0);
// Punto p4 = Punto(511, 100, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 50, 35);
// Punto p2 = Punto(511, 50, 35);
// Punto p3 = Punto(0, 50, 0);
// Punto p4 = Punto(511, 50, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// PARALELOS A LA CARA DEL COSTADO

// Punto p1 = Punto(255, 0, 35);
// Punto p2 = Punto(255, 511, 35);
// Punto p3 = Punto(255, 0, 0);
// Punto p4 = Punto(255, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(128, 0, 35);
// Punto p2 = Punto(128, 511, 35);
// Punto p3 = Punto(128, 0, 0);
// Punto p4 = Punto(128, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(383, 0, 35);
// Punto p2 = Punto(383, 511, 35);
// Punto p3 = Punto(383, 0, 0);
// Punto p4 = Punto(383, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(200, 0, 35);
// Punto p2 = Punto(200, 511, 35);
// Punto p3 = Punto(200, 0, 0);
// Punto p4 = Punto(200, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(400, 0, 35);
// Punto p2 = Punto(400, 511, 35);
// Punto p3 = Punto(400, 0, 0);
// Punto p4 = Punto(400, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(100, 0, 35);
// Punto p2 = Punto(100, 511, 35);
// Punto p3 = Punto(100, 0, 0);
// Punto p4 = Punto(100, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(50, 0, 35);
// Punto p2 = Punto(50, 511, 35);
// Punto p3 = Punto(50, 0, 0);
// Punto p4 = Punto(50, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// PARALELOS A LA CARA DEL PISO

// Punto p1 = Punto(0, 0, 35);
// Punto p2 = Punto(0, 511, 35);
// Punto p3 = Punto(511, 0, 35);
// Punto p4 = Punto(511, 511, 35);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 0, 5);
// Punto p2 = Punto(0, 511, 5);
// Punto p3 = Punto(511, 0, 5);
// Punto p4 = Punto(511, 511, 5);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 0, 10);
// Punto p2 = Punto(0, 511, 10);
// Punto p3 = Punto(511, 0, 10);
// Punto p4 = Punto(511, 511, 10);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 0, 15);
// Punto p2 = Punto(0, 511, 15);
// Punto p3 = Punto(511, 0, 15);
// Punto p4 = Punto(511, 511, 15);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 0, 20);
// Punto p2 = Punto(0, 511, 20);
// Punto p3 = Punto(511, 0, 20);
// Punto p4 = Punto(511, 511, 20);
// Plano plano = Plano(p1, p2, p3, p4);

// Punto p1 = Punto(0, 0, 25);
// Punto p2 = Punto(0, 511, 25);
// Punto p3 = Punto(511, 0, 25);
// Punto p4 = Punto(511, 511, 25);
// Plano plano = Plano(p1, p2, p3, p4);