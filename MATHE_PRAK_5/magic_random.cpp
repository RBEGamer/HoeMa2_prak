//
// Created by Marcel Ochsendorf on 01.07.17.
//

#include "magic_random.h"


magic_random::magic_random(){}
magic_random::magic_random(int _n){}

int magic_random::wert(int _a, int _b){
return rand() % _b + _a;
}

void magic_random::initialisiere(int _n){
    current_n = _n;
    if(_n < 0){
        _n = time(NULL);
        srand(current_n);
    }else {
        srand(_n);
    }
}

std::vector<int> magic_random::test(int _a, int _b, int _N){
_b++;
    std::vector<int> tmp_vork;
    tmp_vork.clear();
    for (int i = 0; i < _b; ++i) {
        tmp_vork.push_back(0);
    }

    for (int j = 0; j < _N; ++j) {
        int index =   wert(_a,_b);
     tmp_vork[index]++;
    }
    return  tmp_vork;
}


std::vector<int> magic_random::testfalsch(int a, int b, int N){
    initialisiere(time(NULL));
    return test(a,b,N);
}


