#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H
#include <cstddef>
#include <cassert>
namespace Algo
{
    //col-major matrix
    template <typename T>
    class DenseMatrix
    {
    public:
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
            return data_[x*h_+y];
        }

        T& operator()(size_t x,size_t y)
        {
            assert(x < w_ && y<h_);
            return data_[x*h_+y];
        }

        DenseMatrix(size_t w,size_t h)
            :w_(w),h_(h),data_(new T[w*h])
        {
        }

        DenseMatrix(size_t w,size_t h,const T* data)
            :w_(w),h_(h),data_(malloc(sizeof(T)*w*h))
        {
            for(size_t i = 0,size=w*h;i<size;++i)
            {
                new (data_+i)T(data[i]);
            }
        }

        ~DenseMatrix()
        {
            delete [] data_;
        }

    private:
        size_t w_;
        size_t h_;
        T* data_;
    };
}

#endif // DENSEMATRIX_H

