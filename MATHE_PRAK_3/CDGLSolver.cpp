//
// Created by henn on 05.06.17.
//

#include "CDGLSolver.h"

vec CDGLSolver::Ableitungen(vec y, double x) {
   
   if (this->isDGLSystem) {
	  vec result = this->Element_f_DGL_System(y,x);
	  return result;
   }
   
   else {
	  // Transformation in ein DGL System
   
	  double y0 = y[0];
	  double y1 = y[1];
	  double y2 = y[2];
	  
	  vec result(3);
   
	  result.at(0) = y1;
	  result.at(1) = y2;
	  result.at(2) = 2*x*y1*y2 + 2*pow(y0,2.0)*y1;
	  
	  return result;
   }
   
   
}

void CDGLSolver::doEuler(double xStart, double xEnd, int numberOfSteps, vec yStart) {
   
   
   double stepWidth = (xEnd - xStart) / numberOfSteps;
   double x = xStart;
   vec tmpvec = yStart;
   double abweichung =0.0;
   if(this->isDGLSystem) {
	  std::cout << "Schrittweite von h:" << stepWidth << std::endl;
   }
   
   for (int i = 0; i <= numberOfSteps; i++) {
	  
	 
	   if (i == 100 && this->isDGLSystem) {
		 std::cout << "Ende bei: " << std::endl;
		 std::cout << "x = " << x << std::endl;
		 std::cout << "y = ";
		 tmpvec.print();
		 return;
	  }
	  abweichung = tmpvec.at(0)-0.5;
	  
	  if(this->isDGLSystem) {
		 std::cout << "Schritt " << i << ":" << std::endl;
		 std::cout << "x = " << x << std::endl;
		 std::cout << "y = ";
		 tmpvec.print();
		 std::cout << "y' = ";
	  }
	  
	  vec res = Ableitungen(tmpvec, x);
	 
	  if(this->isDGLSystem) {
		 res.print();
		 std::cout << "_________________" << std::endl;
		 std::cout << std::endl;
	  }
	  x += stepWidth;
	  vec stepVec = res * stepWidth;
	  tmpvec = tmpvec + stepVec;
	  
   }
   
   std::cout <<"Abweichung bei Euler bei " << numberOfSteps <<" Schritten: " << abweichung<< std::endl;
}



void CDGLSolver::doHeun(double xStart, double xEnd, int numberOfSteps, vec yStart) {
   double abweichung =0.0;
   double stepWidth = (xEnd - xStart) / numberOfSteps;
   double x = xStart;
   vec tmpvec = yStart;
   
   if(this->isDGLSystem) {
	  std::cout << "Schrittweite von h:" << stepWidth << std::endl;
   }
   
   for (int i = 0; i <= numberOfSteps; i++) {
	  
	  if (i == 100 && this->isDGLSystem) {
		 std::cout << "Ende bei: " << std::endl;
		 std::cout << "x = " << x << std::endl;
		 std::cout << "y = ";
		 tmpvec.print();
		 return;
	  }
   
	  abweichung = tmpvec.at(0)-0.5;
	  
	  if(this->isDGLSystem) {
		 std::cout << "Schritt " << i << ":" << std::endl;
		 std::cout << "x = " << x << std::endl;
		 std::cout << "y = ";
		 tmpvec.print();
		 std::cout << "y'_orig = ";
	  }
	  vec res = Ableitungen(tmpvec, x);
	  
	  if(this->isDGLSystem) {
		 res.print();
		 std::cout << std::endl;
	  }
	  
	  double testx = x + stepWidth;
	  vec stepVec = res * stepWidth;
	  vec testvec = tmpvec + stepVec;
	  if(this->isDGLSystem) {
		 std::cout << "y_Test = ";
		 testvec.print();
	  
		 std::cout << "y'_Test = ";
	  }
		 vec testResult = Ableitungen(testvec, testx);
	  if(this->isDGLSystem) {
		 testResult.print();
		 std::cout << std::endl;
		 std::cout << "y'_Mittel = ";
	  }
	  vec middleResult = (testResult + res) * 0.5;
   
	  if(this->isDGLSystem) {
	  middleResult.print();
	  std::cout << std::endl;
	  }
	  vec tpres = middleResult * stepWidth;
	  tmpvec = tmpvec + tpres;
	  x += stepWidth;
   }
   std::cout <<"Abweichung bei Heun bei " << numberOfSteps <<" Schritten: " << abweichung<< std::endl;
}

CDGLSolver::CDGLSolver(vec (*f_DGL_System)(vec, double)) {
  this->isDGLSystem = true;
   this->Element_f_DGL_System = f_DGL_System;
   this->Element_f_DGL_nterOrdnung = nullptr;
}

CDGLSolver::CDGLSolver(double (*f_DGL_nterOrdnung)(vec, double)) {
   this->isDGLSystem = false;
   this->Element_f_DGL_System = nullptr;
   this->Element_f_DGL_nterOrdnung = f_DGL_nterOrdnung;
}
