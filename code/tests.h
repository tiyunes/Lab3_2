#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
#include <cassert>
#include "SFS.h"
#include "SFS_Seq.h"
#include "SFS_Dict.h"

bool compKey(TPair<int, int> a, TPair<int, int> b)
{
    if (a.GetKey() < b.GetKey())
    {
        return 1;
    }
    else return 0;
}

bool compElement(TPair<int, int> a, TPair<int, int> b)
{
    if (a.GetElement() < b.GetElement())
    {
        return 1;
    }
    else return 0;
}

Sequence<TPair<string, int>>* MergeSort1(Sequence<TPair<string, int>>* s1, function<bool(TPair<string, int>, TPair<string, int>)> f)
{
    ISorter<TPair<string, int>>* sorter1 = new MergeSorter<TPair<string, int>>();
    return sorter1->Sorter(s1, f);
}

bool comp3(TPair<string, int> p1, TPair<string, int> p2)
{
    int minl = min(p1.GetKey().size(), p2.GetKey().size());
    if (p1.GetKey().size() == p2.GetKey().size())
    {
        for (int  i = 0; i < p1.GetKey().size(); i++)
        {
            if(p1.GetKey()[i] < p2.GetKey()[i])
            {
                return 1;
            }
            else if (p1.GetKey()[i] > p2.GetKey()[i]) return 0;
        }
        return 0;
    }
    else
    {
        for (int  i = 0; i < minl; i++)
        {
            if(p1.GetKey()[i] < p2.GetKey()[i])
            {
                return 1;
            }
            else if (p1.GetKey()[i] > p2.GetKey()[i]) return 0;
        }
        if (p1.GetKey().size() < p2.GetKey().size())
        {
            return 1;
        }
        else return 0;
    }
}

Sequence<TPair<int, int>>* MergeSort2(Sequence<TPair<int, int>>* s1, function<bool(TPair<int, int>, TPair<int, int>)> f)
{
    ISorter<TPair<int, int>>* sorter1 = new MergeSorter<TPair<int, int>>();
    return sorter1->Sorter(s1, f);
}

bool comp4(TPair<int, TPair<int, int>> a, TPair<int, TPair<int, int>> b)
{
    if (a.GetKey() < b.GetKey())
    {
        return 1;
    }
    else return 0;
}

function<bool(TPair<int, int>, TPair<int, int>)>cmpKey = compKey;
function<bool(TPair<int, int>, TPair<int, int>)>cmpElement = compElement;
function<Sequence<TPair<string, int>>*(Sequence<TPair<string, int>>*, function<bool(TPair<string, int>, TPair<string, int>)>)> sorter1 = MergeSort1;
function<bool(TPair<string, int>, TPair<string, int>)>compSFS = comp3;
function<bool(TPair<int, TPair<int, int>>, TPair<int, TPair<int, int>>)> compMatrix = comp4;
function<Sequence<TPair<int, int>>*(Sequence<TPair<int, int>>*, function<bool(TPair<int, int>, TPair<int, int>)>)> sorter2 = MergeSort2;

