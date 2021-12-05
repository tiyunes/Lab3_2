#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED
#include "SEQUENCE.H"
#include "ArraySequence.h"
#include <functional>

template<class T>
void MergeSortH(Sequence<T>* s, function<bool(T, T)> cmp)
{
    if (s->GetLength() <= 1) return;
    int middle = s->GetLength() / 2;
    Sequence<T>* leftSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength() / 2);
    for (int i = 0; i < (s->GetLength() / 2); i++)
    {
        leftSequence->Set(i, s->Get(i));
    }
    Sequence<T>* rightSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength() - middle);
    for (int i = 0; i < (s->GetLength() - middle); i++)
    {
        rightSequence->Set(i, s->Get(i + (s->GetLength() / 2)));
    }

    MergeSortH(leftSequence, cmp);
    MergeSortH(rightSequence, cmp);

    //Sequence<T>* bufferSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength());
    int left_i = 0;
    int right_i = 0;
    int buffer_i = 0;
    while (left_i < middle && right_i < (s->GetLength() - middle))
    {
        if (cmp(leftSequence->Get(left_i), rightSequence->Get(right_i)))
        {
            s->Set(buffer_i, leftSequence->Get(left_i));
            left_i++;
            buffer_i++;
        }
        else
        {
            s->Set(buffer_i, rightSequence->Get(right_i));
            right_i++;
            buffer_i++;
        }
    }
    while (left_i < middle)
    {
        s->Set(buffer_i, leftSequence->Get(left_i));
        left_i++;
        buffer_i++;
    }
    while (right_i < (s->GetLength() - middle))
    {
        s->Set(buffer_i, rightSequence->Get(right_i));
        right_i++;
        buffer_i++;
    }
    for (int i = 0; i < s->GetLength(); i++)
    {
        s->Set(i, s->Get(i));
    }
    //delete[] bufferSequence;
}

template<class T>
Sequence<T>* MergeSort(Sequence<T>* s, function<bool(T, T)> cmp)
{
    //Sequence<T>* sortedSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength());
    int middle = s->GetLength() / 2;
    Sequence<T>* leftSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength() / 2);
    for (int i = 0; i < (s->GetLength() / 2); i++)
    {
        leftSequence->Set(i, s->Get(i));
    }
    Sequence<T>* rightSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength() - middle);
    for (int i = 0; i < (s->GetLength() - middle); i++)
    {
        rightSequence->Set(i, s->Get(i + (s->GetLength() / 2)));
    }

    MergeSortH(leftSequence, cmp);
    MergeSortH(rightSequence, cmp);

    //Sequence<T>* bufferSequence = (Sequence<T>*)new ArraySequence<T>(s->GetLength());
    int left_i = 0;
    int right_i = 0;
    int buffer_i = 0;
    while (left_i < middle && right_i < (s->GetLength() - middle))
    {
        if (cmp(leftSequence->Get(left_i), rightSequence->Get(right_i)))
        {
            s->Set(buffer_i, leftSequence->Get(left_i));
            left_i++;
            buffer_i++;
        }
        else
        {
            s->Set(buffer_i, rightSequence->Get(right_i));
            right_i++;
            buffer_i++;
        }
    }
    while (left_i < middle)
    {
        s->Set(buffer_i, leftSequence->Get(left_i));
        left_i++;
        buffer_i++;
    }
    while (right_i < (s->GetLength() - middle))
    {
        s->Set(buffer_i, rightSequence->Get(right_i));
        right_i++;
        buffer_i++;
    }

    delete[] leftSequence;
    delete[] rightSequence;
    return s;
}


#endif // MERGESORT_H_INCLUDED
