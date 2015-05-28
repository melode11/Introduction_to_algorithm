#ifndef AVLTREE
#define AVLTREE
#include <utility>
#include <vector>
#include <cassert>
#include <iostream>
namespace Algo
{
    template <typename T>
    class AVLTree
    {
    public:
        typedef struct AVLTreeNode
        {
            AVLTreeNode *left;
            AVLTreeNode *right;
            int height;
            T data;

            AVLTreeNode(T const& d):
                left(NULL),
                right(NULL),
                height(0),
                data(d)
            {}

            AVLTreeNode(T&& d):
                left(NULL),
                right(NULL),
                height(0),
                data(std::move(d))
            {}

        } Node;

        enum LinkPos
        {
            kPosReplace,
            kPosLeft,
            kPosRight
        };

        typedef struct AVLTreePosition
        {
            AVLTreeNode* parent;
            LinkPos linkPos;
        } Position;

        AVLTree();
        ~AVLTree();
        bool Has(T const& t) const;
        void Insert(T&& t);
        void Insert(const T& t);
        int Height() const;

        void Dump(std::ostream& os) const;

        template <typename Handler>
        void InOrderTraversal(Handler&& handler);

        template <typename Handler>
        void InOrderTraversal(Handler& handler);
    private:
        static void LinkLeft(Node* p,Node* l);
        static void LinkRight(Node* p,Node* r);
        static int BalanceFactor(Node* p);
        static int CalcHeight(Node const* p);
        void Insert(Node* node,Position& pos,std::vector<Node*>const & ancestors);
        void RotateLeft(Node* p,Node* pp=NULL);
        void RotateRight(Node* p,Node* pp=NULL);
        void Rebalance(std::vector<Node*> const& ancestors);
        bool RebalanceNode(Node* c,Node* p);
        void UpdateHeightUp(typename std::vector<Node*>::const_iterator begin,typename std::vector<Node*>::const_iterator end);
        static Position FindPostion(T const& data,Node* p,std::vector<Node*>* ancestors=NULL);
        Node* FindParent(Node* c,Node* p);
        void DumpNode(std::ostream& os, Node* node) const;

        template <typename Handler>
        static void Traversal(Node* p,Handler& handler)
        {
            if(p == NULL)
            {
                return;
            }
            Traversal(p->left,handler);
            handler(p);
            Traversal(p->right,handler);
        }

        Node* root_;
    };

    template <typename T>
    AVLTree<T>::AVLTree()
        :root_(NULL)
    {

    }

    template <typename T>
    void DeleteNode(typename AVLTree<T>::Node* p)
    {
        delete p;
    }

    template <typename T>
    AVLTree<T>::~AVLTree()
    {
        Traversal(root_,DeleteNode<T>);
        root_ = NULL;
    }

    template <typename T>
    inline void AVLTree<T>::LinkLeft(Node* p,Node* l)
    {
        p->left = l;
    }

    template <typename T>
    inline void AVLTree<T>::LinkRight(Node* p,Node* r)
    {
        p->right = r;
    }

    template <typename T>
    typename AVLTree<T>::Position AVLTree<T>::FindPostion(T const& data,Node* p,std::vector<Node*>* ancestors)
    {
        assert(p!=NULL);
        if(data < p->data)
        {
            if(p->left!=NULL)
            {
                if(ancestors)ancestors->insert(ancestors->begin(),p);
                return FindPostion(data,p->left,ancestors);
            }
            else
            {
                if(ancestors)ancestors->insert(ancestors->begin(),p);
                return {p,kPosLeft};
            }
        }
        else if(data > p->data)
        {

            if(p->right != NULL)
            {
                if(ancestors)ancestors->insert(ancestors->begin(),p);
                return FindPostion(data,p->right,ancestors);
            }
            else
            {
                if(ancestors)ancestors->insert(ancestors->begin(),p);
                return {p,kPosRight};
            }
        }
        else //==
        {
            return {p,kPosReplace};
        }
    }

    template <typename T>
    int AVLTree<T>::CalcHeight(Node const* p)
    {
        int l = p->left == NULL?-1:p->left->height;
        int r = p->right == NULL?-1:p->right->height;
        return l>r?l+1:r+1;
    }

    template <typename T>
    void AVLTree<T>::UpdateHeightUp(typename std::vector<Node*>::const_iterator begin,typename std::vector<Node*>::const_iterator end)
    {
        for(typename std::vector<Node*>::const_iterator it = begin;it!=end;++it)
        {
            Node* p = *it;
            int calced = CalcHeight(p);
            if(calced == p->height)
            {
                break;
            }
            p->height = calced;
        }
    }

    template <typename T>
    typename AVLTree<T>::Node* AVLTree<T>::FindParent(Node* c,Node* p)
    {
        if(p == NULL)
        {
            return NULL;
        }
        std::vector<Node*> ancestors;
        AVLTreePosition pos = FindPostion(c->data,p,&ancestors);
        if(pos.linkPos != kPosReplace || ancestors.size() == 0)
        {
            return NULL;
        }
        return ancestors.front();
    }

    template <typename T>
    void AVLTree<T>::RotateLeft(Node* p,Node* pp)
    {
        Node* r = p->right;
        if(r == NULL)
        {
            return;
        }
        Node* super = pp == NULL? FindParent(p,root_) : pp;
        Node* rleft = r->left;
        LinkLeft(r,p);
        LinkRight(p,rleft);

        if(super != NULL)
        {
            if(super->left == p)
            {
                LinkLeft(super,r);
            }
            else
            {
                LinkRight(super,r);
            }
        }
        else
        {
            root_ = r;
        }
    }

