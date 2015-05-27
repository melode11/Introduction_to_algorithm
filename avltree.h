#ifndef AVLTREE
#define AVLTREE
#include <utility>
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
            size_t height;
            T data;
        } Node;

        void RotateLeft(Node* p);
        void RotateRight(Node* p);
        const V& Find(K const& k) const;
        void Insert(T&& t);
        void Insert(const T& t);
    private:
        static void LinkLeft(Node* p,Node* l);
        static void LinkRight(Node* p,Node* r);
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
}

#endif // AVLTREE

