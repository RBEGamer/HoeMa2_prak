//
// Created by Marcel Ochsendorf on 06.05.17.
//

#ifndef MATHE_PRAK_1_VEC_H
#define MATHE_PRAK_1_VEC_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>


#define VEC_INIT_SITE 15
#define VEC_INIT_VALUE 0.0


#define VEC_WARNING
class vec {


public:
    vec(const char* _fmt,...);
    vec(const u_int16_t _size);
	vec(void);
    void print();
    int set_value(u_int16_t _pos, const double _val);
    int set_row_values(const char* _fmt,...);
    double get_val(u_int16_t _pos);
    std::vector<double> get_val_row();
    double operator[] (u_int16_t _pos);
    double& at(u_int16_t _pos);
    vec operator+ (vec& _other);
    vec operator*(double _lam);
    u_int16_t gsize();
    double length();
private:
    u_int16_t  size;
    std::vector<double> data_storage;
};
#endif //MATHE_PRAK_1_VEC_H
