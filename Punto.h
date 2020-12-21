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

    pair<double ,double> find_line(Punto A, Punto B) {
        double a1 = B.y - A.y;
        double b1 = A.x - B.x;
        double c1 = a1*A.x + b1*A.y;
        if (round(b1) == 0) {
            return {-9999, A.x};
        }
        rxm = (a1*-1)/b1;
        b = c1/b1;
        //cout << rxm << "x + " << b;
        return {rxm, b};
    }

    pair<double,double> find_line_given_z( double z) {

        auto xy = xy_with_given_z(z);

        double diff_x = l2b.x - xy.first;
        double diff_y = l2b.y - xy.second;

        Punto l2b_aux(xy.first, xy.second, z);
        Punto l2a_aux(l2a.x - diff_x, l2a.y - diff_y, z);

        return find_line(l2b_aux, l2a_aux);

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

    /*
        
    */
    
    

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

        //hallo la resolucion de la ecuacion de 3 variables para ver en que sitio se intersecan los planos

        findSolution(coeff, xi,yi,zi);

        //aqui verifico para cada rango del cubo, si es que existe un punto dada una coordenada fija, dentro del cubo con dicha línea de intersección
        //si eso es verdad, hemos encontrado una intersección.
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
            // cout << "paralelidad desconocida: " << paralelidad << "\n";
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

    /* Codigo fallido para hallar los cortes inclinados y poder obtener los puntos de intersección

    bool intersects(double x_start, double x_end,
                    double y_start, double y_end, double z_start, double z_end){


        Punto esq_inf_izq_del(x_start, y_start, z_start);
        Punto esq_inf_der_del(x_end, y_start, z_start);
        Punto esq_inf_izq_tras(x_start, y_end, z_start);
        Punto esq_inf_der_tras(x_end, y_end, z_start);


        Punto esq_sup_izq_del(x_start, y_start, z_end);
        Punto esq_sup_izq_tras(x_start, y_end, z_end);
        Punto esq_sup_der_del(x_end, y_start, z_end);
        Punto esq_sup_der_tras(x_end, y_end, z_end);



        bool frontal, trasera, piso, techo, izquierda, derecha;
        vector<pair<double, double>> eq_frontal, eq_trasera, eq_piso, eq_techo, eq_izquierda, eq_derecha;
        vector<pair<vector<pair<double, double>>, string>> ecuaciones;

        //verifico interseccion para cada una de las caras del cubo actual

        frontal = interseccion(l1a,l1b,l2a, esq_inf_der_del, esq_inf_izq_del, esq_sup_der_del, x_start, x_end, y_start, y_end, z_start, z_end,eq_frontal, "frontal");
        trasera = interseccion(l1a,l1b,l2a, esq_inf_der_tras, esq_inf_izq_tras, esq_sup_der_tras, x_start, x_end, y_start, y_end, z_start, z_end,eq_trasera, "trasera");
        piso = interseccion(l1a,l1b,l2a, esq_inf_der_tras, esq_inf_izq_tras, esq_inf_der_del, x_start, x_end, y_start, y_end, z_start, z_end,eq_piso, "piso");
        techo = interseccion(l1a,l1b,l2a, esq_sup_der_tras, esq_sup_izq_tras, esq_sup_der_del, x_start, x_end, y_start, y_end, z_start, z_end,eq_techo, "techo");
        izquierda = interseccion(l1a,l1b,l2a, esq_sup_izq_tras, esq_inf_izq_tras, esq_sup_izq_del, x_start, x_end, y_start, y_end, z_start, z_end,eq_izquierda, "izquierda");
        derecha = interseccion(l1a,l1b,l2a, esq_sup_der_tras, esq_inf_der_tras, esq_sup_der_del, x_start, x_end, y_start, y_end, z_start, z_end,eq_derecha, "derecha");

        if(frontal) ecuaciones.push_back({eq_frontal,"frontal"});
        if(trasera) ecuaciones.push_back({eq_trasera,"trasera"});
        if(piso) ecuaciones.push_back({eq_piso,"piso"});
        if(techo) ecuaciones.push_back({eq_techo,"techo"});
        if(izquierda) ecuaciones.push_back({eq_izquierda,"izquierda"});
        if(derecha) ecuaciones.push_back({eq_derecha,"derecha"});
        if(derecha) {cout << "aaaaa" << endl;}




        bool marcados[10][10];

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                marcados[i][j] = 0;
            }
        }


        cout << endl;

//en este doble for hallo las lineas de interseccion que se intersecan entre si para poder hallar un punto valido

        for(auto it: ecuaciones){

            for(auto at: ecuaciones){

                if(it == at){
                    continue;
                }else{

                    string cara1, cara2;

                    cara1 = it.second;
                    cara2 = at.second;
                    int cc1, cc2;

//asigno un valor numerico a la representacion de cada cara

                    if(cara1 == "frontal") cc1 = 1;
                    if(cara1 == "trasera") cc1 = 2;
                    if(cara1 == "piso") cc1 = 3;
                    if(cara1 == "techo") cc1 = 4;
                    if(cara1 == "izquierda") cc1 = 5;
                    if(cara1 == "derecha") cc1 = 6;

                    if(cara2 == "frontal") cc2 = 1;
                    if(cara2 == "trasera") cc2 = 2;
                    if(cara2 == "piso") cc2 = 3;
                    if(cara2 == "techo") cc2 = 4;
                    if(cara2 == "izquierda") cc2 = 5;
                    if(cara2 == "derecha") cc2 = 6;



                    if(marcados[cc1][cc2] || marcados[cc2][cc1]){
                       continue;
                    }

        //marco la combinacion de caras valida para sacar los puntos

                    marcados[cc1][cc2] = 1;
                    marcados[cc2][cc1] = 1;
                    
                    double x1, x2, x3, x4, x5, x6;
                    double a1, a2, a3, a4, a5, a6;

                    // describo las variables de las funciones parametricas de las lineas de interseccion a analizar

                    x1 = it.first[0].first; a1 = it.first[0].second; // x1

                    x2 = it.first[1].first; a2 = it.first[1].second; // y1

                    x3 = it.first[2].first; a3 = it.first[2].second; // z1

                    x4 = at.first[0].first; a4 = at.first[0].second; // x2

                    x5 = at.first[1].first; a5 = at.first[1].second; // y2

                    x6 = at.first[2].first; a6 = at.first[2].second; // z2
                    
                    cout << endl;
                    cout << "x = " << x1 << " + " << a1 << "*t" << endl;
                    cout << "y = " << x2 << " + " << a2 << "*t" << endl;
                    cout << "z = " << x3 << " + " << a3 << "*t" << endl;
                    cout << endl;
                    cout << "x = " << x4 << " + " << a4 << "*t" << endl;
                    cout << "y = " << x5 << " + " << a5 << "*t" << endl;
                    cout << "z = " << x6 << " + " << a6 << "*t" << endl;
                    cout << endl;
                    
                    //resuelvo un sistema de ecuaciones para hallar el punto de interseccion entre las lineas R3

                    double res_x, res_y;
                    bool possible = true;
                    if ((a1 * (a5*-1)) - ((a4*-1) * a2) == 0){
                        possible = false;
                    }
                    else{
                        res_x = ((( x4-x1)*(a5*-1)) - ((a4*-1)*(x5-x2)))/((a1*(a5*-1))-((a4*-1)*a2));
                        res_y = ((a1*(x5-x2)) - ((x4-x1)*a2)) / ((a1*(a5*-1)) - ((a4*-1)*a2));
                        //cout << "x=" << res_x << " y=" << res_y << endl;
                    }


                    if(!possible){
                        continue;
                    }

                    //termino de hallar la funcion 

                    double z1 = a3*res_x + (a6*-1)*res_y;
                    double z2 = x6-x3;

                   // cout << z1 << " " << z2 << endl;

                    double finalx, finaly, finalz;

                    //hallo las coordenadas faltantes con el alfa y beta correspondiente

                    finalx = x1 + a1*res_x;
                    finaly = x2 + a2*res_x;

                    finalz = x3 + a3*res_x;
                    //este es el punto de interseccion de las lineas 

                    cout << "__________" << endl;
                    cout << cara1 << " y " << cara2 << endl;
                    cout << "x=" << (finalx) << " y=" << (finaly) << " z=" << (finalz) <<  endl;
                    cout << "__________" << endl;
                }
            }
        }


     //   cout << endl;


        // frontal = interseccion( );


    }
    bool findpuntos(Punto a1, Punto b1, Punto c1, Punto a2, Punto b2, Punto c2, int coor, double c_start, double c_end) {
        //ecuacion plano 1;
        auto p1 = a1 - b1;
        auto p2 = a1 - c1;
        auto p3 = p1 * p2;
        auto A1 = p3.x;
        auto B1 = p3.y;
        auto C1 = p3.z;
        Punto plano1(A1, B1, C1);
        auto D1 = (A1 * a1.x + B1 * a1.y + C1 * a1.z);
        auto g1 = a2 - b2;
        auto g2 = a2 - c2;
        auto g3 = g1 * g2;
        auto A2 = g3.x;
        auto B2 = g3.y;
        auto C2 = g3.z;
        Punto plano2(A2, B2, C2);
        auto D2 = (A2 * a2.x + B2 * a2.y + C2 * a2.z);
        Punto linea = plano1 * plano2;
        auto A3 = linea.x;
        auto B3 = linea.y;
        auto C3 = linea.z;
        
        //A1*x + B1*y + C1*z = D1
        // A2*x + B2*y + C2*z = D2
        // A3*x + B3*y + C3*z = 0
         
        double coeff[3][4] = {{A1, B1, C1, D1},{A2, B2, C2, D2},{A3, B3, C3, 0},};
        double xi, yi, zi;
        findSolution(coeff, xi, yi, zi);

    }

    */

};

