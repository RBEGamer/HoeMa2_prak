#include <iostream>
#include "magic_random.h"
#include <vector>

#include <time.h>


 void a1(){

     magic_random rnd;

    int min = 3;
    int max = 7;
    int count =10000;
    int n = 5;


     //rnd.initialisiere(time(NULL));
     //rnd.initialisiere(n);
    std::vector<int> test_h = rnd.test(min,max,count);
    for (int i = min; i < max; ++i) {
        std::cout << "" << i << " " << test_h[i] << "x  n=" << n;
    }



     std::cout << "e)" << std::endl;
    test_h = rnd.testfalsch(min,max,count);
    for (int i = min; i < max; ++i) {
        std::cout << "" << i << " " << test_h[i] << "x  n=" << n;
    }



}
int main() {
//a1();



    //3a



    return 0;
}