//
// Created by root on 6/16/17.
//

#include "complex.h"

complex::complex(const complex& _other){
    re = _other.re;
    im = _other.im;
}
complex::complex(const double _re,const double _im){
    re = _re;
    im = _im;
}
complex::complex(const float _re,const float _im){
    re = (double)_re;
    im = (double)_im;
}

complex::complex(double _phi){
    double r = 1.0f;
    re = r*cos(_phi);
    im = r*sin(_phi);
}

double complex::get_re(){
    return re;
}
double complex::get_im(){
    return im;
}

void complex::pint() {
    std::cout << "z=" << get_re() << "";
    if(get_im() >= 0.0f){
        std::cout << "+";
    }
    std::cout << get_im() << "i"<< std::endl;
}

complex complex::operator+(complex _other){
    return  complex(this->get_re() + _other.get_re(),this->get_im()+_other.get_im());
}
complex complex::operator*(complex _other){

    double tmp_re1 = this->get_re() * _other.get_re(); //re*re
    double tmp_re2 = this->get_im() * _other.get_im() * -1.0f; // bi * bi * -1 wegen i2 = -1

    double tmp_im1 =this->get_re() * _other.get_im();
    double tmp_im2 = this->get_im() * _other.get_re();
    return complex(tmp_re1 + tmp_re2,tmp_im1 + tmp_im2);
}

complex complex::operator*(double _other){
   return complex(this->get_re(),this->get_im())*complex(_other,0.0);
}

double complex::abs(){
    return  sqrt((pow(re,2.0) + pow(im,2.0)));
}