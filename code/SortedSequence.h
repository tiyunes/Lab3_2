#ifndef SORTEDSEQUENCE_H_INCLUDED
#define SORTEDSEQUENCE_H_INCLUDED
#include "SEQUENCE.H"
#include <functional>

template<class T>
class ISortedSequence
{
private:
    Sequence<T>* s;
    int length;
    function<bool(T, T)> cmp;
    function<Sequence<T>*(Sequence<T>*, function<bool(T, T)>)> sorter;

public:
    ISortedSequence()
    {
        this->s = (Sequence<T>*) new ArraySequence<T>();
        length = 0;
    }

    ISortedSequence(function<bool(T, T)> cmp, function<Sequence<T>*(Sequence<T>*, function<bool(T, T)>)> sorter)
    {
        this->s = (Sequence<T>*) new ArraySequence<T>();
        length = 0;
        this->cmp = cmp;
        this->sorter = sorter;
    }

    ISortedSequence(Sequence<T>* s1, function<bool(T, T)> cmp, function<Sequence<T>*(Sequence<T>*, function<bool(T, T)>)> sorter)
    {
        this->s = new ArraySequence<T>(s1->GetLength());
        this->s = sorter(s1, cmp);
        length = s1->GetLength();
        this->cmp = cmp;
        this->sorter = sorter;
    }

    ISortedSequence(Sequence<T>* s1)
    {
        this->s = new ArraySequence<T>(s1->GetLength());
        this->s = sorter(s1, this->cmp);
        length = s1->GetLengt();
    }

    ISortedSequence(int n)
    {
        this->s = (Sequence<T>*) new ArraySequence<T>(n);
        length = n;
    }


    int GetLength()
    {
        return this->s->GetLength();
    }

    int IsEmpty()
    {
        if (this->s->GetLength() == 0) return 1;
        else return 0;
    }

    T Get(int index)
    {
        return this->s->Get(index);
    }

    T GetFirst()
    {
        return this->s->GetFirst();
    }

    T GetLast()
    {
        return this->s->GetLast();
    }

    int IndexOf (T element)
    {
        for (int i = 0; i < s->GetLength(); i++)
        {
            if (s->Get(i) == element) return i;
        }
        return -1;
    }

    ISortedSequence<T>* GetSubSequence(int startIndex, int endIndex)
    {
        Sequence<T>* s1 = (Sequence<T>*) new ArraySequence<T>(endIndex - startIndex);
        s1 = s->GetSubsequence(startIndex, endIndex);
        ISortedSequence<T>* s2 = new ISortedSequence<T>(s1);
        return s2;
    }

    int BinarySearch(T element)
    {
        int mid;
        int left = 0;
        int right = (s->GetLength() - 1);
        while(true)
        {
            mid = this->s->GetLength() / 2;
            if (left > right)
            {
                return -1;
            }

            if (element.GetElement() < this->s->Get(mid).GetElement())
            {
                return this->BinarySearchH(left, mid - 1, element);
//              right = mid - 1;
            }
            else if (this->s->Get(mid).GetElement() < element.GetElement())
            {
                return this->BinarySearchH(mid + 1, right, element);
//                left = mid + 1;
            }
            else if (this->s->Get(mid).GetElement() == element.GetElement())
            {
                return this->s->Get(mid).GetElement();
            }
        }
    }

    int BinarySearchH(int left, int right, T element)
    {
        int mid;
        while(true)
        {
            mid = (right + left) / 2;
            if (left > right)
            {
                return -1;
            }

            if (element.GetElement() < this->s->Get(mid).GetElement())
            {
                return this->BinarySearchH(left, mid - 1, element);
//              right = mid - 1;
            }
            else if (this->s->Get(mid).GetElement() < element.GetElement())
            {
                return this->BinarySearchH(mid + 1, right, element);
//                left = mid + 1;
            }
            else if (this->s->Get(mid).GetElement() == element.GetElement())
            {
                return this->s->Get(mid).GetElement();
            }
        }
    }

    void Add(T element)
    {
        this->s->Append(element);
        this->s = sorter(this->s, cmp);
        this->length++;
    }
};




#endif // SORTEDSEQUENCE_H_INCLUDED
