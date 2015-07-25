#include "selectkthvalue.h"
#include "catch.hpp"


TEST_CASE("Select k-th value","[selectkthvalue]")
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
    int* pos = Algo::select_kth_value(data,data+15,4);
    CHECK(*pos == 57);
    pos = Algo::select_kth_value(data,data+15,6);
    CHECK(*pos == 96);

}
