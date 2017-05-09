#include <iostream>

#include "vec.h"
#include <math.h>
#include <limits>
#include <fstream>
#include <iomanip>

const double h = (0.0000001);
const double break_con = 0.0001;
#define MAX_STEPS 50



#define USE_F
//#define USE_G


#ifdef USE_F
#define func_call(a) f(a)
#define func_call_name f
#define func_call_name_string "f"
#endif

#ifdef USE_G
#define func_call(a) g(a)
#define func_call_name g
#define func_call_name_string "g"
#endif


//sin(x+y2)+y3 −6y2 +9y
#ifdef USE_F
double f(vec _x){
    double x = _x[0];
    double y = _x[1];
return sin(x + pow(y,2.0)) + pow(y,3.0) - (6.0*pow(y,2.0)) + (9.0*y);
}
#endif
//2x21 − 2x1x2 + x2 + x23 − 2x1 − 4x3,
#ifdef USE_G
double g(vec _x){
    double x1 = _x[0];
    double x2 = _x[1];
    double x3 = _x[2];
    return -((2*pow(x1,2.0))  -(2.0*x1*x2)  +pow(x2,2.0) +pow(x3,2.0) -(2.0*x1) -(4.0*x3));
}
#endif




#define OUT_FILE_PATH "output_" func_call_name_string ".txt"





vec gradient(vec _x, double (*funktion)(vec x)){
vec res(_x.gsize());

    for (int i = 0; i < res.gsize(); ++i) {
	   vec withstep = _x;
	   withstep.at(i)= withstep.at(i)+h;
	   res.at(i) = ((func_call(withstep) -func_call(_x) )/h);
    }
return res;
}


bool equalityTestDouble(double oldVector,double newVektor){
   return (fabs(newVektor - oldVector) < std::numeric_limits<double>::epsilon());
};


int main() {
using namespace std;
    //INIT FILE STUFF
    ofstream file;
    file.open(OUT_FILE_PATH,fstream::out);
    if(file.fail()){
        std::cout << "FILE OPEN FAILED" << std::endl;
        return -1;
    }






    double schritt_f = 1.0;

#ifdef USE_F
    vec xf("dd", 3.0,2.0);
    schritt_f = 1.0f;
#endif
#ifdef USE_G
    vec xf("ddd", 0.0,0.0,0.0);
    schritt_f = 0.1;
#endif


   
   double func_val = 0.0;
   vec xfn=xf;
   vec res_grad;

    for (int i = 0; i <= MAX_STEPS; ++i) {

        file << "------ STEP " << (i) << "------"<<std::endl;
        file << "x = ";xf.print(&file);

        file << "schritt " << schritt_f << std::endl;

        func_val = func_call(xf);
        file << "f(x)=" << func_val << std::endl;

	    res_grad = gradient(xf,func_call_name);

        file << "grad func(x)";
        res_grad.print(&file);

        file << "| grad func(x) | = " << res_grad.length() << std::endl;

        //HERE BREAK COND CHECK
        if(fabs(res_grad.length()) <= break_con){break;}
        

        //calc new x
        vec tmp_001 = res_grad*schritt_f;
	    xfn = xf +tmp_001;

        file << "x_neu = ";
        xfn.print(&file);
	   double newf = func_call(xfn);
        file << "func(xneu)=" << newf ;
   

        if(func_call(xf) < func_call(xfn)){
            file << "Teste mit doppelter schrittweite" << std::endl;
            vec tmp_002 = gradient(xf,func_call_name)*(2.0*schritt_f);
            vec xtest = xf + tmp_002;
            xtest.print(&file);
            file << "f(xtest)" << func_call(xtest)<<std::endl;
            if(func_call(xtest) > func_call(xfn)){
             schritt_f *= 2.0;
                file << "verdopple schrittweite" << std::endl;
			   xf = xtest;
            }else{
                file << "behalte alte schrittweite" << std::endl;
                xf = xfn; //setzt neues x
            }
        }else {
            file << "enter habierungsloop:" << schritt_f << std::endl;
            //solange xneu > xalt
        while(func_call(xfn) < func_call(xf) || equalityTestDouble(func_call(xf),func_call(xfn)) ){
            schritt_f *= 0.5;
            file << "halbiere schrittweite :" << schritt_f << std::endl;
            tmp_001 = res_grad*schritt_f;
		     xfn = xf +tmp_001;
        }
            file << "neue x fach halbierte schrittweite gefunden  exit loop :" << schritt_f << std::endl;
            xf=xfn;
		}
        file << std::endl <<std::endl;
    }

    file.close();
    return 0;
}