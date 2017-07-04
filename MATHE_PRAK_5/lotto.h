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
    public:
        long gen_n;
        int numbers[TIPP_GROESSE];


    };

    lotto(int _n);
    void set_tippzettel(TIPPZETTEL& _ref);
    std::vector<TIPPZETTEL> make_ziehung(int _n = TIPP_FELDER, bool _oth = true);



    //std::vector<int> get_same_values(std::vector<TIPPZETTEL> _ziehung, TIPPZETTEL fixed);
    std::vector<int> get_same_values(std::vector<lotto::TIPPZETTEL> _ziehung, lotto::TIPPZETTEL fixed);

    int get_count_of_same_values_of_two_trys();
    magic_random rnd_n;
    magic_random rnd_m;
    TIPPZETTEL latest_tippzettel;

};


#endif //MATHE_P5_LOTTO_H
