#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <cstddef>
#include <cassert>
#include "linkedlist.h"

namespace Algo
{
    template <typename T>
    class SparseMatrix
    {
    public:
        SparseMatrix(size_t w,size_t h):
        w_(w),h_(h),lists_(new LinkedList<RowNode>[h])
        {
        }

        ~SparseMatrix()
        {
            delete lists_;
        }

        size_t Width()
        {
            return w_;
        }

        size_t Height() const
        {
            return h_;
        }

        T operator()(size_t x,size_t y) const
        {
            assert(x < w_ && y<h_);
            LinkedList<RowNode>* listptr = lists_+y;
            for(LinkedList<RowNode>::Iterator it = listptr->Begin();it!=listptr->End();++it)
            {
                if(x<it->x)
                {
                    return 0;
                }
                else if(x == it->x)
                {
                    return it->data;
                }
            }
            return 0;
        }

        void Set(size_t x,size_t y, T const& value)
        {
            assert(x < w_ && y<h_);
            LinkedList<RowNode>* listptr = lists_+y;

            for(LinkedList<RowNode>::Iterator it = listptr->Begin();it!=listptr->End();++it)
            {
                if(x<it->x)
                {
                    listptr->Insert(it,value);
                    return;
                }
                else if(x == it->x)
                {
                   it->data = value;
                   return;
                }
            }
        }

        void Set(size_t x,size_t y, T&& value)
        {
            assert(x < w_ && y<h_);
            if(x<it->x)
            {
                listptr->Insert(it,std::move(value));
                return;
            }
            else if(x == it->x)
            {
               it->data =std::move(value);
               return;
            }
        }

    private:
        size_t w_;
        size_t h_;

        struct RowNode
        {
            size_t x;
            T data;
        };

        LinkedList<RowNode>* lists_;
    };
}
#endif // SPARSEMATRIX_H

