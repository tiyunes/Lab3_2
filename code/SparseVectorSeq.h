#ifndef SPARSEVECTORSEQ_H_INCLUDED
#define SPARSEVECTORSEQ_H_INCLUDED
#include "sparse_vector.h"
#include "SortedSequence.h"

template<class T>
class SparseVectorSeq: public SparseVector <T>
{
private:
    ISortedSequence<TPair<int, T>>* s;
    int capacity;
    int size = 0;
    T null;
    function<bool(TPair<int, T>, TPair<int, T>)> cmp;
    function<Sequence<TPair<int, T>>*(Sequence<TPair<int, T>>*, function<bool(TPair<int, T>, TPair<int, T>)>)> sorter;

public:
    SparseVectorSeq(function<bool(TPair<int, T>, TPair<int, T>)> cmp)
    {
        this->s = new ISortedSequence<TPair<int, T>>(cmp, sorter);
        this->cmp = cmp;
    }

    SparseVectorSeq(vector<T>* v, T null, function<bool(TPair<int, T>, TPair<int, T>)> cmp, function<Sequence<TPair<int, T>>*(Sequence<TPair<int, T>>*, function<bool(TPair<int, T>, TPair<int, T>)>)> sorter)
    {
        this->s = new ISortedSequence<TPair<int, T>>(cmp, sorter);
        this->null = null;
        this->cmp = cmp;
        this->capacity = v->size();
        Sequence<TPair<int, T>>* seq = new ArraySequence<TPair<int, T>>();
        int j = 0;
        for (int i = 0; i < v->size(); i++)
        {
            if (v->at(i) != null)
            {
                TPair<int, T> p;
                p.SetKey(j);
                p.SetElement(v->at(i));
                seq->Append(p);
                this->size++;
                j++;
            }
        }
        this->s = new ISortedSequence<TPair<int, T>>(seq, cmp, sorter);
        this->sorter = sorter;
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
        return s->Get(index).GetElement();
    }

    T GetNull() override
    {
        return this->null;
    }

    bool Contains(T element) override
    {
        TPair<int, T> p;
        p.SetElement(element);
        if (this->s->BinarySearch(p) == (-1))
        {
            return false;
        }
        else
        {
            return true;
        }
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

            SparseVector<T>* sumVector = (SparseVector<T>*) new SparseVectorSeq<T>(vSum, null, cmp, sorter);
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

        SparseVector<T>* multVector = (SparseVector<T>*) new SparseVectorSeq<T>(vMult, null, cmp, sorter);
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
#endif // SPARSEVECTORSEQ_H_INCLUDED
