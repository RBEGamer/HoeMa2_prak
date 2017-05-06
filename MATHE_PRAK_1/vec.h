//
// Created by Marcel Ochsendorf on 06.05.17.
//

#ifndef MATHE_PRAK_1_VEC_H
#define MATHE_PRAK_1_VEC_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdarg.h>


#define VEC_TYPE double
#define VEC_INIT_SITE 15
#define VEC_INIT_VALUE 0.0


#define VEC_WARNING
class vec {


public:
    vec(const char* _fmt,...);
    vec(const u_int16_t _size);
    void print();
    int set_value(u_int16_t _pos, const VEC_TYPE _val);
    int set_row_values(const char* _fmt,...);
    VEC_TYPE get_val(u_int16_t _pos);
    std::vector<VEC_TYPE> get_val_row();
    VEC_TYPE operator[] (u_int16_t _pos);
    VEC_TYPE& at(u_int16_t _pos);
    vec operator+ (vec& _other);
    vec operator*(VEC_TYPE _lam);
    u_int16_t gsize();
private:
    u_int16_t  size;
    std::vector<VEC_TYPE> data_storage;
};
#endif //MATHE_PRAK_1_VEC_H
