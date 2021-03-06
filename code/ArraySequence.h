#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H
#include "SEQUENCE.H"
#include "DynamicArray.h"

template<class T>
class ArraySequence: public Sequence<T>
{
public:
    friend class DynamicArray<T>;

    ArraySequence();
    ArraySequence(int Size);
    ArraySequence(T* items, int c);
    ArraySequence(const DynamicArray<T>& dynamicArray);
    ArraySequence(const ArraySequence<T>& arraySequence);
    ArraySequence(Sequence<T>* s);

    T GetFirst() override;
    T GetLast() override;
    T Get(int index) override;
    T& GetP(int index) override;
    void Set(int index, T item) override;
    int GetLength() override;
    void Pop() override;

    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    void Reverse() override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* Concat(Sequence<T> *l) override;
    ~ArraySequence<T>();
private:
    DynamicArray<T>* items;
};

template<class T>
ArraySequence<T>::ArraySequence()
{
    this->items = new DynamicArray<T>();
}

template<class T>
ArraySequence<T>::ArraySequence(int Size)
{
    this->items = new DynamicArray<T>(Size);
}

template<class T>
ArraySequence<T>::ArraySequence(T* items, int c)
{
    this->items = new DynamicArray<T>(items, c);
}

template<class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& dynamicArray)
{
    this->items = new DynamicArray<T>(dynamicArray);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& arraySequence)
{
    this->items = new DynamicArray<T>(arraySequence.items);
}

template<class T>
ArraySequence<T>::ArraySequence(Sequence<T>* s)
{
    this->items = new DynamicArray<T>(s->GetLength());
    for (int i = 0; i < s->GetLength(); i++)
    {
        items[i] = s->Get(i);
    }
}

template<class T>
T ArraySequence<T>::GetFirst()
{
    return this->items->Get(0);
}

template<class T>
T ArraySequence<T>::GetLast()
{
    return this->items->Get(this->items->Size - 1);
}

template<class T>
T ArraySequence<T>::Get(int index)
{
    return this->items->Get(index);
}

template<class T>
T& ArraySequence<T>::GetP(int index)
{
    return (*(items))[index];
}

template<class T>
void ArraySequence<T>::Set(int index, T item)
{
    this->items->Set(index, item);
}

template<class T>
int ArraySequence<T>::GetLength()
{
    return this->items->GetSize();
}

template<class T>
void ArraySequence<T>::Append(T item)
{
    this->items->Resize(this->items->GetSize() + 1);
    this->items->Set(this->items->GetSize() - 1, item);
}

template<class T>
void ArraySequence<T>::Prepend(T item)
{
    if (this->GetLength() != 0)
    {
        DynamicArray<T>* buff = new DynamicArray<T>(this->GetLength());
        for (int j = 0; j < this->GetLength(); j++)
        {
            buff->values[j] = this->Get(j);
        }
        this->items->Size++;
        this->items = new DynamicArray<T>(this->items->Size);
        this->items->Set(0, item);
        for (int i = 1; i < this->GetLength(); i++)
        {
            this->items->Set(i, buff->Get(i - 1));
        }
    }
    else
    {
        this->items->Set(0, item);
        this->items->Size++;
    }
}

template<class T>
void ArraySequence<T>::InsertAt(T item, int index)
{
    this->items->Resize(this->items->Size + 1);
    for (int i = 0; i < index; i++)
    {
        this->items->Set(i, this->Get(i));
    }
    this->items->Set(index, item);
    for (int j = index + 1; j < this->GetLength(); j++)
    {
        this->items->Set(j, this->Get(j - 1));
    }

}

template<class T>
void ArraySequence<T>::Pop()
{
    return this->items->Pop();
}

template<class T>
void ArraySequence<T>::Reverse()
{
    return this->items->Reverse();
}

template<class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex)
{
    ArraySequence<T>* subArray = new ArraySequence<T>(endIndex - startIndex + 1);
    for (int i = 0; i < endIndex - startIndex + 1; i++)
    {
        subArray->items->Set(i, this->items->Get(i + startIndex));
    }
    return subArray;
}

template<class T>
Sequence<T>* ArraySequence<T>::Concat(Sequence <T> *l)
{
    Sequence<T>* concatSequence = (Sequence<T>*)new ArraySequence<T>(l->GetLength() + this->GetLength());
    for (int i = 0; i < this->GetLength(); i++)
    {
        concatSequence->Append(this->Get(i));
    }
    for (int i = 0; i < l->GetLength(); i++)
    {
        concatSequence->Append(l->Get(i));
    }

    return concatSequence;
}

template<class T>
ArraySequence<T>::~ArraySequence()
{
    if (this->items != nullptr)
    {

        delete this->items;
    }
}


#endif // ARRAYSEQUENCE_H


