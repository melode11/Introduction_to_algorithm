#include "mergesort.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Perform mergesort","[mergesort]")
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

    std::vector<int> dataVec(15);
    std::copy(data,data+15,dataVec.begin());
    Algo::mergesort(dataVec);
    bool ordered = true;
    int last = dataVec[0];
    for(size_t i = 1;i<15;++i)
    {
        if(dataVec[i]<last)
        {
            CHECK(false);
            break;
        }
        last = dataVec[i];
    }
}