void TestSFS()
{
    Sequence<char>* sChar = new ArraySequence<char>();
    char c1 = 'g';
    char c2 = 'c';
    char c3 = 'd';
    char c4 = 'g';
    char c5 = 'c';
    char c6 = 'h';
    sChar->Append(c1);
    sChar->Append(c2);
    sChar->Append(c3);
    sChar->Append(c4);
    sChar->Append(c5);
    sChar->Append(c6);
//    ISortedSequence<TPair<string, int>>* ISeq = new ISortedSequence<TPair<string, int>>(11);
    SFS* class1 = (SFS*) new SFS_Seq(sChar, 2, 3, compSFS, sorter1);
//    ISeq = class1->SearchFrequentSubseq(sChar, 2, 3, compSFS, sorter1);
    string s1 = "gc";
    string s2 = "cd";
    string s3 = "dg";
    string s4 = "bh"; // incorrect
    string s5 = "gcd";
    string s6 = "cdg";
    string s7 = "dgd"; // incorrect
    string s8 = "gch";
    assert(class1->GetFrequency(s1) == 2);
    assert(class1->GetFrequency(s2) == 1);
    assert(class1->GetFrequency(s3) == 1);
    assert(class1->GetFrequency(s4) == 0);
    assert(class1->GetFrequency(s5) == 1);
    assert(class1->GetFrequency(s6) == 1);
    assert(class1->GetFrequency(s7) == 0);
    assert(class1->GetFrequency(s8) == 1);

    Sequence<char>* sChar2 = new ArraySequence<char>();
    char c8 = 'a';
    char c9 = 'h';
    char c10 = 'l';
    char c11 = 'w';
    char c12 = 'r';
    char c13 = 'p';
    sChar2->Append(c8);
    sChar2->Append(c9);
    sChar2->Append(c10);
    sChar2->Append(c11);
    sChar2->Append(c12);
    sChar2->Append(c13);

//    ISortedSequence<TPair<string, int>>* ISeq2 = new ISortedSequence<TPair<string, int>>(11);
    SFS* class2 = (SFS*) new SFS_Dict(sChar2, 1, 2, compSFS);
//   ISeq = class2->SearchFrequentSubseq(sChar2, 1, 2, compSFS, sorter1);
    string s9 = "a";
    string s10 = "h";
    string s11 = "w";
    string s12 = "r";
    string s13 = "f"; //incorrect
    string s14 = "lw";
    string s15 = "lp"; //incorrect
    assert(class2->GetSize() == 11);
    assert(class2->GetFrequency(s9) == 1);
    assert(class2->GetFrequency(s10) == 1);
    assert(class2->GetFrequency(s11) == 1);
    assert(class2->GetFrequency(s12) == 1);
    assert(class2->GetFrequency(s13) == 0);
    assert(class2->GetFrequency(s14) == 1);
    assert(class2->GetFrequency(s15) == 0);

    Sequence<char>* sChar3 = new ArraySequence<char>();
    char c14 = 'a';
    char c15 = 'a';
    char c16 = 'a';
    sChar3->Append(c14);
    sChar3->Append(c15);
    sChar3->Append(c16);
//    ISortedSequence<TPair<string, int>>* ISeq3 = new ISortedSequence<TPair<string, int>>(2);
    SFS* class3 = (SFS*) new SFS_Dict(sChar3, 1, 2, compSFS);
//    ISeq = class3->SearchFrequentSubseq(sChar3, 1, 2, compSFS, sorter1);
    string s16 = "a";
    string s17 = "aa";
    string s18 = "wa"; // incorrect
    string s19 = "aaa"; // incorrect

    assert(class3->GetSize() == 2);
    assert(class3->GetFrequency(s16) == 3);
    assert(class3->GetFrequency(s17) == 2);
    assert(class3->GetFrequency(s18) == 0);
    assert(class3->GetFrequency(s19) == 0);

    Sequence<char>* sChar4 = new ArraySequence<char>();
    char c20 = 'T';
    sChar4->Append(c20);
//    ISortedSequence<TPair<string, int>>* ISeq4 = new ISortedSequence<TPair<string, int>>();
    SFS* class4 = (SFS*) new SFS_Seq(sChar4, 1, 2, compSFS, sorter1);
//    ISeq4 = class4->SearchFrequentSubseq(sChar4, 1, 2, compSFS, sorter1);
    string s20 = "T";
    string s21 = "a"; // incorrect
    string s22 = "b"; // incorrect

    assert(class4->GetSize() == 1);
    assert(class4->GetFrequency(s20) == 1);
    assert(class4->GetFrequency(s21) == 0);
    assert(class4->GetFrequency(s22) == 0);

    Sequence<char>* sChar5 = new ArraySequence<char>();
    char c21 = 't';
    char c22 = 'e';
    char c23 = 's';
    char c24 = 't';
    char c25 = 'e';
    char c26 = 'r';
    sChar5->Append(c21);
    sChar5->Append(c22);
    sChar5->Append(c23);
    sChar5->Append(c24);
    sChar5->Append(c25);
    sChar5->Append(c26);
//    ISortedSequence<TPair<string, int>>* ISeq5 = new ISortedSequence<TPair<string, int>>(4);
    SFS* class5 = (SFS*) new SFS_Dict(sChar5, 1, 1, compSFS);
//    ISeq = class5->SearchFrequentSubseq(sChar5, 1, 1, compSFS, sorter1);
    string s23 = "t";
    string s24 = "a"; //incorrect
    string s25 = "s";
    string s26 = "t";
    string s27 = "g"; //incorrect
    string s28 = "r";
    string s29 = "hd"; //incorrect
    assert(class5->GetSize() == 4);
    assert(class5->GetFrequency(s23) == 2);
    assert(class5->GetFrequency(s24) == 0);
    assert(class5->GetFrequency(s25) == 1);
    assert(class5->GetFrequency(s26) == 2);
    assert(class5->GetFrequency(s27) == 0);
    assert(class5->GetFrequency(s28) == 1);
    assert(class5->GetFrequency(s29) == 0);
}

