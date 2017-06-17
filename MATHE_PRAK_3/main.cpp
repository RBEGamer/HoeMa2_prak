#include <iostream>
#include "CMyVektor.h"
#include "CDGLSolver.h"
#include "CMyVektor.h"

#define FUNKTIONSDIMENSION 2


vec functionDGLSystem(vec y,double x){
   vec result(FUNKTIONSDIMENSION) ;
   
   double y1 = y[0];
   double y2 = y[1];
   result.at(0)=2*y2-x*y1;
   result.at(1)=y1*y2 - 2*pow(x,3.0);
   
   return result;
}



double functionHigherDGL(vec y,double x){
 
   double y0 = y[0];
   double ya = y[1];
   double yaa = y[2];
   
   return 2*x*ya*yaa + 2*pow(y0,2.0)*ya;
}






int qs(int z){
    if(z >= 10){
        return  (z%10) + qs(z/10);

    }
    return z;
}









int main() {


//    std::cout << "QS(254) = " << qs(254) << std::endl;

   vec (*fpointerSystem)(vec y, double x) = &functionDGLSystem;
   double (*fpointerHigherDGL)(vec y, double x) = &functionHigherDGL;
   
   CDGLSolver SystemSolver(fpointerSystem);

   CDGLSolver HigherDGLSolver(fpointerHigherDGL);
   
   double xStartDGLSystem = 0.0;
   double xStartHigherDGL = 1.0;
   double xEnd = 2.0;
   
   
   vec startPunktDGLSystem(2);
   startPunktDGLSystem.at(0) = 0;
   startPunktDGLSystem.at(1) = 1;
   
   vec startPunktHigherDGL(3);
   startPunktHigherDGL.at(0) = 1;
   startPunktHigherDGL.at(1) = -1;
   startPunktHigherDGL.at(2) = 2;
   
   SystemSolver.doEuler(xStartDGLSystem,xEnd,100,startPunktDGLSystem);
   SystemSolver.doHeun(xStartDGLSystem,xEnd,100,startPunktDGLSystem);
   
   HigherDGLSolver.doEuler(xStartHigherDGL,xEnd,10,startPunktHigherDGL);
   HigherDGLSolver.doHeun(xStartHigherDGL,xEnd,10,startPunktHigherDGL);
   
   HigherDGLSolver.doEuler(xStartHigherDGL,xEnd,100,startPunktHigherDGL);
   HigherDGLSolver.doHeun(xStartHigherDGL,xEnd,100,startPunktHigherDGL);
   
   HigherDGLSolver.doEuler(xStartHigherDGL,xEnd,1000,startPunktHigherDGL);
   HigherDGLSolver.doHeun(xStartHigherDGL,xEnd,1000,startPunktHigherDGL);
   
   HigherDGLSolver.doEuler(xStartHigherDGL,xEnd,10000,startPunktHigherDGL);
   HigherDGLSolver.doHeun(xStartHigherDGL,xEnd,10000,startPunktHigherDGL);
   
}