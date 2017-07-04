//
// Created by Marcel Ochsendorf on 02.07.17.
//

#ifndef MATHE_P5_LOTTO_H
#define MATHE_P5_LOTTO_H

#include "magic_random.h"
#include <vector>


#define TIPP_GROESSE 6
#define TIPP_FELDER 12
#define zlehungen latest_tippzettel
#define TIPP_MIN 1
#define TIPP_MAX 49
class lotto {
public:

    struct TIPPZETTEL{
    public:
        long gen_n;
        int numbers[TIPP_GROESSE];
    };

public:
    lotto(int n);
    void tipp(int t1, int t2, int t3, int t4, int t5, int t6);
    int tippZiehung();
    int ziehungenVergleich();
private:
    std::vector<int> tippzettel;
    std::vector<int> ziehung();

};


#endif //MATHE_P5_LOTTO_H
