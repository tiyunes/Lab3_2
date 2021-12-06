#ifndef SPARSE_VECTOR_H_INCLUDED
#define SPARSE_VECTOR_H_INCLUDED
#include "SortedSequence.h"
#include "dictionary.h"
#include <vector>

template<class T>
class SparseVector
{
public:
    virtual int GetCapacity() = 0;
    virtual int GetSize() = 0;
    virtual T Get (int index) = 0;
    virtual T GetNull() = 0;
    virtual bool Contains (T element) = 0;
    virtual SparseVector<T>* Sum (SparseVector<T>* sv1) = 0;
    virtual SparseVector<T>* Mult (int scalar) = 0;
    virtual T ScalarProd (SparseVector<T>* sv1) = 0;
    virtual ~SparseVector<T>() = default;
};


#endif // SPARSE_VECTOR_H_INCLUDED
