//
// Created by Marcel Ochsendorf on 06.05.17.
//

#ifndef MATHE_PRAK_2_MAT_H
#define MATHE_PRAK_2_MAT_H


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include "vec.h"

#define MAT_WARNING

class mat {

public:
    mat(const int _dim_w, const int _dim_h);
    vec operator*(vec& x);
    mat invers();
    void set_val(const int _w, const int _h, const double _val);
    double get_val(const int _w, const int _h);

    int dim_w;
    int dim_h;
private:
    std::vector<vec> data_holder_mat;
};
#endif //MATHE_PRAK_2_MAT_H