void TestSparseVector()
{
    vector<int>* v1 = new vector<int>;
    v1->push_back(4);
    v1->push_back(2);
    v1->push_back(0);
    v1->push_back(10);
    v1->push_back(7);
    v1->push_back(0);
    v1->push_back(1);
    SparseVector<int>* sparseVector1 = (SparseVector<int>*) new SparseVectorDict<int>(v1, 0, cmpKey);
    assert(sparseVector1->GetSize() == 5); // number of non null elements
    assert(sparseVector1->Get(0) == 4);
    assert(sparseVector1->Get(1) == 2);
    assert(sparseVector1->Get(2) == 10);
    assert(sparseVector1->Get(3) == 7);
    assert(sparseVector1->Get(4) == 1);
    assert(sparseVector1->Contains(5) == false);
    assert(sparseVector1->Contains(4) == true);

    vector<int>* v2 = new vector<int>;
    v2->push_back(26);
    v2->push_back(17);
    v2->push_back(0);
    v2->push_back(12);
    v2->push_back(0);
    v2->push_back(0);
    v2->push_back(55);
    SparseVector<int>* sparseVector2 = (SparseVector<int>*) new SparseVectorDict<int>(v2, 0, cmpKey);
    assert(sparseVector2->GetSize() == 4); // number of non null elements
    assert(sparseVector2->Get(0) == 26);
    assert(sparseVector2->Get(1) == 17);
    assert(sparseVector2->Get(2) == 12);
    assert(sparseVector2->Get(3) == 55);
    assert(sparseVector2->Contains(5) == false);
    assert(sparseVector2->Contains(4) == false);
    assert(sparseVector2->Contains(55) == true);

    SparseVector<int>* sparseVector3 = (SparseVector<int>*) new SparseVectorSeq<int>(v1, 0, cmpKey, sorter2);
    assert(sparseVector3->GetSize() == 5); // number of non null elements
    assert(sparseVector3->Get(0) == 4);
    assert(sparseVector3->Get(1) == 2);
    assert(sparseVector3->Get(2) == 10);
    assert(sparseVector3->Get(3) == 7);
    assert(sparseVector3->Get(4) == 1);
    assert(sparseVector3->Contains(5) == false);
    assert(sparseVector3->Contains(4) == true);
}

void TestSparseMatrix()
{
    vector<TPair<int, TPair<int, int>>>* vPair = new vector<TPair<int, TPair<int, int>>>;
    pair<int, int> p1;
    p1.first = 11;
    p1.second = 12;
    TPair<int, int> pair1(p1);
    TPair<int, int> l1(p1);

    pair<int, int> p2;
    p2.first = 4;
    p2.second = 1;
    TPair<int, int> pair2(p2);
    TPair<int, int> l2(p2);

    pair<int, int> p3;
    p3.first = 1;
    p3.second = 10;
    TPair<int, int> pair3(p3);
    TPair<int, int> l3(p3);

    pair<int, int> p9;
    p9.first = 78;
    p9.second = 12;
    TPair<int, int> pair9(p9);
    TPair<int, int> l9(p9);

    pair<int, int> p10;
    p10.first = 90;
    p10.second = 11;
    TPair<int, int> pair10(p10);
    TPair<int, int> l10(p10);

    pair<int, TPair<int, int>> p4;
    p4.second = l1;
    p4.first = 2;
    TPair<int, TPair<int, int>> pair4(p4);

    pair<int, TPair<int, int>> p5;
    p5.second = l2;
    p5.first = 3;
    TPair<int, TPair<int, int>> pair5(p5);

    pair<int, TPair<int, int>> p6;
    p6.second = l3;
    p6.first = 7;
    TPair<int, TPair<int, int>> pair6(p6);

    pair<int, TPair<int, int>> p7;
    p7.second = l9;
    p7.first = 6;
    TPair<int, TPair<int, int>> pair7(p7);

    pair<int, TPair<int, int>> p8;
    p8.second = l10;
    p8.first = 36;
    TPair<int, TPair<int, int>> pair8(p8);

    vPair->push_back(pair4);
    vPair->push_back(pair5);
    vPair->push_back(pair6);

    SparseMatrix<int>* sparseMatrix = new SparseMatrix<int>(vPair, 3, 1, 0, compMatrix);
    assert(sparseMatrix->GetColumns() == 1);
    assert(sparseMatrix->GetRows() == 3);
    assert(sparseMatrix->Contains(pair4) == true);
    assert(sparseMatrix->Contains(pair5) == true);
    assert(sparseMatrix->Contains(pair6) == true);
    assert(sparseMatrix->Contains(pair7) == false);
    assert(sparseMatrix->Contains(pair8) == false);

    vector<TPair<int, TPair<int, int>>>* vPair2 = new vector<TPair<int, TPair<int, int>>>;
    vPair2->push_back(pair7);
    vPair2->push_back(pair8);
    SparseMatrix<int>* sparseMatrix2 = new SparseMatrix<int>(vPair2, 1, 2, 0, compMatrix);
    assert(sparseMatrix2->GetColumns() == 2);
    assert(sparseMatrix2->GetRows() == 1);
    assert(sparseMatrix2->Contains(pair7) == true);
    assert(sparseMatrix2->Contains(pair8) == true);
    assert(sparseMatrix2->Contains(pair4) == false);
    assert(sparseMatrix2->Contains(pair5) == false);
    assert(sparseMatrix2->Contains(pair6) == false);
}

