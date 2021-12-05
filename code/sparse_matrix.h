#ifndef SPARSE_MATRIX_H_INCLUDED
#define SPARSE_MATRIX_H_INCLUDED
#include "BTree.h"
#include "BTree_node.h"
#include "dictionary.h"


template<class T>
class SparseMatrix
{
private:
    BTree<TPair<T, TPair<T, T>>>* btree;
    int rows = 0;
    int columns = 0;
    T null;
    function<bool(TPair<T, TPair<T, T>>, TPair<T, TPair<T, T>>)> cmp;

public:
    SparseMatrix(vector<TPair<T, TPair<T, T>>>* v, int rows, int columns, T null, function<bool(TPair<T, TPair<T, T>>, TPair<T, TPair<T, T>>)> cmp)
    {
        this->rows = rows;
        this->columns = columns;
        this->btree = new BTree<TPair<T, TPair<T, T>>>(4);
        this->null = null;
        this->cmp = cmp;
        for (int i = 0; i < v->size(); i++)
        {
            if (v->at(i).GetKey() != null)
            {
                btree->Insert(v->at(i), cmp);
            }
        }
    }

    int GetRows()
    {
        return this->rows;
    }

    int GetColumns()
    {
        return this->columns;
    }

    int GetSize()
    {
        return this->btree->GetSize();
    }

    BTree<TPair<T, TPair<T, T>>>* GetTree()
    {
        return this->btree;
    }

    T GetNull()
    {
        return this->null;
    }

    void SetCmp(function<bool(TPair<T, TPair<T, T>>, TPair<T, TPair<T, T>>)> cmp)
    {
        this->cmp = cmp;
    }

    BTreeNode<TPair<T, TPair<T, T>>>* FindKey (T key)
    {
        pair<T, T> p1;
        pair<T, pair<T, T>> p2;
        p2.first = key;
        TPair<T, TPair<T, T>> pair1(p2);
        return this->btree->Search(pair1, this->cmp);
    }

    BTreeNode<TPair<T, TPair<T, T>>>* FindElement(TPair<int, int> p)
    {
        pair<T, pair<T, T>> p1;
        p1.second = p;
        TPair<T, TPair<T, T>> pair1(p1);
        return this->btree->Search(pair1, this->cmp);
    }

    bool Contains(TPair<T, TPair<T, T>> element)
    {
        vector<TPair<T, TPair<T, T>>>* v = new vector<TPair<T, TPair<T, T>>>;
        this->btree->ToVector(v);
        bool contains = false;
        for (int i = 0; i < v->size(); i++)
        {
            if (v->at(i).GetElement().GetKey() == element.GetElement().GetKey()
                && v->at(i).GetElement().GetElement() == element.GetElement().GetElement())
            {
                contains = true;
            }
        }
        return contains;
    }

    SparseMatrix<T>* Sum(SparseMatrix<T>* sm1)
    {
        if (sm1->GetRows() == this->rows && sm1->GetColumns() == this->columns)
        {
            vector<TPair<T, TPair<T, T>>>* v1 = new vector<TPair<T, TPair<T, T>>>();
            vector<TPair<T, TPair<T, T>>>* v2 = new vector<TPair<T, TPair<T, T>>>();
            sm1->GetTree()->ToVector(v1);
            this->GetTree()->ToVector(v2);

            vector<TPair<T, TPair<T, T>>>* vSum = new vector<TPair<T, TPair<T, T>>>();
            for (int  i = 0; i < sm1->GetRows()* sm1->GetColumns(); i++)
            {
                vSum->push_back(v1->at(i) + v2->at(i));
            }

            SparseMatrix<T>* matrixSum = new SparseMatrix<T>(vSum, this->rows, this->columns, this->null, this->cmp);
            return matrixSum;
        }
        else
        {
            throw std::out_of_range("Invalid dimensions of matrix");
        }
    }

    SparseMatrix<T>* Mult(int scalar)
    {
        vector<TPair<T, TPair<T, T>>>* v1 = new vector<TPair<T, TPair<T, T>>>();
        this->GetTree()->ToVector(v1);
        vector<TPair<T, TPair<T, T>>>* vMult = new vector<TPair<T, TPair<T, T>>>();

        for (int  i = 0; i < this->GetRows()* this->GetColumns(); i++)
        {
            vMult->push_back(v1->at(i) * scalar);
        }

        SparseMatrix<T>* matrixMult = new SparseMatrix<T>(vMult, this->rows, this->columns, this->null, this->cmp);
    }

};


#endif // SPARSE_MATRIX_H_INCLUDED
