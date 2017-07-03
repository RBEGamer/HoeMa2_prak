#include <iostream>
#include "magic_random.h"
#include <vector>

#include <time.h>
#include "lotto.h"

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


    {
        //3a
        lotto l(time(NULL));
        //erstelle festen tippschein
        lotto::TIPPZETTEL tippschein_fest;
        tippschein_fest.gen_n = l.rnd.current_n;
        tippschein_fest.numbers[0] = 2;
        tippschein_fest.numbers[1] = 45;
        tippschein_fest.numbers[2] = 22;
        tippschein_fest.numbers[3] = 32;
        tippschein_fest.numbers[4] = 23;
        tippschein_fest.numbers[5] = 7;
        l.set_tippzettel(tippschein_fest);

        int is_in_couter = 0;
        int N = 100000;
        for (int i = 0; i < N; ++i) {
            //mache eine zeihung
            std::vector<lotto::TIPPZETTEL> ziehung = l.make_ziehung(1);
            //gebe gleiche zahlen aus
            std::vector<int> z1 = l.get_same_values(ziehung);
            if (z1.size() >= 3) {
                is_in_couter++;
            }
        }
        std::cout << "3a) p(>=3 geliche) = Ng/N = " << ((float) is_in_couter / (float) N)*100.0f << "%" << std::endl;
    }


    //3b
    {
        lotto l(time(NULL));

        int N = 100000;
        int counter = 0;
        for (int i = 0; i < N; ++i) {
            if(l.get_count_of_same_values_of_two_trys() >= 3){
                counter++;
            }
        }
        std::cout << "3b) p(>=3 geliche) = Ng/N = " << ((float) counter / (float) N)*100.0f << "%" << std::endl;





    }


    return 0;
}