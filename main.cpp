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

    /*
        Corrimos los 20 cortes random, sacamos el promedio y eso nos daba un resultado.
        Ese resultado, lo obtuvimos tres veces (corrimos el programa tres veces) y finalmene
        sacamos el promedio de esas tres.
    
            Tiempo de ejecución promedio de 'getCorte':
                Cubo con cortes paralelos: (7403 + 6531 + 6396)/3 = 6776 us
                Octree con cortes paralelos: (26843 + 32408 + 37710)/3 = 32 320 us
                Cubo con cortes inclinados y paralelos: (6212 + 5962 + 6206)/3 = 6126 us
                Octree con cortes inclinados y paralelos: _
            Uso de RAM:
                Cubo: (61 + 46 + 51)/3 = 52 MB
                Octree: (89 + 82 + 88)/3 = 86 MB 

    */

    if (ed == OCTREE) {

        print_with_color(AZUL, "A continuación se mostrarán 20 cortes random usando el Octree.\n");

        Octree* octree = new Octree("files.txt");

        int sum = 0;        
        for (int i = 0; i < 20; ++i) {
            auto start = chrono::high_resolution_clock::now();
            cout << "i: " << i << "\n";
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
    }

    return 0;
}