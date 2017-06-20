#include <iostream>
#include "complex.h"

#include <fstream>
#include <vector>
#include <math.h>
using namespace std;


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
vector<complex> werte_ausgeben(char *dateiname, vector<complex>& werte, double epsilon=-1.0, bool ignore_exp = false) {
    vector<complex> werte_exp;
        werte_exp.clear();

    long exported = 0;
    int i;
    int N = 0;

    for (i = 0; i < werte.size(); i++){
        if (ignore_exp || werte[i].abs() > epsilon) {
        
		   N++;
        }
    }

    // File oeffnen
    ofstream fp;
    fp.open(dateiname, ios_base::trunc);
    if (fp.fail()) {
        std::cout << "file could not open - export" << std::endl;
        return werte_exp;
    }
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    if (N < 0) {
        fp.close();
        return werte_exp;
	   
	  
    }
    for (i = 0; i < werte.size(); i++)
	   if (ignore_exp || werte[i].abs() > epsilon) {
		  exported++;
		  fp << i << "\t" << werte[i].get_re() << "\t" << werte[i].get_im() << endl;
			 werte_exp.push_back(werte[i]);
	   }
	
    // File schliessen
    fp.close();
    return werte_exp;
}

//A3
enum FOURIER_MODE{
    FORWARD,
    BACK
};

std::vector<complex> fourier(std::vector<complex> _values, FOURIER_MODE _mode = FOURIER_MODE::FORWARD) {
   
 
   
   
   if (_mode == FOURIER_MODE::FORWARD) {
	  std::cout << "FM:FORWARD" << std::endl;
	  int AnzahlFunktionsWerte = _values.size();
	  
	  std::vector<complex> f_values;
	  f_values.clear();
	  
	  for (int i = 0; i < AnzahlFunktionsWerte; ++i) {
		 f_values.push_back(_values[i]);
	  }
	  
	  std::vector<complex> c_transformation_values(AnzahlFunktionsWerte);
	  c_transformation_values.clear();
	  
	  for (int k = 0; k < AnzahlFunktionsWerte; ++k) {
		 
		 complex cResult;
		 std::vector<complex> w_at_indexTransResult(AnzahlFunktionsWerte);
		 w_at_indexTransResult.clear();
		 
		 
		 for (int n = 0; n < AnzahlFunktionsWerte; ++n) {
			
			
			
			complex w_k(((2 * M_PI *-n*k) / AnzahlFunktionsWerte));
			//complex w_minus_n(((2 * M_PI * -n) / AnzahlFunktionsWerte));
		 
			//std::cout <<" Berechnung Matrix " <<k <<"    " << n<<" " ;
			//std::cout << "Hochwert  von w_k: " << ((2 * M_PI * k) / AnzahlFunktionsWerte) <<"            ";
			//std::cout		  << "w_k ";  w_k.pint();
			
			//std::cout << endl;
			
			//std::cout << "w_minus_n      " << ((2 * M_PI * -n) / AnzahlFunktionsWerte) << "";
			//w_minus_n.pint();
			//std::cout << std::endl;
			
			
			
			//std::cout << "Multiplikation Resultat " ;
			//w_minus_n_k.pint();
			//std::cout << std::endl;
			//std::cout << std::endl;
			
			w_at_indexTransResult.push_back(w_k);
		 }
		 
		 
		 for (int n = 0; n < AnzahlFunktionsWerte; ++n) {
			
			cResult = cResult + w_at_indexTransResult.at(n) * f_values.at(n);
		 
			//std::cout << "Aufaddieren cResult:  "  ;
			//cResult.pint();
			//std::cout << std::endl;
		 }
		 
		 
		 
		 cResult = cResult * (1 / (sqrt(AnzahlFunktionsWerte)));
		 //std::cout << "Aufaddieren cResult: Dividiert  ";
		// cResult.pint();
		 c_transformation_values.push_back(cResult);
	 
	   }

	  return c_transformation_values;
	  
   } else if (_mode == FOURIER_MODE::BACK) {
	  
	  int AnzahlFunktionsWerte = 1000;
	  int AnzahlKoeffizienten = _values.size();
	  
	  std::cout << "FM:BACK" << AnzahlFunktionsWerte << std::endl;
   
	 
	  
	  std::vector<complex> c_values;
	  c_values.clear();
	  for (int i = 0; i < AnzahlKoeffizienten; ++i) {
		 c_values.push_back(_values[i]);
		// std::cout << "C Werte Ruecktransformation" << i << " ";
		//		   _values[i].pint();
		// std::cout << std::endl;
	  }
	  
	  
	  std::vector<complex> Re_transformation_values(AnzahlFunktionsWerte);
	  Re_transformation_values.clear();
	  
	  for (int k = 0; k < AnzahlFunktionsWerte; ++k) {
		 
		 complex ReTransResult;
		 std::vector<complex> f_at_indexTransResult(AnzahlKoeffizienten);
		 f_at_indexTransResult.clear();
		 
		 
		 for (int n = 0; n < AnzahlKoeffizienten; ++n) {
			
			complex w_k((2 * M_PI * k*n) / AnzahlFunktionsWerte);
			
			
			f_at_indexTransResult.push_back(w_k);
		 }
	  
	  
	  for (int n = 0; n < AnzahlKoeffizienten; ++n) {
		 
		 ReTransResult = ReTransResult + f_at_indexTransResult.at(n) * c_values.at(n);
		 
	  }
	  
	  ReTransResult = (ReTransResult * (1 / (sqrt(AnzahlFunktionsWerte))));
	  
	  Re_transformation_values.push_back(ReTransResult);
   
	  }
   
	  for (int n = 0; n < AnzahlFunktionsWerte; ++n) {
	  
		
		 //std::cout <<"F Transformation " <<n << " " ;
		// Re_transformation_values.at(n).pint() ;
		//std::cout <<std::endl;
	  
	  }
	  
	  
	  return Re_transformation_values;
}
	  

    else{
        std::cout << "_mode no omplemented" << std::endl;
    }
    
}




