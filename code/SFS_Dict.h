#ifndef SFSDICT_H_INCLUDED
#define SFSDICT_H_INCLUDED
#include <iostream>
#include "SFS.h"
#include "dictionary.h"

class SFS_Dict: public SFS
{
private:
    IDictionary<string, int>* d;
    function<bool(TPair<string, int>, TPair<string, int>)> cmp;

public:
    SFS_Dict(Sequence<char>* s1, int min, int max,
            function<bool(TPair<string, int>, TPair<string, int>)> cmp)
    {
        this->d = new IDictionary<string, int>();
        this->cmp = cmp;
        d->SetCmp(cmp);
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
                    this->d->Add(subString, c);
                }
                else if (d->ContainsKey(subString))
                {
                    d->Increase(subString);
                }
            }
        }
    }

    int GetFrequency(string s1) override
    {
        if (this->d->ContainsKey(s1) == 0)
        {
            return 0;
        }
        else
        {
            return this->d->Get(s1);
        }
    }

    int GetSize() override
    {
        return this->d->GetCount();
    }

    void print() override
    {
        Sequence<TPair<string, int>>* s = (Sequence<TPair<string, int>>*) new ArraySequence<TPair<string, int>>(this->GetSize());
        s = this->d->GetTree()->SaveToSequence();
        for (int i = 0; i < this->GetSize(); i++)
        {
            cout << "Subsequence: " << s->Get(i).GetKey() << " " << "Frequency: " <<
            s->Get(i).GetElement() << endl;
        }
        cout << endl;
    }
};

#endif // SFSDICT_H_INCLUDED
