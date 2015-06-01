#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <cstddef>
#include <type_traits>
namespace Algo
{
    template <typename T>
    class LinkedList
    {
    public:
        class Iterator
        {
        protected:
            Node* node_;
            Node* prev_;
        friend class LinkedList;
        public:
            Iterator(Node* node,Node* prev)
                :node_(node),prev_(prev)
            {
            }

            void operator++()
            {
                assert(node_ != NULL);
                prev_ = node_;
                node_ = node_->next;
            }

            bool operator==(Iterator const& rhs)
            {
                this->node_ == rhs.node_ && this->prev_ == rhs.prev_;
            }

            bool operator!=(Iterator const& rhs)
            {
                this->node_ != rhs.node_ || this->prev_!=rhs.prev_;
            }

            T& operator*()
            {
                assert(node_ != NULL);
                return this->node_->data;
            }

            T* operator->()
            {
                assert(node_ != NULL);
                return &(this->node_->data);
            }
        };

        LinkedList():
            size_(0),head_(NULL)
        {
        }

        ~LinkedList()
        {
            Node* n = head_;
            while(n != NULL)
            {
                Node* tmp = n;
                n = n->next;
                delete tmp;
            }
        }

        Iterator Begin()
        {
            return Iterator(head_,NULL);
        }

        Iterator End()
        {
            return Iterator(NULL,NodeAt(size_-1));
        }

        void PushBack(T&& data)
        {
            if(head_ == NULL)
            {
                head_ = new Node(std::move(data));
                size_ = 1;
            }
            else
            {
                Node* last = NodeAt(size_ - 1);
                last->next = new Node(std::move(data));
                ++size_;
            }
        }

        void PushBack(T const& data)
        {
            if(head_ == NULL)
            {
                head_ = new Node(data);
                size_ = 1;
            }
            else
            {
                NodeAt(size_ - 1)->next = new Node(data);
                ++size_;
            }
        }

        void RemoveAt(size_t i)
        {
            assert(i < size_);
            if(i == 0)
            {
                Node* tmp = head_;
                head_ = tmp->next;
                delete tmp;
            }
            else
            {
                Node* tmp = NodeAt(i-1);
                Node* rm = tmp->next;
                tmp->next = tmp->next->next;
                delete rm;
            }
            --size_;
        }

        Iterator RemoveAt(Iterator const& it)
        {
            assert(it.node_!=NULL);
            Node** prevNext = it.prev_ == NULL? &head_ : &(it.prev_->next);
            *prevNext = it.node_->next;
            delete it.node_;
            --size_;
            return Iterator(it.prev_,it.node_->next);
        }

        Iterator Insert(Iterator const& it, T const& value)
        {
            Node** prevNext = it.prev_ == NULL? &head_ : &(it.prev_->next);
            Node* toInsert = new Node(value);
            *prevNext = toInsert;
            toInsert->next = it.node_;
            return Iterator(it.prev_,toInsert);
        }

        Iterator Insert(Iterator const& it, T const& value)
        {
            Node** prevNext = it.prev_ == NULL? &head_ : &(it.prev_->next);
            Node* toInsert = new Node(std::move(value));
            *prevNext = toInsert;
            toInsert->next = it.node_;
            return Iterator(it.prev_,toInsert);
        }

        void Append(T* data, size_t n)
        {
            if(n == 0)
            {
                return;
            }
            Node* last;
            if(head_ == NULL)
            {
                head_ = new Node(data[0]);
                size_ = 1;
                ++data;
                --n;
                last = head_;
            }
            else
            {
                last = NodeAt(size_ - 1);
            }
            for(size_t i = 0;i<n; ++i)
            {
                last->next = new Node(data[i]);
                last = last->next;
            }
            size_+=n;
        }

        void Reverse()
        {
            if(size_<2)
            {
                return;
            }
            Node* tmp = head_;
            Node* next = head_->next;
            tmp->next = NULL;
            Node* nextnext = next->next;
            while(nextnext!=NULL)
            {
                next->next = tmp;
                tmp = next;
                next = nextnext;
                nextnext = next->next;
            }
            next->next = tmp;
            head_ = next;
        }

        size_t Size() const
        {
            return size_;
        }

        T& operator[](size_t i)
        {
            assert(i<size_);
            return NodeAt(i)->data;
        }

        T operator[](size_t i) const
        {
            assert(i<size_);
            return NodeAt(i)->data;
        }

    protected:
        struct Node
        {
            Node* next;
            T data;

            Node(T&& d)
                :next(NULL),data(std::move(d))
            {
            }

            Node(T const& d)
                :next(NULL),data(d)
            {
            }
        };

        Node* NodeAt(size_t i)
        {
            Node* n = head_;
            for(size_t a = 0;a<i;++a)
            {
                n = n->next;
            }
            return n;
        }

        const Node* NodeAt(size_t i) const
        {
            Node* n = head_;
            for(size_t a = 0;a<i;++a)
            {
                n = n->next;
            }
            return n;
        }

    friend class Iterator;
    private:
        size_t size_;
        Node* head_;
    };
}
#endif // LINKEDLIST_H

