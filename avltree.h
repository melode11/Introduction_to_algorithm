#ifndef AVLTREE
#define AVLTREE
#include <utility>
#include <vector>
namespace Algo
{
    template <typename K,typename V>
    class AVLTree
    {
    public:
        typedef std::pair<K,V> T;
        typedef struct AVLTreeNode
        {
            AVLTreeNode *left;
            AVLTreeNode *right;
            int height;
            T data;
        } Node;


        const V& Find(K const& k) const;
        void Insert(T&& t);
        void Insert(const T& t);
    private:
        static void LinkLeft(Node* p,Node* l);
        static void LinkRight(Node* p,Node* r);
        static int BalanceFactor(Node* p);
        void RotateLeft(Node* p);
        void RotateRight(Node* p);
        void Rebalance(Node* p);

        Node* FindParent(Node* root,Node* c);
        Node* root_;
    };

    template <typename K,typename V>
    inline void AVLTree<K,V>::LinkLeft(Node* p,Node* l)
    {
        p->left = l;
    }

    template <typename K,typename V>
    inline void AVLTree<K,V>::LinkRight(Node* p,Node* r)
    {
        p->right = r;
    }

    template <typename K,typename V>
    AVLTree<K,V>::Node* AVLTree<K,V>::FindParent(Node* p,Node* c)
    {

        if(c->data > p->data)
        {
            if(p->left == NULL)
            {
                return NULL;
            }
            if(p->left!=c)
            {
                return FindParent(p->left,c);
            }
            else
            {
                return p;
            }
        }
        else
        {
            if(p->right == NULL)
            {
                return NULL;
            }
            if(p->right != c)
            {
                return FindParent(p->right,c);
            }
            else
            {
                return p;
            }
        }
    }

    template <typename K,typename V>
    void AVLTree<K,V>::RotateLeft(Node* p)
    {
        Node* r = p->right;
        if(r == NULL)
        {
            return;
        }
        Node* super = FindParent(root_,p);
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
    }

    template <typename K,typename V>
    void AVLTree<K,V>::RotateRight(Node* p)
    {
        Node* l = p->left;
        if(l == NULL)
        {
            return;
        }
        Node* super = FindParent(root_,p);
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
                LinkRight(super,r);
            }
        }
    }

    template <typename K,typename V>
    int AVLTree<K,V>::BalanceFactor(Node* p)
    {
        int l = p->left == NULL?0:p->left->heigth;
        int r = p->right == NULL? 0: p->right->height;
        return l-r;
    }

    template <typename K,typename V>
    void AVLTree<K,V>::Rebalance(Node* c,std::vector<Node*> const& parents)
    {
        int balanceFactor = p->left->height-p->right->height;
        if(balanceFactor == 2)
        {
            Node* l = p->left;
            int lfactor =l->left->height - l->right->height;
            if(lfactor == 1)
            {
                //single right rotate
            }
            else
            {
                //double right rotate

            }
        }
        else if(balanceFactor == -2)
        {
            Node* r = p->right;
            int rfactor = r->left->height - r->right->height;
            if(rfactor == -1)
            {
                //single left rotate
            }
            else
            {
                //double left rotate
            }
        }
    }
}

#endif // AVLTREE

