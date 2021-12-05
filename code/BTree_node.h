#ifndef BTREE_NODE_H_INCLUDED
#define BTREE_NODE_H_INCLUDED
#include "SEQUENCE.H"
#include <utility>
#include <functional>
#include <vector>

template<class T>
class BTreeNode
{
    //friend class BTree<T>;
private:
    Sequence<T>* k;
    Sequence<BTreeNode<T>*>* c;
    int t;
    int sizeNode;
    bool leaf = 0;

public:
    BTreeNode()
    {
        this->k = new ArraySequence<T>();
        this->c = new ArraySequence<BTreeNode<T>*>();
        this->sizeNode = 0;
    }

    BTreeNode(bool leaf)
    {
        this->leaf = leaf;
    }

    BTreeNode(T item)
    {
        this->k->Add(item);
        this->sizeNode++;
    }

    BTreeNode(Sequence<T>* k, BTreeNode<T>** c, int t, int sizeNode, bool leaf)
    {
        this->k = new ArraySequence<T>(k);
        this->c = new ArraySequence<BTreeNode<T>*>(2 * t);
        this->c = c;
        this->t = t;
        this->sizeNode = sizeNode;
        this->leaf = leaf;
    }

    BTreeNode(BTreeNode<T>* n)
    {
        this->k = n->k;
        this->c = n->c;
        this->sizeNode = n->sizeNode;
        this->t = n->sizeNode;
        this->leaf = n->leaf;
    }

    BTreeNode(BTreeNode<T>& n)
    {
        this->k = n.k;
        this->c = n.c;
        this->sizeNode = n.sizeNode;
        this->t = n.sizeNode;
        this->leaf = n.leaf;
    }

    BTreeNode (int t, bool leaf)
    {
        this->t = t;
        this->leaf = leaf;
        this->k = new ArraySequence<T>(2 * t - 1);
        this->c = new ArraySequence<BTreeNode<T>*>(2 * t);
        this->sizeNode = 0;
    }

    Sequence<T>* GetK()
    {
        return this->k;
    }

    Sequence<BTreeNode<T>*>* GetC()
    {
        return this->c;
    }

    int GetN()
    {
        return this->sizeNode;
    }

    void SetN(int n)
    {
        this->sizeNode = n;
    }

    void ToVector(vector<T>* v)
    {
        int i = 0;
        for (i = 0; i < sizeNode; i++)
        {
            if (this->leaf == false)
            {
                if (c->Get(i) != nullptr && c != nullptr)
                {
                    c->Get(i)->ToVector(v);
                }
            }
            v->push_back(this->GetK()->Get(i));
        }

        if(this->leaf == false)
        {
            if (c != nullptr && c->Get(i) != nullptr)
            {
                c->Get(i)->ToVector(v);
            }
        }
    }

    BTreeNode<T>* Search(T key, function<bool(T, T)> cmp)
    {
        int i = 0;

        while (i < this->sizeNode && cmp(this->k->Get(i), key))
        {
            i++;
        }

        if (this->k->Get(i) == key)
        {
            return this;
        }

        if (leaf == true)
        {
            return nullptr;
        }
        return c->Get(i)->Search(key, cmp);
    }

    void InsertFree(T key, function<bool(T, T)> cmp)
    {
        int i = sizeNode - 1;
        if (leaf == true)
        {
            while (i >= 0 && cmp(key, k->Get(i)))
            {
                k->Set(i + 1, k->Get(i));
                i--;
            }
            k->Set(i + 1, key);
            sizeNode++;
        }

        else
        {
            while (i >= 0 && cmp(key, k->Get(i)))
            {
                i--;
            }
            if (c->Get(i + 1)->GetN() == (2 * t - 1))
            {
                this->SplitC(i + 1, c->Get(i + 1));
                if (cmp(k->Get(i + 1), key))
                {
                    i++;
                }
            }
            c->Get(i + 1)->InsertFree(key, cmp);
        }
    }

    void SplitC(int i, BTreeNode<T>* n1)
    {
        BTreeNode<T>* n2 = new BTreeNode(n1->t, n1->leaf);
        n2->sizeNode = (t - 1);
        for (int j = 0; j < (t - 1); j++)
        {
            n2->k->Set(j, n1->k->Get(j + t));
        }
        if (n1->leaf == false)
        {
            for (int j = 0;  j < t; j++)
            {
                n2->c->Set(j, n1->c->Get(j + t));
            }
        }

        n1->SetN(t - 1);

        for (int j = this->sizeNode; j >= (i + 1); j--)
        {
            c->Set(j + 1, c->Get(j));
        }

        c->Set(i + 1, n2);

        for (int j = (this->sizeNode - 1); j >= i; j--)
        {
            k->Set(j + 1, k->Get(j));
        }

        k->Set(i, n1->GetK()->Get(t - 1));
        this->sizeNode++;
    }
};


#endif // BTREE_NODE_H_INCLUDED
