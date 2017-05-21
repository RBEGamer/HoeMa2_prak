#include <iostream>
#include "vec.h"
#include "mat.h"
#include <math.h>
#include <limits>
#include <fstream>
#include <iomanip>


//HÖHÖ USE THIS
#define BREAK_CON 0.00001
#define BREAK_STEPS 50
#define H 0.0001
#define OUT_FILE_PATH "../output_result.txt"



//TODO A3
vec f(vec _x){


}

//TODO A2
mat jacobi(vec x, vec (*funktion)(vec x)){



}



int main() {

    std::ofstream file;
    file.open(OUT_FILE_PATH,std::fstream::out);
    if(file.fail()){
        std::cout << "FILE OPEN FAILED" << std::endl;
        return -1;
    }




    vec VECTOR_X("dd",1.0f,1.0f); //START COORDIANTE
    //TODO A3

    for (int i = 0; i < BREAK_STEPS; ++i) {
        file << i <<":"     <<std::endl;
        file <<"   "<< "X =";
        VECTOR_X.print(&file);

        mat RESULT_MAT(2,2);
        file << "   " << "f´(x)=";
        RESULT_MAT.print(&file);

    }



    file.close();
    return 0;
}