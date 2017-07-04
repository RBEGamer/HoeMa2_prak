
#ifndef MATHE_P5_MAGIC_RANDOM_H
#define MATHE_P5_MAGIC_RANDOM_H


#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

class magic_random
{
public:
    static void initialisiere(int n);
    static int wert(int a, int b);
    static std::vector<int> test(int a, int b, int N);
    static std::vector<int> test_falsch(int a, int b, int N);
};
#endif //MATHE_P5_MAGIC_RANDOM_H
