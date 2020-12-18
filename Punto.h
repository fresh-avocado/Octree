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

    // Punto operator/ (const int& n) {
    //     Punto answer;
    //     answer.x = (int)(this->x/n);
    //     answer.y = (int)(this->y/n);
    //     answer.z = (int)(this->z/n);
    //     return answer;
    // }

    friend bool operator== (const Punto& lhs, const Punto& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;        
    }

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



    

};


#endif