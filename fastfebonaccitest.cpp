#include "fastfebonacci.h"
#include "catch.hpp"


int slowFeb(int k)
{

    if(k == 0)
    {
        return 0;
    }
    else
    {
        int f0 = 0;
        int f1 = 1;

        for(int i = 2;i<=k;i++)
        {
            int f = f0+f1;
            f0=f1;
            f1 = f;
        }
        return f1;
    }
}

TEST_CASE("Perform fast febonacci","[fastfebonacci]")
{
    CHECK(Algo::FastFebonacci<10>::value == slowFeb(10));
    CHECK(Algo::FastFebonacci<20>::value == slowFeb(20));
    CHECK(Algo::FastFebonacci<30>::value == slowFeb(30));


}
