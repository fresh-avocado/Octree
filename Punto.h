#ifndef PUNTO
#define PUNTO

#include <bits/stdc++.h>

using namespace std;

struct Punto{
    float x = -1;
    float y = -1;
    float z = -1;

    Punto(float x_, float y_, float z_) : x{x_}, y{y_}, z{z_} {}
    Punto() = default;

   Punto operator+ (const int& n) {
        Punto answer;
        answer.x = (this->x + n);
        answer.y = (this->y + n);
        answer.z = (this->z + n);
        return answer;
    }

    Punto operator+ (const Punto& B) {
        Punto answer;
        answer.x = (this->x + B.x);
        answer.y = (this->y + B.y);
        answer.z = (this->z + B.z);
        return answer;
    }

    Punto operator- (const Punto& B) {
        Punto answer;

        answer.x = (this->x - B.x);
        answer.y = (this->y - B.y);
        answer.z = (this->z - B.z);
        return answer;
    }

    Punto operator/ (const int& n) {
        Punto answer;
        answer.x = (this->x/n);
        answer.y = (this->y/n);
        answer.z = (this->z/n);
        return answer;
    }


    Punto operator* (const  Punto& B) {
        Punto answer;
        answer.x = (this->y * B.z - this->z * B.y );
        answer.y = (this->z * B.x - this->x * B.z);
        answer.z = (this->x * B.y - this->y * B.x);
        return answer;
    }


    friend bool operator== (const Punto& lhs, const Punto& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;        
    }

};

struct nodo {
    Punto i;
    Punto f;
    bool color;
    bool isLeaf;
    nodo* children[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    nodo(Punto i, Punto f): i{i}, f{f} {}
};

struct Plano{
    Punto l1a, l1b;
    Punto l2a, l2b;

    float xm, ym, zm;
    float xt, yt, zt;

    float rxm, b;

  

    //linea 3d = l1b, l2b, ancla l1b
    //recta 2d = l2b, l2a ancla l2b
    

    //parametricas 

    pair<float, float> xy_with_given_z(float z){

        float x = xm + (xt*((z - zm)/zt));
        float y = ym + (yt*((z - zm)/zt));


        return {x,y};
    }

    int getMinZ() {
        return min({l1a.z, l1b.z, l2a.z, l2b.z});
    }

    int getMaxZ() {
        return max({l1a.z, l1b.z, l2a.z, l2b.z});
    }

    int getMinX() {
        return min({l1a.x, l1b.x, l2a.x, l2b.x});
    }

    int getMaxX() {
        return max({l1a.x, l1b.x, l2a.x, l2b.x});
    }

    int getMinY() {
        return min({l1a.y, l1b.y, l2a.y, l2b.y});
    }

    int getMaxY() {
        return max({l1a.y, l1b.y, l2a.y, l2b.y});
    }

    pair<float,float> find_line(Punto A, Punto B) {
        float a1 = B.y - A.y;
        float b1 = A.x - B.x;
        float c1 = a1*A.x + b1*A.y;
        rxm = (a1*-1)/b1;
        b = c1/b1;
        //cout << rxm << "x + " << b;
        return {rxm, b};
    }

    pair<float,float> find_line_given_z( float z) {

        auto xy = xy_with_given_z(z);

        float diff_x = l2b.x - xy.first;
        float diff_y = l2b.y - xy.second;

        Punto l2b_aux(xy.first, xy.second, z);
        Punto l2a_aux(l2a.x - diff_x, l2a.y - diff_y, z);

       //cout << "l2b_aux = {" << l2b_aux.x << "," << l2b_aux.y << "} l2a_aux = {"  << l2a_aux.x << "," << l2a_aux.y << "}";

    }

    Plano(Punto l1a_, Punto l1b_, Punto l2a_, Punto l2b_) : l1a{l1a_}, l1b{l1b_}, l2a{l2a_}, l2b{l2b_} {
        
        //aqui hallo variables para la ecuacion de la recta 3d (l1b, l2b)
        xm = l1b.x;
        ym = l1b.y;
        zm = l1b.z;

        xt = l2b.x - l1b.x;
        yt = l2b.y - l1b.y;
        zt = l2b.z - l1b.z;
        //aqui hallo variables para la ecuacion de la recta 2d (l2b, l2a)
        find_line(l2b, l2a);
    }

