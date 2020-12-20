#include <bits/stdc++.h>

#include "CImg.h"
#include "Cubo.h"
#include "Octree.h"
#include "funciones.h"

#define OCTREE 1
#define CUBO 2

using namespace std;

int main() {

    int ed;

    print_with_color(VERDE, "Octree (1) o Cubo (2)?");

    cin >> ed;

    // paralelo al plano XZ
    // Punto p1 = Punto(0, 255, 35);
    // Punto p2 = Punto(511, 255, 35);
    // Punto p3 = Punto(0, 255, 0);
    // Punto p4 = Punto(511, 255, 0);

    // paralelo al plano YZ
    // Punto p1 = Punto(250, 0, 35);
    // Punto p2 = Punto(250, 511, 35);
    // Punto p3 = Punto(250, 0, 0);
    // Punto p4 = Punto(250, 511, 0);

    // paralelo al plano YZ
    // Punto p1 = Punto(200, 0, 35);
    // Punto p2 = Punto(200, 511, 35);
    // Punto p3 = Punto(200, 0, 0);
    // Punto p4 = Punto(200, 511, 0);

    /*
    
        Insertar las estadisticas acá:
            Tiempo de ejecución promedio de 'getCorte':
                Para el cubo
                Para el octree
            Uso de RAM
                Para el cubo
                Para el octree

    */

    if (ed == OCTREE) {

        print_with_color(AZUL, "A continuación se mostrarán 20 cortes random usando el Octree.\n");

        Octree* octree = new Octree("files.txt");

        int sum = 0;        
        for (int i = 0; i < 20; ++i) {
            auto start = chrono::high_resolution_clock::now();
            CImg<float>* temp = octree->getCorte(puntos[i][0], puntos[i][1], puntos[i][2], puntos[i][3]);
            auto end = chrono::high_resolution_clock::now();
            auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start);
            sum += executionTime.count();
            temp->display();
        }
        string msg = "Tiempo promedio de ejecución de 'getCorte': " + to_string(sum/20) + " us.\n";
        print_colorful(VERDE, msg);

        delete octree;
    } else if (ed == CUBO) {

        print_with_color(AZUL, "A continuación se mostrarán 20 cortes random usando el Cubo.\n");

        Cubo* cubo = new Cubo("files.txt");

        int sum = 0;        
        for (int i = 0; i < 20; ++i) {
            auto start = chrono::high_resolution_clock::now();
            CImg<float>* temp = cubo->getCorte(puntos[i][0], puntos[i][1], puntos[i][2], puntos[i][3]);
            auto end = chrono::high_resolution_clock::now();
            auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start);
            sum += executionTime.count();
            temp->display();
        }
        string msg = "Tiempo promedio de ejecución de 'getCorte': " + to_string(sum/20) + " us.\n";
        print_colorful(VERDE, msg);

        delete cubo;
    } else {
        print_with_color(ROJO, "Opción inválida.");
        return 0;
    }

    return 0;
}