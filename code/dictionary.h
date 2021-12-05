#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
#include "BinaryTree.h"
#include <functional>
#include <exception>
#include <utility>
#include <iostream>

template<class TKey, class TElement>
class TPair
{
public:
    TKey key;
    TElement element;

    TPair() = default;

    TPair(TKey key, TElement element)
    {
        this->key = key;
        this->element = element;
    }

    TPair(pair<TKey, TElement> p)
    {
        this->key = p.first;
        this->element = p.second;
    }

    TKey GetKey()
    {
        return this->key;
    }

    TElement& GetElement()
    {
        return this->element;
    }

    void SetKey(TKey key)
    {
        this->key = key;
    }

    void SetElement(TElement element)
    {
        this->element = element;
    }

    bool operator==(TPair<TKey, TElement> p1)
    {
        return ((this->GetKey() == p1.GetKey()));
    }

    bool operator!=(TPair<TKey, TElement> &p1)
    {
        return ((this->GetKey() != p1.GetKey()));
    }
};

template<class TKey, class TElement>
class IDictionary
{
    friend class TPair<TKey, TElement>;
private:
    BinaryTree<TPair<TKey, TElement>>* tree;
    function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp;

public:
    IDictionary()
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>();
    }

    IDictionary(function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>();
        this->cmp = cmp;
    }

    IDictionary(int n, function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>(n, cmp);
        this->SetCmp(cmp);
    }

    IDictionary(IDictionary<TKey, TElement>* d)
    {
        this->tree = new BinaryTree<TPair<TKey, TElement>>(d->GetTree());
        this->SetCmp(d->GetCmp());
    }

    int GetCount()
    {
        return this->tree->GetS();
    }

    BinaryTree<TPair<TKey, TElement>>* GetTree()
    {
        return this->tree;
    }

    function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> GetCmp()
    {
        return this->cmp;
    }

    bool ContainsKey(TKey key)
    {
        TPair<TKey, TElement> p;
        p.SetKey(key);
        if (this->tree->Contains(p, cmp) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ContainsElement(TElement element)
    {
        TPair<TKey, TElement> p;
        p.SetElement(element);
        if (this->tree->Contains(p, cmp) == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    TElement& Get(TKey key)
    {
        TPair<TKey, TElement> p;
        p.SetKey(key);
        if (this->tree->Contains(p, cmp) == 1)
        {
            return (this->tree->Find(p, cmp))->Get().GetElement();
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }

    void SetCmp(function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp)
    {
        this->cmp = cmp;
    }

    void Add(TKey key, TElement element)
    {
        TPair<TKey, TElement> p;
        p.SetKey(key);
        p.SetElement(element);
        this->tree->Add(p, cmp);
    }

    void Add(TPair<TKey, TElement> p)
    {
        this->tree->Add(p, cmp);
    }

    void Remove(TKey key)
    {
        TPair<TKey, TElement> p;
        p.SetKey(key);
        if (this->tree->Contains(p, cmp) == 1)
        {
            this->tree->Remove(p, cmp);
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }


    void Increase(TKey key)
    {
        TPair<TKey, TElement> p;
        p.SetKey(key);
        if (this->tree->Contains(p, cmp) == 1)
        {
            this->Get(key)++;
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }


};


#endif // DICTIONARY_H_INCLUDED
