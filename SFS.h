#ifndef SFS_H_INCLUDED
#define SFS_H_INCLUDED
#include "SEQUENCE.H"
#include "SortedSequence.h"
#include "dictionary.h"
#include "MergeSort.h"
#include <string>
#include <utility>

using namespace std;

class SFS
{
public:
    virtual int GetFrequency(string s1) = 0;
    virtual int GetSize() = 0;
    virtual void print() = 0;
};


#endif // SFS_H_INCLUDED