    double determinantOfMatrix(double mat[3][3])
    {
        double ans;
        ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
              - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
              + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
        return ans;
    }


    void findSolution(double coeff[3][4], double &xx, double &yy, double &zz)
    {
        // Matrix d using coeff as given in cramer's rule
        double d[3][3] = {
                { coeff[0][0], coeff[0][1], coeff[0][2] },
                { coeff[1][0], coeff[1][1], coeff[1][2] },
                { coeff[2][0], coeff[2][1], coeff[2][2] },
        };
        // Matrix d1 using coeff as given in cramer's rule
        double d1[3][3] = {
                { coeff[0][3], coeff[0][1], coeff[0][2] },
                { coeff[1][3], coeff[1][1], coeff[1][2] },
                { coeff[2][3], coeff[2][1], coeff[2][2] },
        };
        // Matrix d2 using coeff as given in cramer's rule
        double d2[3][3] = {
                { coeff[0][0], coeff[0][3], coeff[0][2] },
                { coeff[1][0], coeff[1][3], coeff[1][2] },
                { coeff[2][0], coeff[2][3], coeff[2][2] },
        };
        // Matrix d3 using coeff as given in cramer's rule
        double d3[3][3] = {
                { coeff[0][0], coeff[0][1], coeff[0][3] },
                { coeff[1][0], coeff[1][1], coeff[1][3] },
                { coeff[2][0], coeff[2][1], coeff[2][3] },
        };

        // Calculating Determinant of Matrices d, d1, d2, d3
        double D = determinantOfMatrix(d);
        double D1 = determinantOfMatrix(d1);
        double D2 = determinantOfMatrix(d2);
        double D3 = determinantOfMatrix(d3);
        /*
        printf("D is : %lf \n", D);
        printf("D1 is : %lf \n", D1);
        printf("D2 is : %lf \n", D2);
        printf("D3 is : %lf \n", D3);
        */
        // Case 1
        if (D != 0) {
            // Coeff have a unique solution. Apply Cramer's Rule
            double x = D1 / D;
            double y = D2 / D;
            double z = D3 / D; // calculating z using cramer's rule
            /*
            printf("Value of x is : %lf\n", x);
            printf("Value of y is : %lf\n", y);
            printf("Value of z is : %lf\n", z);
            */
            xx = x;
            yy = y;
            zz = z;
        }
            // Case 2
        else {
            if (D1 == 0 && D2 == 0 && D3 == 0) {
                // printf("Infinite solutions\n");
            }
            else if (D1 != 0 || D2 != 0 || D3 != 0)
                printf("No solutions\n");
        }
    }
    
    

    bool interseccion(Punto a1, Punto b1, Punto c1, Punto a2, Punto b2, Punto c2, double x_start, double x_end, double y_start, double y_end, double z_start, double z_end){
        //ecuacion plano 1;
        auto p1 = a1-b1;
        auto p2 = a1-c1;
        auto p3 = p1 * p2;
        auto A1 = p3.x;
        auto B1 = p3.y;
        auto C1 = p3.z;

        Punto plano1( A1, B1, C1);

        auto D1 = (A1*a1.x + B1*a1.y + C1*a1.z);

        //cout <<"(" << A1 <<"x) + (" << B1  <<"y) + (" << C1 <<"z) + (" << D1 << ") = 0"<< endl;

        //ecuacion plano 2

        auto g1 = a2-b2;
        auto g2 = a2-c2;
        auto g3 = g1 * g2;
        auto A2 = g3.x;
        auto B2 = g3.y;
        auto C2 = g3.z;

        Punto plano2( A2, B2, C2);

        auto D2 = (A2*a2.x + B2*a2.y + C2*a2.z);

        //cout <<"(" << A2 <<"x) + (" << B2  <<"y) + (" << C2 <<"z) + (" << D2 << ") = 0"<< endl;


        Punto linea = plano1*plano2;

        auto A3 = linea.x;
        auto B3 = linea.y;
        auto C3 = linea.z;


        /*
         * A1*x + B1*y + C1*z = D1
         * A2*x + B2*y + C2*z = D2
         * A3*x + B3*y + C3*z = 0
         */

        double coeff[3][4] = {
                { A1, B1, C1, D1 },
                { A2, B2, C2, D2 },
                { A3, B3, C3, 0 },
        };


        double xi, yi, zi;

        findSolution(coeff, xi,yi,zi);

        for (int x = x_start; x <= x_end ; ++x) {
           /*
              x = x1 + A3 * t
              y = y1 + B3 * t
              z = z1 + C3 * t

              (i - xi) / A3 =  t
           */

           double t = (x-xi) / A3;
           double y = yi + B3 * t;
           double z = zi + C3 * t;

           if( (x >= x_start && x <= x_end) && (y >= y_start && y <= y_end) && (z >= z_start && z <= z_end)){

               //cout << "Si" << endl;
               return true;
           }

        }
        for (int y = y_start; y <= y_end ; ++y) {
            /*
               x = x1 + A3 * t
               y = y1 + B3 * t
               z = z1 + C3 * t

               (y - yi) / B3 =  t
            */

            double t = (y-yi) / B3;
            double x = xi + A3 * t;
            double z = zi + C3 * t;

            if( (x >= x_start && x <= x_end) && (y >= y_start && y <= y_end) && (z >= z_start && z <= z_end)){

                //cout << "Si" << endl;
                return true;
            }

        }

        for (int z = z_start; z <= z_end ; ++z) {
            /*
               x = x1 + A3 * t
               y = y1 + B3 * t
               z = z1 + C3 * t

               (z - zi) / C3 =  t
            */

            double t = (z-zi) / C3;
            double x = xi + A3 * t;
            double y = yi + B3 * t;

            if( (x >= x_start && x <= x_end) && (y >= y_start && y <= y_end) && (z >= z_start && z <= z_end)){

                //cout << "Si" << endl;
                return true;
            }

        }

        //cout << "No" << endl;
        return false;

    }

