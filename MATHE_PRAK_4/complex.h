//
// Created by root on 6/16/17.
//

#ifndef MATHE_PRAK_4_COMPLEX_H
#define MATHE_PRAK_4_COMPLEX_H

#include <math.h>
#include <iostream>
class complex {
    double re;
    double im;
public:
    complex(const double _re, const double _im);
    complex(const float _re, const float _im);
    complex(const double _phi);
    complex(const complex& _other);
    double get_re();
    double get_im();
    void pint();
    complex operator+(complex _other);
    complex operator*(complex _other);
    complex operator*(const double _other);
    double abs();






};


#endif //MATHE_PRAK_4_COMPLEX_H
