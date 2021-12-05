#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "SEQUENCE.H"
#include "LinkedListSequence.h"
#include "ArraySequence.h"
#include "BTree_node.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

template<class T>
class BTree
{
    friend class BTreeNode<T>;
public:
    BTree(int t)
    {
        this->root = nullptr;
        this->t = t;
        this->size = 0;
    }

    void ToVector(vector<T>* v)
    {
        if (this->root != nullptr)
        {
            this->root->ToVector(v);
        }
    }

    BTreeNode<T>* Search(T key, function<bool(T, T)> cmp)
    {
        if (this->root != nullptr)
        {
            return this->root->Search(key, cmp);
        }
        else
        {
            return nullptr;
        }
    }

    void Insert(T key, function<bool(T, T)> cmp)
    {
        if (this->root == nullptr)
        {
            this->root = new BTreeNode<T>(t, true);
            root->GetK()->InsertAt(key, 0);
            root->SetN(1);
        }
        else
        {
            if (root->GetN() == (2 * t - 1))
            {
                BTreeNode<T>* s = new BTreeNode<T>(t, false);
                s->GetC()->Set(0, root);
                s->SplitC(0, root);
                int i = 0;
                if (cmp((s->GetK()->Get(0)), key))
                {
                    i++;
                }
                s->GetC()->Get(i)->InsertFree(key, cmp);

                this->root = s;
            }
            else
            {
                root->InsertFree(key, cmp);
            }
        }
    }

    int GetT()
    {
        return this->t;
    }

    int GetSize()
    {
        return this->size;
    }
private:
    BTreeNode<T>* root;
    int size;
    int t;
};


#endif // BTREE_H_INCLUDED