    vector<Punto> hallar_puntos(Punto a1, Punto b1, Punto c1, Punto a2, Punto b2, Punto c2, int coor, double c_start, double c_end){
        //ecuacion plano 1;
        auto p1 = a1-b1;
        auto p2 = a1-c1;
        auto p3 = p1 * p2;
        auto A1 = p3.x;
        auto B1 = p3.y;
        auto C1 = p3.z;

        Punto plano1( A1, B1, C1);

        auto D1 = (A1*a1.x + B1*a1.y + C1*a1.z);


        auto g1 = a2-b2;
        auto g2 = a2-c2;
        auto g3 = g1 * g2;
        auto A2 = g3.x;
        auto B2 = g3.y;
        auto C2 = g3.z;

        Punto plano2( A2, B2, C2);

        auto D2 = (A2*a2.x + B2*a2.y + C2*a2.z);

        Punto linea = plano1*plano2;

        auto A3 = linea.x;
        auto B3 = linea.y;
        auto C3 = linea.z;

        double coeff[3][4] = {
                { A1, B1, C1, D1 },
                { A2, B2, C2, D2 },
                { A3, B3, C3, 0 },
        };


        double xi, yi, zi;

        findSolution(coeff, xi,yi,zi);
/*
            x = x1 + A3 * t
            y = y1 + B3 * t
            z = z1 + C3 * t
*/
        // if(coor)


    }

    pair<vector<Punto>, string> interseccion_simple(nodo* node){

        if (!node) return make_pair(vector<Punto>(), "");

        double x_s = node->i.x;
        double x_e = node->f.x;
        double y_s = node->i.y;
        double y_e = node->f.y;
        double z_s = node->i.z;
        double z_e = node->f.z;

        string paralelidad;

        if(l2a.y == l1b.y){
            paralelidad = "xz";
        }else if(l2a.x == l1b.x){
            paralelidad = "yz";
        }else if(l2a.z == l1b.z){
            paralelidad = "xy";
        } else {
            cout << "paralelidad desconocida: " << paralelidad << "\n";
        }

        if(paralelidad == "xz"){
            if(l2a.y >= y_s && l2a.y <= y_e){
                Punto p1(x_s, l2a.y, z_e);
                Punto p2(x_e, l2a.y, z_e);
                Punto p3(x_s, l2a.y, z_s);
                Punto p4(x_e, l2a.y, z_s);

                return {{p1,p2,p3,p4}, paralelidad};
            }
            else{
                return make_pair(vector<Punto>(), "");
            }
        }else if (paralelidad == "xy"){
            if(l2a.z >= z_s && l2a.z <= z_e){
                Punto p1(x_s, y_s, l2a.z);
                Punto p2(x_s, y_e, l2a.z);
                Punto p3(x_e, y_s, l2a.z);
                Punto p4(x_e, y_e, l2a.z);

                return {{p1,p2,p3,p4}, paralelidad};
            }
            else{
                return make_pair(vector<Punto>(), "");
            }
        }else if(paralelidad == "yz"){
            if(l2a.x >= x_s && l2a.x <= x_e){
                Punto p1(l2a.x, y_s, z_e);
                Punto p2(l2a.x, y_e, z_e);
                Punto p3(l2a.x, y_s, z_s);
                Punto p4(l2a.x, y_e, z_s);

                return {{p1,p2,p3,p4}, paralelidad};
            }
            else{
                return make_pair(vector<Punto>(), "");
            }
        } else {
            return make_pair(vector<Punto>(), "");
        }
    }