// 20 CORTES RANDOM:

// PARALELOS AL PLANO XZ

Punto b1 = Punto(0, 128, 39);
Punto b2 = Punto(511, 128, 39);
Punto b3 = Punto(0, 128, 0);
Punto b4 = Punto(511, 128, 0);
// Plano plano = Plano(p1, p2, p3, p4);

Punto a1 = Punto(0, 100, 39);
Punto a2 = Punto(511, 100, 39);
Punto a3 = Punto(0, 100, 0);
Punto a4 = Punto(511, 100, 0);

Punto a5 = Punto(0, 50, 39);
Punto a6 = Punto(511, 50, 39);
Punto a7 = Punto(0, 50, 0);
Punto a8 = Punto(511, 50, 0);

Punto a9 = Punto(0, 300, 39);
Punto a10 = Punto(511, 300, 39);
Punto a11 = Punto(0, 300, 0);
Punto a12 = Punto(511, 300, 0);

Punto a13 = Punto(0, 400, 39);
Punto a14 = Punto(511, 400, 39);
Punto a15 = Punto(0, 400, 0);
Punto a16 = Punto(511, 400, 0);

Punto a17 = Punto(0, 500, 39);
Punto a18 = Punto(511, 500, 39);
Punto a19 = Punto(0, 500, 0);
Punto a20 = Punto(511, 500, 0);

