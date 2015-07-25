#ifndef SELECTKTHVALUE_H
#define SELECTKTHVALUE_H
#include <cstddef>
namespace Algo
{
    template<typename T>
    T* __select_kth_partition(T* start,T* end)
    {
        T x = *(end -1);
        T* p = start;
        for(T* i = start;i<end - 1;++i)
        {
            if(*i < x)
            {
                T tmp = *i;
                *i = *p;
                *p = tmp;
                ++p;
            }
        }
        *(end - 1) = *p;
        *p = x;
        return p;
    }

    template<typename T>
    T* select_kth_value(T* start,T* end, size_t k)
    {
        if(end - start < k)
        {
            return end;
        }
        T* q = __select_kth_partition(start,end);
        size_t l = q - start;
        if(l == k)
        {
            return q;
        }
        else if(l < k)
        {
            return select_kth_value(q+1,end,k);
        }
        else
        {
            return select_kth_value(start,q,k);
        }
    }
}

#endif // SELECTKTHVALUE_H

