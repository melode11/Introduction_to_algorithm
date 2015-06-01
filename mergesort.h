#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>
#include <algorithm>

namespace Algo
{
    template <typename T>
    void __mergesort(std::vector<T>& data, size_t start, size_t end,std::vector<T>& aux)
    {
        if(end - start <= 1)
        {
            return;
        }
        size_t middle = (end - start)/2 + start;
        __mergesort(data,start,middle,aux);
        __mergesort(data,middle,end,aux);
        //merge:
        size_t pos = start;
        for(size_t i = start,j = middle;pos<end;)
        {
            if(i<middle&&j<end)
            {
                if(data[i]<data[j])
                {
                    aux[pos] = data[i];
                    ++i;
                }
                else
                {
                    aux[pos] = data[j];
                    ++j;
                }
            }
            else if(i<middle)
            {
                aux[pos] = data[i];
                ++i;
            }
            else
            {
                aux[pos] = data[j];
                ++j;
            }
            ++pos;
        }
        std::copy(aux.begin()+start,aux.begin()+end,data.begin()+start);
    }

    template <typename T>
    void mergesort(std::vector<T>& data)
    {
        std::vector<T> aux(data.size());
        __mergesort(data,0,data.size(),aux);
    }

}

#endif // MERGESORT_H

