#include <iostream>
#include "magic_random.h"
#include <vector>

#include <time.h>
#include "lotto.h"





int main() {


    lotto lotto(time(NULL));
//3a
    lotto.tipp(9, 10, 11, 22, 23, 24);
    int count_3a = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (lotto.tippZiehung() == 3)
        {
            count_3a++;
        }
    }
    std::cout << "3a) Die Wahrscheinlichkeit liegt damit bei "  << (double(count_3a)/ 10000.0)*100.0f << "%" << std::endl;




//3b
    int count_3b = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (lotto.ziehungenVergleich() == 3)
        {
            count_3b++;
        }
    }
    std::cout << "3b) Die Wahrscheinlichkeit liegt damit bei " << (double(count_3b) / 10000.0)*100.0f << "%" << std::endl;

    return 0;
}