    template <typename T>
    void AVLTree<T>::RotateRight(Node* p,Node* pp)
    {
        Node* l = p->left;
        if(l == NULL)
        {
            return;
        }
        Node* super = pp == NULL? FindParent(p,root_) : pp;
        Node* lRight = l->right;
        LinkRight(l,p);
        LinkLeft(p,lRight);
        if(super!=NULL)
        {
            if(super->left == p)
            {
                LinkLeft(super,l);
            }
            else
            {
                LinkRight(super,l);
            }
        }
        else
        {
            root_ = l;
        }
    }

    template <typename T>
    int AVLTree<T>::BalanceFactor(Node* p)
    {
        int l = p->left == NULL?-1:p->left->height;
        int r = p->right == NULL? -1: p->right->height;
        return l-r;
    }

    template <typename T>
    bool AVLTree<T>::RebalanceNode(Node* c,Node* p)
    {
        int balanceFactor = BalanceFactor(c);
        if(balanceFactor == 2)
        {
            Node* l = c->left;
            int lfactor =BalanceFactor(l);
            if(lfactor == 1)
            {
                //single right rotate
                RotateRight(c,p);
            }
            else
            {
                //zig-zag routine
                RotateLeft(l,c);
                RotateRight(c,p);
            }
            c->height = CalcHeight(c);
            l->height = CalcHeight(l);
            return true;//conitinue going up
        }
        else if(balanceFactor == -2)
        {
            Node* r = c->right;
            int rfactor = BalanceFactor(r);
            if(rfactor == -1)
            {
                //single left rotate
                RotateLeft(c,p);
            }
            else
            {
                //zig-zag routine
                RotateRight(r,c);
                RotateLeft(c,p);
            }
            c->height = CalcHeight(c);
            r->height = CalcHeight(r);
            return true;//conitinue going up
        }
        else
        {
            return false;//stop
        }
    }


    template <typename T>
    void AVLTree<T>::Rebalance(std::vector<Node*> const& ancestors)
    {
        for(size_t  i = 0;i<ancestors.size()-1;++i)
        {
            Node* p = ancestors[i];
            if(!RebalanceNode(p,ancestors[i+1]))
            {
                return;
            }
            UpdateHeightUp(ancestors.begin()+i+1,ancestors.end());
        }
        RebalanceNode(ancestors.back(),NULL);
    }

    template <typename T>
    bool AVLTree<T>::Has(T const& t) const
    {
        if(root_ == NULL)
        {
            return false;
        }
        Position pos =  FindPostion(t,root_);
        return pos.linkPos == kPosReplace;
    }

    template <typename T>
    int AVLTree<T>::Height() const
    {
        return root_->height;
    }

    template <typename T>
    void AVLTree<T>::Insert(T&& t)
    {
        if(root_ == NULL)
        {
            root_ = new Node(std::move(t));
            return;
        }
        std::vector<Node*> ancestors;
        Position pos = FindPostion(t,root_,&ancestors);
        if(pos.linkPos == kPosReplace)
        {
            //this parent's data is going to be replaced.
            pos.parent->data = std::move(t);
        }
        else
        {
            if(ancestors.size()>0)
            {
                ancestors.erase(ancestors.begin());
            }
            Node* newnode = new Node(std::move(t));
            Insert(newnode,pos,ancestors);
        }
    }

    template <typename T>
    void AVLTree<T>::Insert(const T& t)
    {
        if(root_ == NULL)
        {
            root_ = new Node(t);
            return;
        }
        std::vector<Node*> ancestors;
        Position pos = FindPostion(t,root_,&ancestors);
        if(pos.linkPos == kPosReplace)
        {
            //this parent's data is going to be replaced.
            pos.parent->data = t;
        }
        else
        {
            if(ancestors.size()>0)
            {
                ancestors.erase(ancestors.begin());
            }
            Node* newnode = new Node(t);
            Insert(newnode,pos,ancestors);
        }
    }

    template <typename T>
    void AVLTree<T>::Insert(Node* node, Position& pos,std::vector<Node*>const & ancestors)
    {
        if(pos.linkPos == kPosLeft)
        {
            LinkLeft(pos.parent,node);
        }
        else
        {
            LinkRight(pos.parent,node);
        }
        pos.parent->height = CalcHeight(pos.parent);
        UpdateHeightUp(ancestors.begin(),ancestors.end());
        Rebalance(ancestors);
    }

    template <typename T>
    void AVLTree<T>::DumpNode(std::ostream& os, Node* node) const
    {
        if(node == NULL)
        {
            os<<"x(#) ";
        }
        else
        {
            os<<node->data<<'('<<node->height<<')'<<" ";
        }
    }

    template <typename T>
    void AVLTree<T>::Dump(std::ostream& os) const
    {
        std::vector<Node*> level;
        level.push_back(root_);
        bool allNull = false;
        while(!allNull)
        {
            std::vector<Node*> tmp;
            allNull = true;
            for(size_t i = 0;i<level.size();++i)
            {
                DumpNode(os,level[i]);
                if(level[i] == NULL)
                {
                    tmp.push_back(NULL);
                    tmp.push_back(NULL);
                    continue;
                }
                Node* l = level[i]->left, *r = level[i]->right;
                if(l||r)
                {
                    allNull = false;
                }
                tmp.push_back(l);
                tmp.push_back(r);
            }
            os<<std::endl;
            level = std::move(tmp);
        };
    }

    template <typename T>
    template <typename Handler>
    void AVLTree<T>::InOrderTraversal(Handler&& handler)
    {
        Traversal(root_,handler);
    }

    template <typename T>
    template <typename Handler>
    void AVLTree<T>::InOrderTraversal(Handler& handler)
    {
        Traversal(root_,handler);
    }
}

#endif // AVLTREE

