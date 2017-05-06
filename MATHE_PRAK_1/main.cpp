#include <iostream>

#include "vec.h"

//#define VEC_UNITTEST



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




    return 0;
}