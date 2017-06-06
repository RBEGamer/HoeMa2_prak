//
// Created by henn on 05.06.17.
//
#include "CMyVektor.h"

#ifndef PRAKTIKUM3_CDGLSOLVER_H
#define PRAKTIKUM3_CDGLSOLVER_H


class CDGLSolver {


private:
	double (*Element_f_DGL_nterOrdnung)(vec y, double x);
	vec (*Element_f_DGL_System)(vec y, double x);
	
	bool isDGLSystem;
	vec Ableitungen(vec y, double x);
	
public:
	
	CDGLSolver (double (*f_DGL_nterOrdnung)(vec y, double x));
	CDGLSolver (vec (*f_DGL_System)(vec y, double x));
	

    void doEuler(double xStart,double xEnd,int numberOfSteps, vec yStart);
	
	void doHeun(double xStart,double xEnd,int numberOfSteps, vec yStart);







};


#endif //PRAKTIKUM3_CDGLSOLVER_H
