//
// Created by root on 6/16/17.
//

#include "complex.h"

complex::complex() {
    re = 0;
    im = 0;
}
complex::complex(const  complex& _other){
    re = _other.re;
    im = _other.im;
}
complex::complex(const double _re,const double _im){
    re = _re;
    im = _im;
}


complex::complex(const double _phi){
    double r = 1.0f;
    re = r*cos(_phi);
    im = r*sin(_phi);
}

double complex::get_re(){
#ifdef COMPLEX_ADV_CHECK
    if(this == nullptr){
        throw ;
    }
#endif
    return this->re;
}
double complex::get_im(){
#ifdef COMPLEX_ADV_CHECK
    if(this == nullptr){
        throw ;
    }
#endif
    return this->im;
}

void complex::pint() {
    std::cout << "z=" << get_re() << "";
    if(get_im() >= 0.0f){
        std::cout << "+";
    }
    std::cout << get_im() << "i"<< std::endl;
}

complex complex::operator+(complex _other){
    return  complex((const double)(get_re() + _other.get_re()),(const double)(get_im()+_other.get_im()));
}
complex complex::operator-(complex _other){
    return  complex((const double)(get_re() - _other.get_re()),(const double)(get_im()-_other.get_im()));
}
complex complex::operator*(complex _other){

    double tmp_re1 = get_re() * _other.get_re(); //re*re
    double tmp_re2 = get_im() * _other.get_im() * -1.0f; // bi * bi * -1 wegen i2 = -1

    double tmp_im1 =get_re() * _other.get_im();
    double tmp_im2 = get_im() * _other.get_re();
    return complex(tmp_re1 + tmp_re2,tmp_im1 + tmp_im2);
}

complex complex::operator*(double _other){
   return complex(get_re(),get_im())*complex(_other,0.0);
}

double complex::abs(){
    return  sqrt((pow(get_re(),2.0) + pow(get_im(),2.0)));
}