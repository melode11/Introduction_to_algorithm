#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "heap.h"
namespace Algo
{
    template <typename T>
    void heapsort(T* array,size_t n)
    {
        Heap<T> heap(array,n);
        for(size_t i=0;i<n;++i)
        {
            array[i] = heap.ExtractMax();
        }
    }
}
#endif // HEAPSORT_H