int main() {
   
   
   //READ ORIGINAL FILES
    std::vector<complex> original_values = werte_einlesen("../original.txt");
    //MAKE FOURIER FORWARD TRANSFORMATION
    std::vector<complex> fourier_forward = fourier(original_values,FOURIER_MODE::FORWARD);
    //EXPORT VALUES
    std::vector<complex> write_values_default = werte_ausgeben("../output_default.txt",fourier_forward,-1.0);
    std::vector<complex> write_values_10 = werte_ausgeben("../output_10.txt",fourier_forward,1.0);
    std::vector<complex> write_values_01 = werte_ausgeben("../output_01.txt",fourier_forward,0.1);
    //mache hintransformtation
    std::cout << "es wurden " << write_values_default.size() << " werte mit epsilon=-1.0 exportiert" << std::endl;
    std::cout << "es wurden " <<  write_values_10.size() << " werte mit epsilon=1.0 exportiert" << std::endl;
    std::cout << "es wurden " << write_values_01.size() << " werte mit epsilon=0.1 exportiert" << std::endl;
    //lese werte
    std::vector<complex> read_values_default = werte_einlesen("../output_default.txt");
    std::vector<complex> read_values_10 = werte_einlesen("../output_10.txt");
    std::vector<complex> read_values_01 = werte_einlesen("../output_01.txt");
    //mache rücktransformation
   
   std::vector<complex> retrans_values_default = fourier(read_values_default,FOURIER_MODE::BACK);
   std::vector<complex> retrans_values_10 = fourier(read_values_10,FOURIER_MODE::BACK);
   std::vector<complex> retrans_values_01 = fourier(read_values_01,FOURIER_MODE::BACK);
   


    //WRITE BACK TRANS
    werte_ausgeben("../output_BACK_default.txt",retrans_values_default,-1.0, true);
    werte_ausgeben("../output_BACK_10.txt",retrans_values_10,-1, true);
    werte_ausgeben("../output_BACK_01.txt",retrans_values_01,-1, true);

    //berechne abweichung für -1.0f defualt
    long compare_index_default = retrans_values_default.size();
    if(read_values_default.size() > compare_index_default){
        compare_index_default = read_values_default.size();
    }
    double abweichung_ep_default = -1.0f;
    for (int i = 0; i < compare_index_default; ++i) {
        if((original_values[i].abs()-retrans_values_default[i].abs()) > abweichung_ep_default){
            abweichung_ep_default = (original_values[i].abs()-retrans_values_default[i].abs());
        }
    }
    std::cout<< "max abweichung -1.0 default ist " << abweichung_ep_default << std::endl;
  
  
  
  
    //berechne abweichung für 1.0
   long compare_index_10 = retrans_values_10.size();
   if(read_values_10.size() < compare_index_10){
	  compare_index_10 = read_values_10.size();
   }
  
    double abweichung_ep_10 = -1.0f;;
    for (int i = 0; i < compare_index_10; ++i) {
       //std::cout<<"ORIGINAL: " << original_values[i].abs();
	   //std::cout<<"    Transformiert: " << retrans_values_10[i].abs();
	   //std::cout<<std::endl;
	   
	   if(((original_values[i].abs()-retrans_values_10[i].abs())) < abweichung_ep_10){
         abweichung_ep_10 = (original_values[i].abs()-retrans_values_10[i].abs());
         }
    }
    std::cout<< "max abweichung 1.0 ist " << abweichung_ep_10 << std::endl;
   
   
   //berechne abweiung für 0.1f
   long compare_index_01 = retrans_values_01.size();
   if(read_values_01.size() < compare_index_01){
	  compare_index_01 = read_values_01.size();
   }
   
   
   double abweichung_ep_01 = (original_values[0].abs()-retrans_values_01[0].abs());
    for (int i = 0; i < compare_index_01; ++i) {
        if((original_values[i].abs()-retrans_values_01[i].abs()) > abweichung_ep_01){
            abweichung_ep_01 = (original_values[i].abs()-retrans_values_01[i].abs());
        }
    }
    std::cout<< "max abweichung 0.1 ist " << abweichung_ep_01 << std::endl;
   return 0;
}