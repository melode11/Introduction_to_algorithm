#include "maxsubarray.h"
#include "catch.hpp"
#include <iostream>

using namespace std;

TEST_CASE("Find maximum subarray","[maxsubarray]")
{
    //correct max subarray : [4-14]
    int data[] = {
        -293
        ,43
        ,21
        ,-345
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
        ,-694
    };

    int sum = 0;
    for(int* i = data+4;i<data+14;++i)
    {
        sum+=*i;
    }
    cout<<"s:"<<sum<<endl;

    Algo::SubArrayDescriptor<int> desc = Algo::MaxSubArray(data,data+15);
    CHECK(desc.start == data+4);
    CHECK(desc.end == data+14);
    CHECK(desc.sum == sum);
}
