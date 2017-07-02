//
// Created by Marcel Ochsendorf on 01.07.17.
//

#ifndef MATHE_P5_MAGIC_RANDOM_H
#define MATHE_P5_MAGIC_RANDOM_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

class magic_random {
public:
    long current_n; //GET ONLY
    magic_random();
    magic_random(int _n);
    int wert(int _a, int _b);
    void initialisiere(int _n);
    std::vector<int> test(int _a, int _b, int _N);
     std::vector<int> testfalsch(int _a, int _b, int _N);
};


#endif //MATHE_P5_MAGIC_RANDOM_H
