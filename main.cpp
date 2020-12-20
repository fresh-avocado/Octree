#include <bits/stdc++.h>

#include "CImg.h"
#include "Cubo.h"
#include "Octree.h"
#include "funciones.h"

using namespace std;


int main() {

    Cubo* cubo = new Cubo("files.txt");

    // cada imagen es 512x512

    Punto p1 = Punto(0, 255, 344);
    Punto p2 = Punto(511, 255, 344);
    Punto p3 = Punto(0, 255, 0);
    Punto p4 = Punto(511, 255, 0);

    cubo->getCorte(p1, p2, p3, p4)->display();

    delete cubo;

    // Octree* octree = new Octree("files.txt");
    // octree->getCorte(p1, p2, p3, p4)->display(); // corte transversal
    // delete octree;

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
