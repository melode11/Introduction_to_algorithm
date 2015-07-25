#ifndef SPIRALMATRIXPRINT_H
#define SPIRALMATRIXPRINT_H
#include "densematrix.h"
#include <vector>
namespace Algo
{
    template<typename T>
    void __print_ring(DenseMatrix<T> const& matrix,int x, int y, int col,int row,std::vector<T>& output)
    {
        if(col == 0 || row == 0 || col!=row)
        {
            return;
        }
        if(col == 1)
        {
            output.push_back(matrix(x,y));
            return;
        }
        for(int i =0;i<col - 1;++i)
        {
             output.push_back(matrix(x+i,y));
        }

        for(int i =0;i<row - 1;++i)
        {
             output.push_back(matrix(x+col-1,y+i));
        }

        for(int i = col - 1 ;i>0;--i)
        {
             output.push_back(matrix(x+i,y+row-1));
        }
        for(int i = row - 1;i>0;--i)
        {
            output.push_back(matrix(x,y+i));
        }
        __print_ring(matrix,x + 1,y + 1,col - 2,row-2,output);
    }

    template<typename T>
    void spiral_matrix_print(DenseMatrix<T> const& matrix,std::vector<T>& output)
    {
        __print_ring(matrix,0,0,(int)matrix.Width(),(int)matrix.Height(),output);
    }
}

#endif // SPIRALMATRIXPRINT_H