    bool intersects(nodo* node) {

        if (!node) return false;
        // node.i: (xi, yi, zi)
        // node.f: (xf, yf, zf)

        double x_s = node->i.x;
        double x_e = node->f.x;
        double y_s = node->i.y;
        double y_e = node->f.y;
        double z_s = node->i.z;
        double z_e = node->f.z;
    
        Punto esq_inf_izq_del(x_s, y_s, z_s);
        Punto esq_inf_der_del(x_e, y_s, z_s);
        Punto esq_inf_izq_tras(x_s, y_e, z_s);
        Punto esq_inf_der_tras(x_e, y_e, z_s);

        Punto esq_sup_izq_del(x_s, y_s, z_e);
        Punto esq_sup_der_del(x_e, y_s, z_e);
        Punto esq_sup_izq_tras(x_s, y_e, z_e);
        Punto esq_sup_der_tras(x_e, y_e, z_e);

        bool piso = 0, techo = 0, izquierda = 0, derecha = 0, frontal = 0, trasera = 0;

        piso = interseccion(l1a,l1b,l2a, esq_inf_izq_del, esq_inf_der_del, esq_inf_izq_tras, x_s, x_e, y_s, y_e, z_s, z_e);

        techo = interseccion(l1a,l1b,l2a, esq_sup_izq_del, esq_sup_der_del, esq_sup_izq_tras, x_s, x_e, y_s, y_e, z_s, z_e);

        izquierda = interseccion(l1a,l1b,l2a, esq_sup_izq_del, esq_sup_izq_tras, esq_inf_izq_del, x_s, x_e, y_s, y_e, z_s, z_e);

        derecha =  interseccion(l1a,l1b,l2a, esq_sup_der_del, esq_sup_der_tras, esq_inf_der_del, x_s, x_e, y_s, y_e, z_s, z_e);

        frontal =  interseccion(l1a,l1b,l2a, esq_inf_izq_del, esq_inf_der_del, esq_sup_izq_del, x_s, x_e, y_s, y_e, z_s, z_e);

        trasera =  interseccion(l1a,l1b,l2a, esq_inf_izq_tras, esq_inf_der_tras, esq_sup_izq_tras, x_s, x_e, y_s, y_e, z_s, z_e);


        //posibles combinaciones

            //piso,techo,frontal,trasera

            // frontal -> z
            // trasera -> z
            // techo -> y
            // piso -> y


            // frontal, trasera, derecha, izquierda

            // frontal -> x
            // trasera -> x
            // derecha -> y
            // izquierda -> y


            // derecha, izquierda, piso, techo

            // derecha -> z
            // izquierda -> z
            // piso -> x
            // techo -> x

        return( piso || techo || izquierda || derecha || frontal || trasera);
    }

};

// 20 CORTES RANDOM:

// PARALELOS AL PLANO XZ

Punto b1 = Punto(0, 128, 39);
Punto b2 = Punto(511, 128, 39);
Punto b3 = Punto(0, 128, 0);
Punto b4 = Punto(511, 128, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a1 = Punto(0, 255, 39);
Punto a2 = Punto(511, 255, 39);
Punto a3 = Punto(0, 255, 0);
Punto a4 = Punto(511, 255, 0);
// Plano a5 = Plano(p1, p2, p3, p4);

Punto a5 = Punto(0, 383, 39);
Punto a6 = Punto(511, 383, 39);
Punto a7 = Punto(0, 383, 0);
Punto a8 = Punto(511, 383, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a9 = Punto(0, 200, 39);
Punto a10 = Punto(511, 200, 39);
Punto a11 = Punto(0, 200, 0);
Punto a12 = Punto(511, 200, 0);
// Plano a13 = Plano(p1, p2, p3, p4);

Punto a13 = Punto(0, 400, 39);
Punto a14 = Punto(511, 400, 39);
Punto a15 = Punto(0, 400, 0);
Punto a16 = Punto(511, 400, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a17 = Punto(0, 100, 39);
Punto a18 = Punto(511, 100, 39);
Punto a19 = Punto(0, 100, 0);
Punto a20 = Punto(511, 100, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a21 = Punto(0, 50, 39);
Punto a22 = Punto(511, 50, 39);
Punto a23 = Punto(0, 50, 0);
Punto a24 = Punto(511, 50, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// PARALELOS AL PLANO YZ

Punto a25 = Punto(255, 0, 39);
Punto a26 = Punto(255, 511, 39);
Punto a27 = Punto(255, 0, 0);
Punto a28 = Punto(255, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a29 = Punto(128, 0, 39);
Punto a30 = Punto(128, 511, 39);
Punto a31 = Punto(128, 0, 0);
Punto a32 = Punto(128, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a33 = Punto(383, 0, 39);
Punto a34 = Punto(383, 511, 39);
Punto a35 = Punto(383, 0, 0);
Punto a36 = Punto(383, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a37 = Punto(200, 0, 39);
Punto a38 = Punto(200, 511, 39);
Punto a39 = Punto(200, 0, 0);
Punto a40 = Punto(200, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a41 = Punto(400, 0, 39);
Punto a42 = Punto(400, 511, 39);
Punto a43 = Punto(400, 0, 0);
Punto a44 = Punto(400, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a45 = Punto(100, 0, 39);
Punto a46 = Punto(100, 511, 39);
Punto a47 = Punto(100, 0, 0);
Punto a48 = Punto(100, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a49 = Punto(55, 0, 39);
Punto a50 = Punto(55, 511, 39);
Punto a51 = Punto(55, 0, 0);
Punto a52 = Punto(55, 511, 0);
// Plano plano = Plano(p1, p2, p3, p4);

// PARALELOS AL PLANO XY

Punto a53 = Punto(0, 0, 39);
Punto a54 = Punto(0, 511, 30);
Punto a55 = Punto(511, 0, 39);
Punto a56 = Punto(511, 511, 39);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a57 = Punto(0, 0, 10);
Punto a58 = Punto(0, 511, 10);
Punto a59 = Punto(511, 0, 10);
Punto a60 = Punto(511, 511, 10);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a61 = Punto(0, 0, 5);
Punto a62 = Punto(0, 511, 5);
Punto a63 = Punto(511, 0, 5);
Punto a64 = Punto(511, 511, 5);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a65 = Punto(0, 0, 15);
Punto a66 = Punto(0, 511, 15);
Punto a67 = Punto(511, 0, 15);
Punto a68 = Punto(511, 511, 15);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a69 = Punto(0, 0, 20);
Punto a70 = Punto(0, 511, 20);
Punto a71 = Punto(511, 0, 20);
Punto a72 = Punto(511, 511, 20);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a73 = Punto(0, 0, 25);
Punto a74 = Punto(0, 511, 25);
Punto a75 = Punto(511, 0, 25);
Punto a76 = Punto(511, 511, 25);
// Plano plano = Plano(p1, p2, p3, p4);

vector< vector<Punto> > puntos = {
    {b1, b2, b3, b4},
    {a1, a2, a3, a4},
    {a5, a6, a7, a8},
    {a9, a10, a11, a12},
    {a13, a14, a15, a16},
    {a17, a18, a19, a20},
    {a21, a22, a23, a24},
    {a25, a26, a27, a28},
    {a29, a30, a31, a32},
    {a33, a34, a35, a36},
    {a37, a38, a39, a40},
    {a41, a42, a43, a44},
    {a45, a46, a47, a48},
    {a49, a50, a51, a52},
    {a53, a54, a55, a56},
    {a57, a58, a59, a60},
    {a61, a62, a63, a64},
    {a65, a66, a67, a68},
    {a69, a70, a71, a72},
    {a73, a74, a75, a76}
};

#endif