#include <iostream>

#include "vec.h"
#include <math.h>
//#define VEC_UNITTEST


const double h = 0.0000001;
const double break_con = 0.0001;
#define MAX_STEPS 50


#define USE_F
//#define USE_G


#ifdef USE_F
#define func_call(a) f(a)
#define func_call_name f
#endif

#ifdef USE_G
#define func_call(a) g(a)
#define func_call_name g
#endif



//sin(x+y2)+y3 −6y2 +9y
double f(vec _x){
    double x = _x[0];
    double y = _x[1];
return sin(x + pow(y,2.0)) + pow(y,3.0) - (6.0*pow(y,2.0)) + (9.0*y);
}

//2x21 − 2x1x2 + x2 + x23 − 2x1 − 4x3,
double g(vec _x){
    double x1 = _x[0];
    double x2 = _x[1];
    double x3 = _x[2];
    return -((2*pow(x1,2.0))  -(2.0*x1*x2)  +pow(x2,2.0) +pow(x3,2.0) -(2.0*x1) -(4.0*x3));
}



vec gradient(vec _x, double (*funktion)(vec x)){
vec res(_x.gsize());
//TODO AUF 2
    for (int i = 0; i < res.gsize(); ++i) {
        res.at(i) = (f() -f(_x) )/h;
    }

return res;
}


int main() {
    double schritt_f = 1.0;

#ifdef USE_F
    vec xf("dd", 3.0,2.0);
    schritt_f = 1.0f;
#endif
#ifdef USE_G
    vec xf("ddD", 0.0,0.0,0.0);
    schritt_f = 0.1;
#endif



    double func_val = 0.0;


    for (int i = 0; i < MAX_STEPS; ++i) {

        std::cout << "------ STEP " << (i+1) << "------"<<std::endl;
        std::cout << "x = ";xf.print();

        std::cout << "schritt " << schritt_f << std::endl;

        func_val = func_call(xf);
        std::cout << "f(x)" << func_val << std::endl;

        vec res_grad = gradient(xf,func_call_name);

        std::cout << "grad func(x)";
        res_grad.print();

        std::cout << "| grad func(x) | = " << res_grad.length() << std::endl;


        if(fabs(res_grad.length()) <= break_con){break;}

        //calc new x
        vec tmp_001 = res_grad*schritt_f;
        vec xfn = xf +tmp_001;

        std::cout << "x_neu = ";
        xfn.print();
        std::cout << "func(xneu)=" << func_call(xfn);

        if(func_call(xf) > func_call(xfn)){
            std::cout << "Teste mit doppelter schrittweite" << std::endl;
            vec tmp_002 = gradient(xf,func_call_name)*(2*schritt_f);
            vec xtest = xf + tmp_002;
            xtest.print();
            std::cout << "f(xtest)" << func_call(xtest)<<std::endl;
            if(func_call(xtest) > func_call(xfn)){
             schritt_f += 2.0f;
                std::cout << "verdopple schrittweite" << std::endl;
            }else{
                std::cout << "behalte alte schrittweite" << std::endl;
                xf = xfn; //setzt neues x
            }

        }else if(func_call(xfn) <= func_call(xf)){
//TODO AUF 3


        }

    break;

    }






    return 0;
}