Punto a21 = Punto(0, 255, 39);
Punto a22 = Punto(511, 255, 39);
Punto a23 = Punto(0, 255, 0);
Punto a24 = Punto(511, 255, 0);

// Punto a1(511, 0, 19);
// Punto a2(0, 0, 19);
// Punto a3(511, 511, (int) 39.0/1.5);
// Punto a4(0, 511, (int) 39.0/1.5);

// Punto a5(0,400,38);
// Punto a6(511,400,38);
// Punto a7(0,0,0);
// Punto a8(511,0,0);

// Punto a9(300,0,38);
// Punto a10(300,511,38);
// Punto a11(50,0,0);
// Punto a12(50,511,0);

// Punto a13(0,250,38);
// Punto a14(511,250,38);
// Punto a15(0,50,0);
// Punto a16(511,50,0);

// Punto a17(0,250,38);
// Punto a18(511,250,38);
// Punto a19(0,100,0);
// Punto a20(511,100,0);

// Punto a21(0,511,15);
// Punto a22(0,0,15);
// Punto a23(500,511,0);
// Punto a24(500,0,0);

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

Punto c1(511, 0, 19);
Punto c2(0, 0, 19);
Punto c3(511, 511, (int) 39.0/1.5);
Punto c4(0, 511, (int) 39.0/1.5);

Punto c5(0,400,38);
Punto c6(511,400,38);
Punto c7(0,0,0);
Punto c8(511,0,0);

Punto c9(300,0,38);
Punto c10(300,511,38);
Punto c11(50,0,0);
Punto c12(50,511,0);

Punto c13(0,250,38);
Punto c14(511,250,38);
Punto c15(0,50,0);
Punto c16(511,50,0);

Punto c17(0,250,38);
Punto c18(511,250,38);
Punto c19(0,100,0);
Punto c20(511,100,0);

Punto c21(0,511,15);
Punto c22(0,0,15);
Punto c23(500,511,0);
Punto c24(500,0,0);

vector< vector<Punto> > planosInclinados = {
    {c1, c2, c3, c4},
    {c5, c6, c7, c8},
    {c9, c10, c11, c12},
    {c13, c14, c15, c16},
    {c17, c18, c19, c20},
    {c21, c22, c23, c24}
};

#endif