#include "kmp.h"
#include "catch.hpp"

TEST_CASE("kmp string compare","[kmp]")
{
    std::string a("sisaicdiisdfdfsidifjgitk;sociskd;kgivuahtjenglix ceuxiemceuyrnt,px,eiyenrmrjr");
    std::string b("ceuxiemceu");
    CHECK(Algo::kmp(a,b) == a.find(b));
}

TEST_CASE("kmp get max match","[kmp]")
{
    std::string b("ceuxiemceu");
    CHECK(Algo::GetMaxMatch(b.data(),b.length()) == 3);
    CHECK(Algo::GetMaxMatch(b.data(),b.length()-1) == 2);
    CHECK(Algo::GetMaxMatch(b.data(),b.length()-2) == 1);
    for(int i = 3;i<b.length();++i)
    {
        CHECK(Algo::GetMaxMatch(b.data(),b.length()-i) == 0);
    }
}
