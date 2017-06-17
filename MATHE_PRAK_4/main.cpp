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
long werte_ausgeben(char *dateiname, vector<complex> werte, double epsilon=-1.0, vector<complex>* werte_exp = nullptr)
{
    if(werte_exp != nullptr){
        werte_exp->clear();
    }
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
            if(werte_exp != nullptr){
                werte_exp->push_back(werte[i]);
            }
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
    std::vector<complex> original_values = werte_einlesen("../original.txt");
    //write values A4


    std::vector<complex> write_values_10;
    std::vector<complex> write_values_01;
    //mache hintransformtation
    std::cout << "es wurden " <<  werte_ausgeben("../output_10.txt",fourier(original_values,FOURIER_MODE::FORWARD),1.0, &write_values_10) << " werte mit epsilon=1.0 exportiert" << std::endl;
    std::cout << "es wurden " << werte_ausgeben("../output_01.txt",fourier(original_values,FOURIER_MODE::FORWARD),0.1, &write_values_01) << " werte mit epsilon=0.1 exportiert" << std::endl;
    //lese werte
    std::vector<complex> read_values_10 = werte_einlesen("../output_10.txt");
    std::vector<complex> read_values_01 = werte_einlesen("../output_01.txt");
    //mache rücktransformation
    read_values_10 = fourier(read_values_10,FOURIER_MODE::BACK);
    read_values_01 = fourier(read_values_01,FOURIER_MODE::BACK);
    //berechne abweichung für 1.0
    if(write_values_10.size() != read_values_10.size()){
        std::cout << "compare 1.0 not possible" << std::endl;
    }
    double abweichung_ep_10 = -1.0f;
    for (int i = 0; i < write_values_10.size(); ++i) {
        if((read_values_10[i].abs()-write_values_10[i].abs()) > abweichung_ep_10){
         abweichung_ep_10 = (read_values_10[i].abs()-write_values_10[i].abs());
         }
    }
    std::cout<< "abweichung 0.1 ist " << abweichung_ep_10 << std::endl;
    //berechne abweiung für 0.1f
    if(write_values_01.size() != read_values_01.size()){
        std::cout << "compare 0.1 not possible" << std::endl;
    }
    double abweichung_ep_01 = -1.0f;
    for (int i = 0; i < write_values_01.size(); ++i) {
        if((read_values_01[i].abs()-write_values_01[i].abs()) > abweichung_ep_01){
            abweichung_ep_01 = (read_values_01[i].abs()-write_values_01[i].abs());
        }
    }
    std::cout<< "abweichung 0.1 ist " << abweichung_ep_01 << std::endl;



    
    return 0;
}