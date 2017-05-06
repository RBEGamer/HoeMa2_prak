#include <iostream>

#include "vec.h"
#include <math.h>
//#define VEC_UNITTEST


const double h = 0.0000001;




//sin(x+y2)+y3 −6y2 +9y
double f(vec _x){
    double x = _x[0];
    double y = _x[1];
return sin(x + pow(y,2.0)) + pow(y,3.0) - (6*pow(y,2.0)) + (9*y);
}

//2x21 − 2x1x2 + x2 + x23 − 2x1 − 4x3,
double g(vec _x){
    double x1 = _x[0];
    double x2 = _x[1];
    double x3 = _x[2];
    return -((2*pow(x1,2.0))  -(2*x1*x2)  +pow(x2,2.0) +pow(x3,2.0) -(2*x1) -(4*x3));
}



vec gradient(vec _x, double (*funktion)(vec x)){


}


int main() {
#ifdef VEC_UNITTEST
    std::cout << "starting vec unit test" << std::endl;
    vec va_vec_a(3);
    va_vec_a.set_value(0,1.0);
    va_vec_a.set_value(1,2.0);
    va_vec_a.set_value(2,3.0);
    va_vec_a.print();
   vec res1 = va_vec_a * 2.0;
    res1.print();
    vec res2 = res1 + res1;
    res2.print();
#endif

    vec start_f("dd", 2.0,3.0);
    vec start_g("ddd", 0.0,0.0, 0.0);
    double schritt_f = 1.0;
    double schritt_g = 0.1;









    
    return 0;
}