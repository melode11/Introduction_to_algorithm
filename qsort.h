#ifndef QSORT_H
#define QSORT_H
#include <iostream>
namespace Algo
{
    template <typename T> T* __qpartition(T* start, T* end)
    {
        T x = *(end-1);
        T *p = start;
        for(T* i = start;i<end-1;++i)
        {
            if(*i < x)
            {
                T tmp = *p;
                *p = *i;
                *i = tmp;
                p++;
            }
        }
        *(end-1) = *p;
        *p = x;
        return p;
    }


    template <typename T>
    void qsort(T* start, T* end)
    {
        if(start >= end -1)
        {
            return;
        }
        T* q = __qpartition(start,end);

        std::cout<<std::endl;
        qsort(start,q);
        qsort(q+1,end);
    }
}

#endif // QSORT_H

