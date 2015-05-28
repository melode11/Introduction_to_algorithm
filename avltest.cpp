#include "avltree.h"
#include "catch.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>

const int TEST_DATA_SIZE = 1024;
int* testdata()
{
    static int *testdata = NULL;
    if(testdata == NULL)
    {
        srand(time(NULL));
        testdata = new int[TEST_DATA_SIZE];
        for(int i =0;i<TEST_DATA_SIZE;++i)
        {
            testdata[i] = 10000 * rand()/RAND_MAX;
        }
    }
    return testdata;
}


TEST_CASE("Avl insert","[avl]")
{
    int *data = testdata();

    Algo::AVLTree<int> tree;
    for(int i = 0;i<TEST_DATA_SIZE;++i)
    {
        tree.Insert(data[i]);
    }

    CHECK(tree.Height() < ceil((log2(TEST_DATA_SIZE)) * 1.42) );//height upper bound of avl tree:~= 1.414*logn

    //test data may have duplicated values.
    //so the tree node count <= testdata length, but Has() still works.
    size_t hasCount = 0;
    for(int i = 0;i<TEST_DATA_SIZE;++i)
    {
        if(tree.Has(data[i]))
        {
            ++hasCount;
        }
    }
    CHECK(hasCount == TEST_DATA_SIZE);
    CHECK(!tree.Has(-1));
    CHECK(!tree.Has(10001));
}

struct DumpHandler
{
    DumpHandler(std::vector<int>& out)
        :out_(out)
    {

    }
    void operator()(typename Algo::AVLTree<int>::Node* node)
    {
        out_.push_back(node->data);
    }

    std::vector<int>& out_;
};


TEST_CASE("Avl sort","[avl]")
{
    int *data = testdata();

    Algo::AVLTree<int> tree;
    for(int i = 0;i<TEST_DATA_SIZE;++i)
    {
        tree.Insert(data[i]);
    }
    std::vector<int> sorted;
    tree.InOrderTraversal<DumpHandler>(DumpHandler(sorted));
    bool ordered = true;
    int last = sorted[0];
    for(size_t i = 1;i<sorted.size();++i)
    {
        if(sorted[i]<last)
        {
            CHECK(false);
            break;
        }
        last = sorted[i];
    }
}
