#include "magic_random.h"

void magic_random::initialisiere(int n)
{
    srand(n);
}

int magic_random::wert(int a, int b)
{
    if (a > b)
    {
        return NULL;
    }
    return (rand() % (b-a+1)) + a;
}

std::vector<int> magic_random::test(int a, int b, int N)
{
    std::vector<int> values = std::vector<int>((b - a) + 1,0);
    for (int i = 0; i < N; i++)
    {
        values[wert(a, b) - a]++;
    }
    return values;
}

std::vector<int> magic_random::test_falsch(int a, int b, int N)
{
    std::vector<int> values = std::vector<int>((b - a) + 1, 0);
    for (int i = 0; i < N; i++)
    {
        srand(time(NULL));
        values[wert(a, b) - a]++;
    }
    return values;
}