void TestHistogram()
{
    Sequence<Student>* sStudent = new ArraySequence<Student>();

    StudentID* id1 = new StudentID(1, 2);
    string* firstName1 = new string("Ivan");
    string* lastName1 = new string("Ivanov");
    Student student1(id1, firstName1, lastName1);

    StudentID* id2 = new StudentID(1, 10);
    string* firstName2 = new string("Ivan");
    string* lastName2 = new string("Ivanov");
    Student student2(id2, firstName2, lastName2);

    StudentID* id3 = new StudentID(5, 6);
    string* firstName3 = new string("Ivan");
    string* lastName3 = new string("Ivanov");
    Student student3(id3, firstName3, lastName3);

    sStudent->Append(student1);
    sStudent->Append(student2);
    sStudent->Append(student3);

 //   IDictionary<int, int>* d1 = new IDictionary<int, int>();
    int (Student::*GetP)() = Student::GetNumber;
    Histogram<int, int>* h1 = new Histogram<int, int>(sStudent, 3, cmpKey, GetP);
    assert(h1->GetSize() == 3);
    assert(h1->GetSubAmount(1) == 2);
    assert(h1->GetSubAmount(2) == 0);
    assert(h1->GetSubAmount(3) == 1);

    Sequence<Student>* sStudent2 = new ArraySequence<Student>();

    StudentID* id4 = new StudentID(17, 4);
    string* firstName4 = new string("Peter");
    string* lastName4 = new string("Ivanov");
    int age4 = 23;
    Student student4(id4, age4, firstName4, lastName4);

    StudentID* id5 = new StudentID(15, 11);
    string* firstName5 = new string("Boris");
    string* lastName5 = new string("Ivanov");
    int age5 = 41;
    Student student5(id5, age5, firstName5, lastName5);

    StudentID* id6 = new StudentID(5, 6);
    string* firstName6 = new string("Ed");
    string* lastName6 = new string("Ivanov");
    int age6 = 21;
    Student student6(id6, age6, firstName6, lastName6);

    StudentID* id7 = new StudentID(5, 7);
    string* firstName7 = new string("Ed");
    string* lastName7 = new string("Ivanov");
    int age7 = 28;
    Student student7(id7, age7, firstName7, lastName7);

    StudentID* id8 = new StudentID(5, 8);
    string* firstName8 = new string("Ed");
    string* lastName8 = new string("Ivanov");
    int age8 = 35;
    Student student8(id8, age8, firstName8, lastName8);

    sStudent2->Append(student4);
    sStudent2->Append(student5);
    sStudent2->Append(student6);
    sStudent2->Append(student7);
    sStudent2->Append(student8);
    int (Student::*GetP2)() = Student::GetAge;

    Histogram<int, int>* h2 = new Histogram<int, int>(sStudent2, 4, cmpKey, GetP2);
    assert(h2->GetSize() == 4);
    assert(h2->GetSubAmount(1) == 2);
    assert(h2->GetSubAmount(2) == 1);
    assert(h2->GetSubAmount(3) == 1);
    assert(h2->GetSubAmount(4) == 1);
}

#endif // TESTS_H_INCLUDED
