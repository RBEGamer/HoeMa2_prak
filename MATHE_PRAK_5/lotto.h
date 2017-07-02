//
// Created by Marcel Ochsendorf on 02.07.17.
//

#ifndef MATHE_P5_LOTTO_H
#define MATHE_P5_LOTTO_H

#include "magic_random.h"
#include <vector>


#define TIPP_GROESSE 6
#define TIPP_FELDER 12

#define TIPP_MIN 1
#define TIPP_MAX 49
class lotto {
public:

    struct TIPPZETTEL{
        long gen_n;
        int numbers[TIPP_GROESSE];
    };

    lotto(int _n);
    void set_tippzettel(TIPPZETTEL& _ref);
    std::vector<TIPPZETTEL> make_ziehung(int _n = TIPP_FELDER);
    bool check_tippzettel_geliche_zahlen(TIPPZETTEL& _a, TIPPZETTEL& _b);
    bool check_tippzettel_gleicher_schein(TIPPZETTEL& _a, TIPPZETTEL& _b);
    int make_ziehung_vergl_mit_schein(int _n);


    int make_ziehung_vergl_geliche_zahlen(int _n);
    magic_random rnd;
    TIPPZETTEL latest_tippzettel;

};


#endif //MATHE_P5_LOTTO_H
