#include "heapsort.h"
#include <iostream>
#include "catch.hpp"

TEST_CASE("Heapsort is performed","[heapsort]")
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

    Algo::heapsort(data,15);
    int ordered[] = {
        1345,
        755,
        699,
        694,
        635,
        384,
        293,
        273,
        96,
        84,
        57,
        43,
        37,
        32,
        21
    };

    for(size_t i = 0;i<15;++i)
    {
        CHECK(data[i] == ordered[i]);
    }
}


TEST_CASE("Heap with 1 element","[heap]")
{
    int value = 1;
    Algo::Heap<int> heap(&value,1);
    CHECK(heap.Max() == 1);
    CHECK(heap.Size() == 1);
    CHECK(heap.ExtractMax() == 1);
    CHECK(heap.Size() == 0);
    CHECK(heap.Capacity() == 1);
}

TEST_CASE("Heap with 2 element","[heap]")
{
    int value[] = {1,2};
    Algo::Heap<int> heap(value,2);
    CHECK(heap.Max() == 2);
    CHECK(heap.Size() == 2);
    CHECK(heap.ExtractMax() == 2);
    CHECK(heap.Size() == 1);
    CHECK(heap.Max() == 1);
    CHECK(heap.ExtractMax() == 1);
    CHECK(heap.Size() == 0);
    CHECK(heap.Capacity() == 2);
}

TEST_CASE("Heap shrink","[heap]")
{
    int value[] = {4,2,5,4,2};
    Algo::Heap<int> heap(value,5);
    CHECK(heap.ExtractMax() == 5);
    CHECK(heap.ExtractMax() == 4);
    heap.ShrinkToFit();
    CHECK(heap.Size() == 3);
    CHECK(heap.Capacity() == 3);
    CHECK(heap.ExtractMax() == 4);
    CHECK(heap.ExtractMax() == 2);
    CHECK(heap.ExtractMax() == 2);
}
