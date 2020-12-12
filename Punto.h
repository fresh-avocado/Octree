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

    Punto operator/ (const int& n) {
        Punto answer;
        answer.x = (this->x/n);
        answer.y = (this->y/n);
        answer.z = (this->z/n);
        return answer;
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
        float t = (z - zm)/zt;

        float x = xm + (xt*t);
        float y = ym + (yt*t);


        return {x,y};
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

        rxm = (l2b.y - l2a.y) / (l2b.x - l2a.x);
    }

    

};


#endif