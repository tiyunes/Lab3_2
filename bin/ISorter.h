#ifndef ISORTER_H_INCLUDED
#define ISORTER_H_INCLUDED
#include <functional>
#include <utility>
#include <vector>
#include <algorithm>
//#include "BubbleSort.h"
//#include "InsertionSort.h"
//#include "CountingSort.h"
#include "MergeSort.h"
//#include "QuickSort.h"
//#include "QuickSortF.h"
//#include "QuickSortM.h"
//#include "QuickSort3.h"


template<class T>
class ISorter
{
public:
    virtual Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) = 0;
};

//template<class T>
//class BubbleSorter: public ISorter<T>
//{
//public:
//    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
//    {
//        s = BubbleSort(s, cmp);
//        return s;
//    }
//};
//
//template<class T>
//class InsertionSorter: public ISorter<T>
//{
//public:
//    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
//    {
//        s = InsertionSort(s, cmp);
//        return s;
//    }
//};

template<class T>
class MergeSorter: public ISorter<T>
{
public:
    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
    {
        s = MergeSort(s, cmp);
        return s;
    }
};

//template<class T>
//class QuickSorter: public ISorter<T>
//{
//public:
//    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
//    {
//        s = QuickSort(s, cmp);
//        return s;
//    }
//};
//
//template<class T>
//class QuickSorterF: public ISorter<T>
//{
//public:
//    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
//    {
//        s = QuickSortF(s, cmp);
//        return s;
//    }
//};
//
//template<class T>
//class QuickSorterM: public ISorter<T>
//{
//public:
//    Sequence<T>* Sorter(Sequence<T>* s, function<bool(T, T)> cmp) override
//    {
//        s = QuickSortM(s, cmp);
//        return s;
//    }
//};


#endif // ISORTER_H_INCLUDED
