#ifndef SFS_SEQ_H_INCLUDED
#define SFS_SEQ_H_INCLUDED
#include "SFS.h"
#include "SortedSequence.h"
#include <string>

class SFS_Seq: public SFS
{
private:
    ISortedSequence<TPair<string, int>>* s;
    function<bool(TPair<string, int>, TPair<string, int>)> cmp;
    function<Sequence<TPair<string, int>>*(Sequence<TPair<string, int>>*, function<bool(TPair<string, int>, TPair<string, int>)>)> sorter;


public:
    SFS_Seq (Sequence<char>* s1, int min, int max,
            function<bool(TPair<string, int>, TPair<string, int>)> cmp,
            function<Sequence<TPair<string, int>>*(Sequence<TPair<string, int>>*, function<bool(TPair<string, int>, TPair<string, int>)>)> sorter)
    {
        IDictionary<string, int>* d = new IDictionary<string, int>();
        d->SetCmp(cmp);
        this->cmp = cmp;
        this->sorter = sorter;
        for (int i = 0; i < s1->GetLength(); i++)
        {
            for (int j = min - 1; j < max && (i + j) < s1->GetLength(); j++)
            {
                Sequence<char>* subSeq = new ArraySequence<char>(j);
                subSeq = s1->GetSubsequence(i, i + j);
                string subString("");
                for (int l = 0; l < subSeq->GetLength(); l++)
                {
                    subString.push_back(subSeq->Get(l));
                }

                if (!d->ContainsKey(subString))
                {
                    int c = 1;
                    d->Add(subString, c);
                }
                else
                {
                    d->Increase(subString);
                }
            }
        }
        Sequence<TPair<string, int>>* sAns1 = (Sequence<TPair<string, int>>*) new ArraySequence<TPair<string, int>>(d->GetCount());
        sAns1 = d->GetTree()->SaveToSequence();
        this->s = new ISortedSequence<TPair<string, int>>(sAns1, cmp, sorter);
    }

    int GetFrequency(string s1) override
    {
        TPair<string, int> p;
        p.SetKey(s1);
        if (this->s->IndexOf(p) == -1)
        {
            return 0;
        }
        else
        {
            int  i = this->s->IndexOf(p);
            return this->s->Get(i).GetElement();
        }
    }

    int GetSize() override
    {
        return this->s->GetLength();
    }

    ISortedSequence<TPair<string, int>>* GetSeq()
    {
        return this->s;
    }

    void print() override
    {
         for (int i = 0; i < this->GetSeq()->GetLength(); i++)
         {
            cout << "Subsequence: " << this->GetSeq()->Get(i).GetKey() << " " << "Frequency: " <<
            this->GetSeq()->Get(i).GetElement() << endl;
         }
         cout << endl;
    }
};



#endif // SFS_SEQ_H_INCLUDED
