#include <iostream>
#include "complex.h"

#include <fstream>
#include <vector>
using namespace std;




//A2
vector<complex>  werte_einlesen(char *dateiname)
{
    int i, N, idx;
    double re, im;
    vector<complex> werte;
    // File oeffnen
    ifstream fp;
    fp.open(dateiname);

    if(fp.fail()){
        std::cout << "file not found" << std::endl;
        throw ;
    }
    // Dimension einlesen
    fp >> N;
    // Werte-Vektor anlegen
    werte.resize(N);
    complex null(0.0,0.0);
    for (i = 0; i<N; i++)
        werte[i] = null;
    // Eintraege einlesen und im Werte-Vektor ablegen
    while (!fp.eof())
    {
        fp >> idx >> re >> im;
        complex a(re,im);
        werte[idx] = a;
    }
    // File schliessen
    fp.close();

    std::cout << "values_read:" << werte.size() << std::endl;
    return werte;
}
long werte_ausgeben(char *dateiname, vector<complex> werte, double epsilon=-1.0)
{
    long exported = 0;
    int i;
    int N = werte.size();
    // File oeffnen
    ofstream fp;
    fp.open(dateiname);
    if(fp.fail()){
        std::cout << "file could not open - export" << std::endl;
        return -1;
    }
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    for (i = 0; i < N; i++)
        if (werte[i].abs() > epsilon)
            exported++;
            fp << i << "\t" << werte[i].get_re() << "\t" << werte[i].get_im() << endl;
    // File schliessen
    fp.close();
    return exported;
}

//A3
enum FOURIER_MODE{
    FORWARD,
    BACK
};
std::vector<complex>fourier(std::vector<complex> _values, FOURIER_MODE _mode = FOURIER_MODE::FORWARD){
    std::vector<complex> output_values;
    if(_mode == FOURIER_MODE::FORWARD){





    }else if(_mode == FOURIER_MODE::BACK){

    }else{
        std::cout << "_mode no omplemented" << std::endl;
    }
    return output_values;
}




int main() {
    //read values A4
    std::vector<complex> read_values = werte_einlesen("../original.txt");




    //write values A4
    long exp_count_10 = werte_ausgeben("../output_10.txt",fourier(read_values,FOURIER_MODE::FORWARD),1.0);
    long exp_count_01 =werte_ausgeben("../output_01.txt",fourier(read_values,FOURIER_MODE::FORWARD),0.1);
    std::cout << "es wurden " << exp_count_10 << " werte mit epsilon=1.0 exportiert" << std::endl;
    std::cout << "es wurden " << exp_count_01 << " werte mit epsilon=0.1 exportiert" << std::endl;



    std::vector<complex> read_values_10 = werte_einlesen("../output_10.txt");
    std::vector<complex> read_values_01 = werte_einlesen("../output_01.txt");



    return 0;
}