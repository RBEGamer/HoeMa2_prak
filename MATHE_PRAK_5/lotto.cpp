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
   std::vector<lotto::TIPPZETTEL> tmp_vec;
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
        tmp_vec.push_back(tmp);
    }
    return tmp_vec;
}



std::vector<int> lotto::get_same_values(std::vector<lotto::TIPPZETTEL> _ziehung){
std::vector<int> zahlen_drin;
    for (int i = 0; i <_ziehung.size(); ++i) {
        //gehe von 1 - 49
        for (int j = TIPP_MIN; j < TIPP_MAX+1; ++j) {
            volatile  bool is_in_saved = false;
            volatile  bool is_in_extern = false;
            for (int k = 0; k < TIPP_GROESSE; ++k) {
                if(latest_tippzettel.numbers[k] == j){
                    is_in_saved = true;
                }

                if(_ziehung[i].numbers[k] == j){
                    is_in_extern = true;
                }
            }
            if(is_in_extern && is_in_saved){
                zahlen_drin.push_back(j);
            }
        }
    }
    return zahlen_drin;
}



int lotto::get_count_of_same_values_of_two_trys(){
    std::vector<lotto::TIPPZETTEL> z1 = make_ziehung(1);
    std::vector<lotto::TIPPZETTEL> z2 = make_ziehung(1);

    std::vector<int> ub_zahl;
    int counter = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
        if(z1[0].numbers[i] == z2[0].numbers[j]){
            volatile  bool is_in = false;
            for (int k = 0; k < ub_zahl.size(); ++k) {
                if(z1[0].numbers[i] == ub_zahl[k]){
                    is_in = true;
                }
            }

            if(!is_in){
                counter++;
            }
        }
        }
    }
    
return counter;
}