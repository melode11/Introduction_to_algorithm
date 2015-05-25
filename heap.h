#ifndef HEAP_H
#define HEAP_H
#include <utility>
#include <algorithm>
namespace Algo
{
template <typename K,typename V>
class Heap
{
public:
    Heap(std::pair<K,V> const* unordered,size_t n);

    ~Heap();

    const std::pair<K,V>& Max() const;
private:
    static size_t Left(size_t i);
    static size_t Right(size_t i);
    static size_t Parent(size_t i);
    void Swap(size_t i,size_t j);
    void BuildMaxHeap();
    void MaxHeapify(size_t i);
    std::pair<K,V> *pairs_;
    size_t capacity_;
    size_t size_;
};
template <typename K,typename V>
Heap<K,V>::Heap(std::pair<K,V> const* unordered,size_t n):
    capacity_(n),
    size_(n)
{
    pairs_ = new std::pair<K,V>[capacity_];
    std::copy(unordered,unordered+n,pairs_);
}

template <typename K,typename V>
Heap<K,V>::~Heap()
{
    delete [] pairs_;
}

template <typename K,typename V>
size_t Heap<K,V>::Left(size_t i)
{
    return i*2 +1;
}

template <typename K,typename V>
size_t Heap<K,V>::Right(size_t i)
{
    return i*2+2;
}

template <typename K,typename V>
size_t Heap<K,V>::Parent(size_t i)
{
    return (i-1)/2
}

template <typename K,typename V>
void Heap<K,V>::Swap(size_t i,size_t j)
{
    std::pair tmp(std::move(pairs_[i]));
    pairs_[i] = std::move(pairs_[j]);
    pairs_[j] = std::move(tmp);
}

template <typename K,typename V>
void Heap<K,V>::MaxHeapify(size_t i)
{
    if(i>(size_/2-1))
    {
        return;
    }
    if(pairs_[Left(i)].first>pairs_[Right(i)].first)
    {
        if(pairs_[Left(i)].first>pairs_[i].first)
        {
            Swap(Left(i),i);
            MaxHeapify(Left(i));
        }
    }
    else
    {
        if(pairs_[Right(i)].first>pairs_[i].first)
        {
            Swap(Right(i),i);
            MaxHeapify(Right(i));
        }
    }
}

template <typename K,typename V>
void Heap<K,V>::BuildMaxHeap()
{
    for(size_t i = size_/2-1;i>=0;--i)
    {
        MaxHeapify(i);
    }
}

template <typename K,typename V>
const std::pair<K,V>& Heap<K,V>::Max() const
{
    return pairs_[0];
}
}
#endif // HEAP_H
