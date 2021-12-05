#ifndef SPARSEVECTORDICT_H_INCLUDED
#define SPARSEVECTORDICT_H_INCLUDED
#include "sparse_vector.h"
#include "dictionary.h"

template<class T>
class SparseVectorDict: public SparseVector <T>
{
private:
    IDictionary<int, T>* d;
    int capacity;
    int size = 0;
    T null;
    function<bool(TPair<int, T>, TPair<int, T>)> cmp;

public:
    SparseVectorDict(function<bool(TPair<int, T>, TPair<int, T>)> cmp)
    {
        this->d = new IDictionary<int, T>(cmp);
    }

    SparseVectorDict(vector<T>* v, T null, function<bool(TPair<int, T>, TPair<int, T>)> cmp)
    {
        this->d = new IDictionary<int, T>(cmp);
        this->capacity = v->size();
        this->null = null;
        this->cmp = cmp;
        int j = 0;
        for (int i = 0; i < this->capacity; i++)
        {
            if (v->at(i) != null)
            {
                d->Add(j, v->at(i));
                this->size++;
                j++;
            }
        }
    }

    int GetCapacity() override
    {
        return capacity;
    }

    int GetSize() override
    {
        return this->size;
    }

    T Get(int index) override
    {
        return d->Get(index);
    }

    T GetNull() override
    {
        return this->null;
    }

    bool Contains(T element) override
    {
        bool flag = false;
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (this->Get(i) == element)
            {
                flag = true;
            }
        }
        return flag;
    }

    SparseVector<T>* Sum (SparseVector<T>* sv1) override
    {
        if (sv1->GetSize() == this->GetSize())
        {
            vector<T>* v1 = new vector<T>();
            for (int i = 0; i < sv1->GetSize(); i++)
            {
                v1->push_back(sv1->Get(i));
            }

            vector<T>* v2 = new vector<T>();
            for (int i = 0; i < this->GetSize(); i++)
            {
                v2->push_back(this->Get(i));
            }

            vector<T>* vSum = new vector<T>();
            for (int  i = 0; i < sv1->GetSize(); i++)
            {
                vSum->push_back(v1->at(i) + v2->at(i));
            }

            SparseVector<T>* sumVector = (SparseVector<T>*)new SparseVectorDict<T>(vSum, null, cmp);
            return sumVector;
        }

        else
        {
            throw std::out_of_range("Invalid size of arrays");
        }
    }

    SparseVector<T>* Mult(int scalar) override
    {
        vector<T>* v1 = new vector<T>();
        for (int  i = 0; i < this->GetSize(); i++)
        {
            v1->push_back(this->Get(i));
        }

        vector<T>* vMult = new vector<T>();
        for (int i = 0; i < this->GetSize(); i++)
        {
            vMult->push_back(scalar * this->Get(i));
        }
        SparseVector<T>* multVector = (SparseVector<T>* )new SparseVectorDict<T>(vMult, null, cmp);
    }

    T ScalarProd (SparseVector<T>* sv1) override
    {
        if(sv1->GetSize() != this->GetSize())
        {
            throw std::out_of_range("Invalid sizes of vectors");
        }
        else
        {
            T mult = null;
            for (int i = 0; i < this->GetSize(); i++)
            {
                mult += ((this->Get(i)) * (sv1->Get(i)));
            }
            return mult;
        }
    }
};


#endif // SPARSEVECTORDICT_H_INCLUDED
