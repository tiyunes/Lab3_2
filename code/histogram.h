#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include "dictionary.h"
#include "STUDENTS.H"
#include "SEQUENCE.H"

template<class TKey, class TElement>
class Histogram
{
private:
    IDictionary<int, int>* d;
    int (Student::*GetP)();
    int min;
    int max;
    double range;

friend class TPair<TKey, TElement>;
public:

    IDictionary<int, int>* GetDict()
    {
        return this->d;
    }

    Histogram (Sequence<Student>* s, int N,
                                      function<bool(TPair<TKey, TElement>, TPair<TKey, TElement>)> cmp, int (Student::*GetP)())
    {
        this->min = (s->Get(0).*GetP)();
        this->max = (s->Get(0).*GetP)();
        for (int i = 1; i < s->GetLength(); i++)
        {
            if ((s->Get(i).*GetP)() < min)
            {
                min = (s->Get(i).*GetP)();
            }
            if ((s->Get(i).*GetP)() > max)
            {
                max = (s->Get(i).*GetP)();
            }
        }
        this->range = (max * 1.0 - min * 1.0) / N;
        this->d = new IDictionary<int, int>();
        d->SetCmp(cmp);
        for (int i = 1; i <= N; i++)
        {
            TPair<int, int> p;
            p.SetKey(i);
            p.SetElement(0);
            d->Add(p);
        }
        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j < s->GetLength(); j++)
            {
                if (((s->Get(j).*GetP)() >= (min + (i - 1)* range)) && ((s->Get(j).*GetP)() <= (min + i * range))
                    && (s->Get(j).*GetP)() <= max)
                {
                    d->Increase(i);
                }
            }
        }
    }

    Histogram(IDictionary<int, int>* d)
    {
        this->d = new IDictionary<int, int>(d);
    }

    int GetSize()
    {
        return this->d->GetCount();
    }

    int GetSubAmount(int index)
    {
        if (this->d->ContainsKey(index))
        {
            return this->d->Get(index);
        }
        else
        {
            throw std::out_of_range("Invalid key");
        }
    }

    int GetMin()
    {
        return this->min;
    }

    int GetMax()
    {
        return this->max;
    }

    double GetRange()
    {
        return this->range;
    }
};



#endif // HISTOGRAM_H_INCLUDED
