#include <iostream>
#include "complex.h"

#include <fstream>
#include <vector>
using namespace std;



#define PI M_1_PI
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
    fp.open(dateiname,ios_base::trunc);
    if(fp.fail()){
        std::cout << "file could not open - export" << std::endl;
        return -1;
    }
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    if(N <= 0){
        fp.close();
        return  exported;
    }
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

std::vector<complex> fourier(std::vector<complex> _values, FOURIER_MODE _mode = FOURIER_MODE::FORWARD){
    std::vector<complex> output_values;
    output_values.clear();
    if(_mode == FOURIER_MODE::FORWARD){
      //      std::cout << "FM:FORWARD" << std::endl;
    //frequenz to sum
        output_values = _values;


        //redindexing by http://www.drdobbs.com/cpp/a-simple-and-efficient-fft-implementatio/199500857
        // reverse-binary reindexing
        long nn = _values.size();
        long n = _values.size()<<1;
        long i = 0;
        long j=1;
        for (i=1; i<n; i+=2) {
            if (j>i) {
                swap(_values[j-1], _values[i-1]);
                swap(_values[j], _values[i]);
            }
            long m = nn;
            while (m>=2 && j>m) {
                j -= m;
                m >>= 1;
            }
            j += m;
        };



        /*
         *
         * Wenn im obigen Algorithmus zuerst die beiden Hälften des Feldes miteinander
         * vertauscht werden, und dann die beiden Hälften dieser Hälften, usw. –
         * dann ist das Ergebnis am Ende dasselbe,
         * als würden alle Elemente des Feldes von 0 aufsteigend nummeriert werden und
         * anschließend die Reihenfolge der Bits der Nummern der Felder umgekehrt.
         */
        //https://de.wikipedia.org/wiki/Schnelle_Fourier-Transformation
        for (int rek_ebene = 0; rek_ebene < _values.size(); ++rek_ebene) {
            int fft_abschnitte = _values.size()-rek_ebene-1;
            for (int abschnitt = 0; abschnitt < fft_abschnitte; ++abschnitt) {

                int fft_element = rek_ebene -1;
                for (int element = 0; element < fft_element; ++element) {

                    int index_links =(rek_ebene+1)*abschnitt+element;
                    int index_rechts = index_links + pow(2.0,rek_ebene);

                    double phi_links =-1.0*PI*(element/rek_ebene);
                    double  phi_rechts = -1.0*PI*(element/rek_ebene);

                    output_values[index_links] = _values[index_links] + complex(phi_links) *_values[index_rechts];
                    output_values[index_rechts] = _values[index_links] - complex(phi_rechts) * _values[index_rechts];
                }
            }
        }





    }else if(_mode == FOURIER_MODE::BACK){


        //double to complex
    }else{
        std::cout << "_mode no omplemented" << std::endl;
    }
    return output_values;
}




int main() {
    //read values A4
    std::vector<complex> original_values = werte_einlesen("../original.txt");
    //write values A4

    std::vector<complex> write_values_default;
    std::vector<complex> write_values_10;
    std::vector<complex> write_values_01;
    //mache hintransformtation
    std::cout << "es wurden " << werte_ausgeben("../output_default.txt",fourier(original_values,FOURIER_MODE::FORWARD),-1.0, &write_values_default) << " werte mit epsilon=-1.0 exportiert" << std::endl;
    std::cout << "es wurden " <<  werte_ausgeben("../output_10.txt",fourier(original_values,FOURIER_MODE::FORWARD),1.0, &write_values_10) << " werte mit epsilon=1.0 exportiert" << std::endl;
    std::cout << "es wurden " << werte_ausgeben("../output_01.txt",fourier(original_values,FOURIER_MODE::FORWARD),0.1, &write_values_01) << " werte mit epsilon=0.1 exportiert" << std::endl;
    //lese werte
    std::vector<complex> read_values_default = werte_einlesen("../output_default.txt");
    std::vector<complex> read_values_10 = werte_einlesen("../output_10.txt");
    std::vector<complex> read_values_01 = werte_einlesen("../output_01.txt");
    //mache rücktransformation
    read_values_default = fourier(read_values_default,FOURIER_MODE::BACK);
    read_values_10 = fourier(read_values_10,FOURIER_MODE::BACK);
    read_values_01 = fourier(read_values_01,FOURIER_MODE::BACK);
    //berechne abweichung für -1.0f defualt
    if(write_values_10.size() != read_values_10.size()){
        std::cout << "compare default not possible" << std::endl;
    }
    double abweichung_ep_default = -1.0f;
    for (int i = 0; i < write_values_default.size(); ++i) {
        if((read_values_default[i].abs()-write_values_default[i].abs()) > abweichung_ep_default){
            abweichung_ep_default = (read_values_default[i].abs()-write_values_default[i].abs());
        }
    }
    std::cout<< "abweichung -1.0 default ist " << abweichung_ep_default << std::endl;
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