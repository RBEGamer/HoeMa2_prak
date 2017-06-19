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
    std::vector<complex> werte;
    // File oeffnen
    ifstream fp;
    fp.open(dateiname);

    if(fp.fail()){
        std::cout << "file not found" << std::endl;
        throw ;
    }
    // Dimension einlesen
    fp >> N;
    std::cout << "es sind " << N << "sätzen in der tabelle" <<std::endl;
    // Werte-Vektor anlegen
    werte.resize(N);
    werte.clear();
    complex null(0.0,0.0);
    for (i = 0; i<N; i++){
        werte.push_back(null);
    }

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
long werte_ausgeben(char *dateiname, vector<complex> werte, double epsilon=-1.0, vector<complex>* werte_exp = nullptr) {
    if (werte_exp != nullptr) {
        werte_exp->clear();
    }
    long exported = 0;
    int i;
    int N = 0;

    for (i = 0; i < werte.size(); i++){
        if (werte[i].abs() > epsilon) {
            N++;
        }
    }

    // File oeffnen
    ofstream fp;
    fp.open(dateiname, ios_base::trunc);
    if (fp.fail()) {
        std::cout << "file could not open - export" << std::endl;
        return -1;
    }
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    if (N < 0) {
        fp.close();
        return exported;
    }
    for (i = 0; i < N; i++)
        if (werte[i].abs() > epsilon) {
            exported++;
            fp << i << "\t" << werte[i].get_re() << "\t" << werte[i].get_im() << endl;
            if (werte_exp != nullptr) {
            werte_exp->push_back(werte[i]);
        }
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


//anschauen http://www.rrhess.de/pdf/Skript-FFT.pdf ganz unten
//     http://paulbourke.net/miscellaneous/dft/
//https://de.wikipedia.org/wiki/Schnelle_Fourier-Transformation




std::vector<complex> fourier(std::vector<complex> _values, FOURIER_MODE _mode = FOURIER_MODE::FORWARD){
    std::vector<complex> output_values;
    output_values.clear();
    for (int i = 0; i < _values.size(); ++i) {
        output_values.push_back(_values[i]);
    }



    if(_mode == FOURIER_MODE::FORWARD){
      std::cout << "FM:FORWARD" << std::endl;
    //frequenz to sum

/*
            int n = _values.size();
            for (int k = 0; k < n; k++) {  // For each output element
                double sumreal = 0;
                double sumimag = 0;
                for (int t = 0; t < n; t++) {  // For each input element
                    double angle = 2 * PI * t * k / n;
                    sumreal +=  _values[t].get_re() * cos(angle) + _values[t].get_im() * sin(angle);
                    sumimag += -_values[t].get_re() * sin(angle) + _values[t].get_im() * cos(angle);
                }
                output_values[k]= complex(sumreal,sumimag);
            }
*/
        //long data_size = 512;
        long data_size = _values.size();

        unsigned butterflySize;   // size for actual butterfly calculation
        int i, j, k;              // local index variables
        complex wActual(0.0,0.0);  // actual rotation factor
        complex wStep(0.0);    // step rotation factors
        complex tmp(0.0,0.0);      // temp. value for butterfly calculation
        // loop over all level of FFT
        for(butterflySize=data_size/2; butterflySize>0; butterflySize/=2) {
            // evaluate angle step and set first angle
            wStep = complex(cos(-PI/butterflySize), sin(-PI/butterflySize));
            wActual = complex(1, 0);
            // loop over number of butterflys
            for(j=0; j<butterflySize; j++) {
                // loop over number of FFTs
                for(i=j; i<data_size; i+=2*butterflySize) {
                    // get index of second element
                    k = i+butterflySize;
                    // perform butterfly calculation
                    tmp = output_values[i];          // store one element
                    output_values[i] =output_values[i] + output_values[k];     // take sum
                    output_values[k] = tmp-output_values[k];  // take difference
                    output_values[k] = output_values[k]*wActual;     // multiply with rotation factor
                }
                // evaluate next rotation factor
                wActual = wActual*wStep;
            }
        }
        // perform bit reversal
        j = 0;
        for(i=0; i<data_size; i++) {
            if(j>i) {
                // swap numbers
                tmp = output_values[i];
                output_values[i] = output_values[j];
                output_values[j] = tmp;
            }
            k = data_size/2;
            while(k>=2 && j>=k) {
                j -= k;
                k /= 2; }
            j += k; }


/*
        // reverse-binary reindexing
        long nn = data_size;
        long n = data_size<<1;
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
*/

/*
        for (int rek_ebene = 0; rek_ebene < data_size; ++rek_ebene) {
            long long fft_abschnitte = (long)pow(2.0f,(float)(data_size-rek_ebene-1));
            for (int abschnitt = 0; abschnitt < fft_abschnitte; ++abschnitt) {

                int fft_element = (int)pow(2.0f,(float)(rek_ebene -1));
                for (int element = 0; element < fft_element; ++element) {

                    int index_links =(pow(2.0f,(float)(rek_ebene+1))*abschnitt)+element;
                    int index_rechts = index_links + pow(2.0,rek_ebene);

                    double phi_links =-1.0*PI*(element/rek_ebene);
                    double  phi_rechts = -1.0*PI*(element/rek_ebene);

                    output_values[index_links] = _values[index_links] + complex(phi_links) *_values[index_rechts];
                    output_values[index_rechts] = _values[index_links] - complex(phi_rechts) * _values[index_rechts];
                }
            }
        }
*/




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
    long compare_index_default = write_values_default.size();
    if(read_values_default.size() > compare_index_default){
        compare_index_default = read_values_default.size();
    }
    double abweichung_ep_default = -1.0f;
    for (int i = 0; i < compare_index_default; ++i) {
        if((read_values_default[i].abs()-write_values_default[i].abs()) > abweichung_ep_default){
            abweichung_ep_default = (read_values_default[i].abs()-write_values_default[i].abs());
        }
    }
    std::cout<< "max abweichung -1.0 default ist " << abweichung_ep_default << std::endl;
    //berechne abweichung für 1.0
    long compare_index_10 = write_values_10.size();
    if(read_values_10.size() > compare_index_10){
        compare_index_10 = read_values_10.size();
    }
    double abweichung_ep_10 = -1.0f;
    for (int i = 0; i < compare_index_10; ++i) {
        if((read_values_10[i].abs()-write_values_10[i].abs()) > abweichung_ep_10){
         abweichung_ep_10 = (read_values_10[i].abs()-write_values_10[i].abs());
         }
    }
    std::cout<< "max abweichung 0.1 ist " << abweichung_ep_10 << std::endl;
    //berechne abweiung für 0.1f
    long compare_index_01 = write_values_01.size();
    if(read_values_01.size() > compare_index_01){
        compare_index_01 = read_values_10.size();
    }
    double abweichung_ep_01 = -1.0f;
    for (int i = 0; i < compare_index_01; ++i) {
        if((read_values_01[i].abs()-write_values_01[i].abs()) > abweichung_ep_01){
            abweichung_ep_01 = (read_values_01[i].abs()-write_values_01[i].abs());
        }
    }
    std::cout<< "max abweichung 0.1 ist " << abweichung_ep_01 << std::endl;
    return 0;
}