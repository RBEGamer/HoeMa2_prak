//
// Created by Marcel Ochsendorf on 02.07.17.
//

#include "lotto.h"

lotto::lotto(int n)
{
    if (n < 0)
    {
        magic_random::initialisiere(time(NULL));
    }
    else
    {
        magic_random::initialisiere(n);
    }
}

void lotto::tipp(int t1, int t2, int t3, int t4, int t5, int t6)
{
    tippzettel = std::vector<int>(6);

    tippzettel[0] = t1;
    tippzettel[1] = t2;
    tippzettel[2] = t3;
    tippzettel[3] = t4;
    tippzettel[4] = t5;
    tippzettel[5] = t6;
}

std::vector<int> lotto::ziehung()
{
    std::vector<int> result = std::vector<int>(6,0);
    int rnd_num = -1;
    volatile bool is_in;
    for (int i = 0; i < 6; i++)
    {
        do
        {
            is_in = false;
            rnd_num = magic_random::wert(1, 49);
            for (int j = 0; j < 6; j++)
            {
                if (rnd_num == result[j])
                {
                    is_in = true;
                }
            }
        } while (is_in);
        result[i] = rnd_num;
    }
    return result;
}

int lotto::tippZiehung(){
    std::vector<int> z = ziehung();
    int smae_num_counter = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (tippzettel[i] == z[j])
            {
                smae_num_counter++;
                break;
            }
        }
    }
    return smae_num_counter;
}

int lotto::ziehungenVergleich()
{
    std::vector<int> z1 = ziehung();
    std::vector<int> z2 = ziehung();
    int same_number = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (z1[i] == z2[j])
            {
                same_number++;
                break;
            }
        }
    }
    return same_number;
}