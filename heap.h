#ifndef HEAP_H
#define HEAP_H
#include <utility>
#include <algorithm>
#include <cassert>
#include <memory>
#include <cstdlib>
namespace Algo
{
    template <typename T>
    class Heap
    {
    public:
        Heap(T const* unordered,size_t n);

        ~Heap();

        const T& Max() const;

        T ExtractMax();

        void Insert(T const& value);

        void Insert(T&& value);

        size_t Size() const;

        size_t Capacity() const;

        void ShrinkToFit();
    private:
        static size_t Left(size_t i);
        static size_t Right(size_t i);
        static size_t Parent(size_t i);
        void Swap(size_t i,size_t j);
        void BuildMaxHeap();
        void MaxHeapify(size_t i);
        void BubbleUp(size_t i);
        void ExpandBy(size_t expand_size);
        T *buf_;
        size_t capacity_;
        size_t size_;
        std::allocator<T>  allocator_;
    };
    template <typename T>
    Heap<T>::Heap(T const* unordered,size_t n):
        buf_(NULL),
        capacity_(n),
        size_(n),
        allocator_()
    {
        if(n>0)
        {
            buf_ = allocator_.allocate(n);
            for(size_t i = 0;i<n;++i)
            {
                allocator_.construct(buf_+i,unordered[i]);
            }
        }
        BuildMaxHeap();
    }

    template <typename T>
    Heap<T>::~Heap()
    {
        if(buf_ != NULL)
        {
        for(size_t i =0;i<size_;++i)
        {
            allocator_.destroy(buf_+i);
        }
        allocator_.deallocate(buf_,capacity_);
        }
    }

    template <typename T>
    size_t Heap<T>::Left(size_t i)
    {
        return i*2 +1;
    }

    template <typename T>
    size_t Heap<T>::Right(size_t i)
    {
        return i*2+2;
    }

    template <typename T>
    size_t Heap<T>::Parent(size_t i)
    {
        assert(i>0);
        return (i-1)/2;
    }

    template <typename T>
    void Heap<T>::Swap(size_t i,size_t j)
    {
        T tmp(std::move(buf_[i]));
        buf_[i] = std::move(buf_[j]);
        buf_[j] = std::move(tmp);
    }

    template <typename T>
    void Heap<T>::MaxHeapify(size_t i)
    {
        if(size_<2 || i>(size_/2-1))
        {
            return;
        }
        size_t l = Left(i),r=Right(i);
        if( r>=size_ || buf_[l]>buf_[r])
        {
            if(buf_[l]>buf_[i])
            {
                Swap(l,i);
                MaxHeapify(l);
            }
        }
        else
        {
            if(buf_[r]>buf_[i])
            {
                Swap(r,i);
                MaxHeapify(r);
            }
        }
    }

    template <typename T>
    void Heap<T>::BuildMaxHeap()
    {
        if(size_<=1)
        {
            return;
        }
        for(int i = size_/2-1;i>=0;--i)
        {
            MaxHeapify(i);
        }
    }

    template <typename T>
    const T& Heap<T>::Max() const
    {
        assert(size_>0);
        return buf_[0];
    }

    template <typename T>
    T Heap<T>::ExtractMax()
    {
        assert(size_>0);
        T tmp(std::move(buf_[0]));
        --size_;
        if(size_>0)
        {
            buf_[0] = std::move(buf_[size_]);//swap the item behind the last element with root.
            MaxHeapify(0);
        }
        allocator_.destroy(buf_+size_);
        return tmp;
    }

    template <typename T>
    void Heap<T>::ShrinkToFit()
    {
        if(size_ > 0)
        {
            //buf_ = realloc(buf_,size_*sizeof(T));//check if this is safe
            T* tmp = allocator_.allocate(size_);
            for(size_t i = 0;i<size_;++i)
            {
                allocator_.construct(tmp+i,std::move(buf_[i]));
                allocator_.destroy(buf_+i);
            }
            allocator_.deallocate(buf_,capacity_);
            capacity_ = size_;
            buf_ = tmp;
        }
        else
        {
            allocator_.deallocate(buf_,capacity_);
            buf_= NULL;
            capacity_ = 0;
        }
    }

    template <typename T>
    void Heap<T>::BubbleUp(size_t i)
    {
        if(i == 0)
        {
            return;//no need to bubble up root.
        }
        size_t p = Parent(i);
        if(buf_[i]>buf_[p])
        {
            Swap(i,p);
            BubbleUp(p);
        }
    }

    template <typename T>
    void Heap<T>::ExpandBy(size_t expand_size)
    {
        if(buf_==NULL)
        {
            buf_=allocator_.allocate(expand_size);
            capacity_ = expand_size;
        }
        else
        {
            size_t cap = capacity_ + expand_size;
            T* tmp = allocator_.allocate(cap);
            for(size_t i = 0;i<size_;++i)
            {
                allocator_.construct(tmp+i,std::move(buf_[i]));
                allocator_.destroy(buf_+i);
            }
            allocator_.deallocate(buf_,capacity_);
            buf_ = tmp;
            capacity_ = cap;
        }
    }

    template <typename T>
    void Heap<T>::Insert(T &&value)
    {
        if(capacity_ == size_)
        {
            ExpandBy(16);
        }
        buf_[size_] = std::move(value);
        ++size_;
        BubbleUp(size_-1);
    }

    template <typename T>
    void Heap<T>::Insert(const T &value)
    {
        if(capacity_ == size_)
        {
            ExpandBy(16);
        }
        buf_[size_] = value;
        ++size_;
        BubbleUp(size_-1);
    }

    template <typename T>
    size_t Heap<T>::Size() const
    {
        return size_;
    }

    template <typename T>
    size_t Heap<T>::Capacity() const
    {
        return capacity_;
    }

}
#endif // HEAP_H
