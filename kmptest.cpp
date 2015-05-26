#include "kmp.h"
#include "catch.hpp"
#include <algorithm>
#include <iostream>
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

TEST_CASE("kmp get next set","[kmp]")
{
    std::string b("abcdabc");
    std::vector<int> nexts;
    Algo::GetNextSet(b,nexts);
    //raw:0,0,0,0,1,2,3
    //len-raw:1,2,3,4,4,4,4
    int expected[] = {1,2,3,4,4,4,4};
    CHECK(std::equal(nexts.begin(),nexts.end(),expected));


      std::string b2("abcabcd");//size = 10
      nexts.clear();
      Algo::GetNextSet(b2,nexts);
      //0,0,0,1,2,3,0
      //1,2,3,3,3,3,7
      int expected2[] = {1,2,3,3,3,3,7};
      CHECK(std::equal(nexts.begin(),nexts.end(),expected2));
}

TEST_CASE("kmp string compare","[kmp]")
{
    std::string a("sisaicdiisdfdfsidifjgitk;sociskd;kgivuahtjenglix ceuxiemceuyrnt,px,eiyenrmrjr");
    std::string b("ceuxiemceu");
    std::string a2("This time however unlike the previous two leaks not one, not two and not even three but four PCB assemblies for the GPU have been shipped. And for the first time the listing included a very peculiar suffix “(FOC)” which we believe stands for Full Operational Capacity. This signals that the card has exited the early prototyping stage as finalized samples are being shipped for end-stage testing and evaluation. The R9 390X moniker will only serve as a place holder for this article until we know for sure what AMD has decided to call it. However there’s strong indication that this is going to be the new flagship GPU from AMD to lead the charge on the 2015 graphics refresh.");
    std::string b2("prototyping");

    CHECK(Algo::kmp(a,b) == a.find(b));
    CHECK(Algo::kmp(a,b2) == a.length());
    CHECK(Algo::kmp(a2,b2) == a2.find(b2));
    CHECK(Algo::kmp(a2,b) == a2.length());
    CHECK(Algo::kmp(a2,std::string("graphics")) == a2.find("graphics"));
}
