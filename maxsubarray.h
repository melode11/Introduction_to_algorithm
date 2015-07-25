#ifndef MAXSUBARRAY_H
#define MAXSUBARRAY_H
#include <limits>
#include <exception>

namespace Algo
{
    template <typename T>
    struct SubArrayDescriptor
    {
        T* start;
        T* end;
        T sum;
    };


    template <typename T>
    SubArrayDescriptor<T> __MaxSubArrayCrossMiddle(T* start, T* end, T* middle)
    {
        T sum = *middle;
        T max = sum;
        SubArrayDescriptor<T> desc;
        desc.start = middle;
        for(T* i = middle-1;i>=start;--i)
        {
            sum+=*i;
            if(max<sum)
            {
                max = sum;
                desc.start = i;
            }
        }
        sum = max;
        desc.end = middle+1;

        for(T* i = middle+1;i<end;++i)
        {
            sum+=*i;
            if(max<sum)
            {
                max = sum;
                desc.end = i+1;
            }
        }
        desc.sum = max;
        return desc;
    }

    template <typename T>
    SubArrayDescriptor<T> MaxSubArray(T* start,T* end)
    {
        if(end<=start)
        {
            throw std::exception();
        }
        SubArrayDescriptor<T> desc;
        if(start == end - 1)
        {
            desc.start = start;
            desc.end = end;
            desc.sum = *start;
        }
        else
        {
            T* middle = start+(end - start)/2;


            desc = MaxSubArray(start,middle);
            SubArrayDescriptor<T> aux = __MaxSubArrayCrossMiddle(start,end,middle);
            if(aux.sum>desc.sum)
            {
                desc = aux;
            }

            aux = MaxSubArray(middle,end);
            if(aux.sum > desc.sum)
            {
                desc = aux;
            }

        }
        return desc;
    }
}

#endif // MAXSUBARRAY_H

