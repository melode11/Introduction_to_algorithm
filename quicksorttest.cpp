#include "catch.hpp"
#include "qsort.h"
#include <iostream>

TEST_CASE("Perform quick sort","[quicksort]")
{
    int data[] = {
        293
        ,43
        ,21
        ,1345
        ,32
        ,96
        ,84
        ,699
        ,635
        ,755
        ,37
        ,384
        ,273
        ,57
        ,694
    };

    Algo::qsort(data,data+15);

    int last = data[0];
    for(size_t i = 1;i<15;++i)
    {
        if(data[i]<last)
        {
            CHECK(false);
            break;
        }
        last = data[i];
    }
}
