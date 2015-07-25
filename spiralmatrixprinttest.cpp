#include "catch.hpp"
#include "spiralmatrixprint.h"
#include <iostream>
using namespace Algo;

void testMatrixWithScale(int scale,std::vector<int>& output)
{
    DenseMatrix<int> matrix(scale,scale);
    for(int i = 0;i<scale;++i)
    {
        for(int j = 0;j<scale;++j)
        {
            matrix(i,j) = j*10+i;
        }
    }

    Algo::spiral_matrix_print(matrix,output);

}

TEST_CASE("Spiral matrix print","[spiralmatrixprint]")
{
    std::vector<int> output;
    testMatrixWithScale(1,output);

    testMatrixWithScale(2,output);

    testMatrixWithScale(3,output);

    testMatrixWithScale(4,output);

    testMatrixWithScale(5,output);


    int answer[] = {0,0,1,11,10,0,1,2,12,22,21,20,10,11,0,1,2,3,13,23,33,32,31,30,20,10,11,12,22,21,0,1,2,3,4,14,24,34,44,43,42,41,40,30,20,10,11,12,13,23,33,32,31,21,22};
    std::vector<int> answerVec(answer,answer + sizeof(answer)/sizeof(int));
    CHECK(answerVec == output);
}
