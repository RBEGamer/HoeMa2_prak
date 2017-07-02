//
// Created by Marcel Ochsendorf on 02.07.17.
//

#include "lotto.h"



lotto::lotto(int _n) {
    rnd.initialisiere(_n); //die n<0 it ist im magic_random drin
}

void lotto::set_tippzettel(lotto::TIPPZETTEL& _ref){
    latest_tippzettel = _ref;
}


std::vector<lotto::TIPPZETTEL> lotto::make_ziehung(int _n){
    for (int i = 0; i < _n; ++i) {
        lotto::TIPPZETTEL tmp;
        tmp.gen_n = rnd.current_n;


        for (int j = 0; j < TIPP_GROESSE; ++j) {
            tmp.numbers[j] = 0;

            while(true) {
                volatile  bool is_in = false;
                int w = rnd.wert(1, 49);
                for (int k = 0; k < TIPP_GROESSE; ++k) {
                    if(w == tmp.numbers[k]){
                        is_in = true;
                    }
                }
                if(!is_in){
                    tmp.numbers[j] = w;
                    break;
                }
            }

        }


    }



}

//check lottozettel ob die gleichen zahlen vorkommen in beiden
bool lotto::check_tippzettel_geliche_zahlen(lotto::TIPPZETTEL& _a, lotto::TIPPZETTEL& _b){
volatile  bool t = false;
    for (int i = 0; i < TIPP_GROESSE; ++i) {
        t = false;
        for (int j = 0; j < TIPP_GROESSE; ++j) {
            if(_a.numbers[i] == _b.numbers[j]){t = true;}
        }
        if(t == false){
            return false;
        }
    }
    return true;
}

bool lotto::check_tippzettel_gleicher_schein(lotto::TIPPZETTEL& _a, lotto::TIPPZETTEL& _b){
    for (int i = 0; i < TIPP_GROESSE; ++i) {
      if(_a.numbers[i] != _b.numbers[i]){return false;}
    }
    return true;
}

//gebe anzahl zurück mit gleichem schein
int lotto::make_ziehung_vergl_mit_schein(int _n){
    std::vector<lotto::TIPPZETTEL> ziehung = make_ziehung(_n);
    int counter = 0;
    for (int i = 0; i < ziehung.size(); ++i) {
if(check_tippzettel_gleicher_schein(ziehung[i], latest_tippzettel)){
    counter++;
}
    }
}



int lotto::make_ziehung_vergl_geliche_zahlen(int _n){

    std::vector<lotto::TIPPZETTEL> z1 = make_ziehung(_n);
    std::vector<lotto::TIPPZETTEL> z2 = make_ziehung(_n);

    int counter = 0;
    for (int j = 0; j < _n; ++j) {
        for (int i = TIPP_MIN; i < TIPP_MAX; ++i) {

            volatile bool is_zahl_in_z1 = false;
            volatile bool is_zahl_in_z2 = false;

            for (int k = 0; k < TIPP_GROESSE; ++k) {
                if(z1[j].numbers[k] == i){
                    is_zahl_in_z1 = true;
                }
                if(z2[j].numbers[k] == i){
                    is_zahl_in_z2 = true;
                }
            }

            if(is_zahl_in_z1 && is_zahl_in_z2){
                //nummer i ist in beiden
                counter++;
            }

        }
    }
    return counter;
}