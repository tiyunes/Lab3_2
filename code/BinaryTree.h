#ifndef BINARYTREE_BINARYTREE
#define BINARYTREE_BINARYTREE
#include "SEQUENCE.H"
#include "LinkedListSequence.h"
#include "ArraySequence.h"
#include "BinaryTreeNode.h"
#include "STUDENTS.H"
#include "TEACHER.H"
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

template<class T>
class BinaryTree: public BinaryTreeNode<T>
{
public:
    BinaryTree()
    {
        this->root = nullptr;
        size = 0;
    }

    BinaryTree(Sequence<T>* s, function<bool(T, T)> cmp)
    {
        this->root = nullptr;
        for(int  i = 0; i < s->GetLength(); i++)
        {
            this->Add(s->Get(i), cmp);
        }
    }

    BinaryTree(const BinaryTree<T>& tree)
    {
        this->root = new BinaryTreeNode<T>(tree.GetRoot());
        this->size = tree.size();
    }

    BinaryTree(const BinaryTree<T>* tree)
    {
        this->root = new BinaryTreeNode<T>(tree->GetRoot());
        this->size = tree->size();
    }

    BinaryTree(BinaryTreeNode<T>* n)
    {
        this->root = new BinaryTreeNode<T>(n);
        size = 1;
    }

    BinaryTreeNode<T>* Find(T item, function<bool(T, T)> cmp)
    {
        if (this->root == nullptr)
        {
            return nullptr;
        }
        else if (this->root->Get() == item)
        {
            return this->root;
        }
        else if (cmp(this->root->Get(), item))
        {
            if (this->root->GetRight() != nullptr)
            {
                return this->root->GetRight()->Find(item, cmp);
            }
            else
            {
                return nullptr;
            }
        }
        else if (cmp(item, this->root->Get()) && (item != this->root->Get()))
        {
            if (this->root->GetLeft() != nullptr)
            {
                return this->root->GetLeft()->Find(item, cmp);
            }
            else
            {
                return nullptr;
            }
        }
    }

    template<class T2>
    void Traverse(T2 f, function<void(BinaryTreeNode<T>*, T2)> action)
    {
        if (this->root == nullptr)
        {
            return;
        }
        TraverseNode(f, this->root->GetLeft(), action);
        action(this->root, f);
        TraverseNode(f, this->root->GetRight(), action);
    }

    BinaryTreeNode<T>* GetRoot()
    {
        BinaryTreeNode<T>* n = new BinaryTreeNode<T>();
        n = this->root;
        return n;
    }

    void SetRoot(T element)
    {
        this->root->SetItem(element);
    }

    int GetHeight()
    {
        return max(this->root->GetLeft()->Count(), this->root->GetRight()->Count()) + 1;
    }

    int GetSize()
    {
        if (this->root != nullptr)
        {
            return this->Count() + 1;
        }
        else return 0;
    }

    bool IsEmpty()
    {
        if (this->GetSize() == 0)
        {
            return true;
        }
        else return false;
    }

    bool Contains(T item, function<bool(T, T)> cmp)
    {
        BinaryTreeNode<T>* n = new BinaryTreeNode<T>();
        n = this->Find(item, cmp);

        if (n != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Add(T item, function<bool(T, T)> cmp)
    {
        if (this->Contains(item, cmp))
        {
            throw std::out_of_range("Duplicate element");
        }
        else
        {
            if (this->root == nullptr)
            {
                this->root = new BinaryTreeNode<T>(item);
            }
            if (cmp(item, this->root->Get()))
            {
                if (this->root->GetLeft() ==  nullptr)
                {
                    this->root->GetLeft() = new BinaryTreeNode<T>(item);
                }
                else
                {
                    this->root->GetLeft()->Add(item, cmp);
                }
            }
            if (cmp(this->root->Get(), item) && (this->root->Get() != item))
            {
                if (this->root->GetRight() ==  nullptr)
                {
                    this->root->GetRight() = new BinaryTreeNode<T>(item);
                }
                else
                {
                    this->root->GetRight()->Add(item, cmp);
                }
            }
            if (this->root->Get() == item)
            {
                this->root->Get() = item;
            }
            size++;
        }
    }

    BinaryTreeNode<T>* Next()
    {
        if (this->root->GetRight() != nullptr)
        {
            return Min(this->root->GetRight());
        }
    }

    void Remove (T item, function<bool(T, T)> cmp)
    {
        if (this->Contains(item, cmp) == 0)
        {
            throw std::out_of_range("Invalid item");
        }
        else Remove(item, Find(item, cmp), cmp);
        size--;
    }

    void Remove(T item, BinaryTreeNode<T>* node, function<bool(T, T)> cmp)
    {
        if (node->Get() == item && this->root->Get() != item)
        {
            node->RemoveNode(node, this->root->Previous(node->Get()), cmp);
            node = nullptr;
            delete node;
        }
        else if (this->root->Get() == item)
        {
            if (this->root->GetLeft() == nullptr && this->root->GetRight() != nullptr)
            {
                BinaryTreeNode<T>* r = new BinaryTreeNode<T>(this->root->GetRight());
                this->root = r;
            }
            else if (this->root->GetRight() == nullptr && this->root->GetLeft() != nullptr)
            {
                BinaryTreeNode<T>* l = new BinaryTreeNode<T>(this->root->GetLeft());
                this->root = l;
            }
            else if (this->root->GetRight() == nullptr && this->root->GetLeft() == nullptr)
            {
                this->root = nullptr;
            }
            else if (this->root->GetRight() != nullptr && this->root->GetLeft() != nullptr)
            {
                pair<BinaryTreeNode<T>*, BinaryTreeNode<T>*> pair1;
                if (this->root->GetRight()->GetLeft() == nullptr)
                {
                    pair1.first = this->root;
                    pair1.second = this->root->GetRight();
                }
                else
                {
                    pair1 = this->root->Min(this->root->GetRight());
                }
                this->SetRoot(pair1.second->Get());
                if (pair1.first->GetLeft() == pair1.second)
                {
                    pair1.first->GetLeft() = pair1.second->GetRight();
                }
                else
                {
                    pair1.first->GetRight() = pair1.second->GetRight();
                }
                delete pair1.second;
            }
        }
    }

    void Clear(function<bool(T, T)> cmp)
    {
        Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>(this->GetSize());
        s = this->SaveToSequence();
        int length = s->GetLength();
        for (int i = 0; i < length; i++)
        {
            this->Remove(s->Get(i), cmp);
        }
    }

    BinaryTree<T>* Map(function<T(T)> f)
    {
        Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>();
        Sequence<T>* sequenceThis = (Sequence<T>*) new LinkedListSequence<T>();
        sequenceThis = this->SaveToSequence();
        for (int i = 0; i < this->GetSize(); i++)
        {
            s->Append(f(sequenceThis->Get(i)));
        }
        BinaryTree<T>* bt = new BinaryTree<T>(s);
        return bt;
    }

    BinaryTree<T>* Where(function<bool(T)> f)
    {
        Sequence<T>* s = (Sequence<T>*)new LinkedListSequence<T>;
        Sequence<T>* sequenceThis = (Sequence<T>*) new LinkedListSequence<T>();
        sequenceThis = this->SaveToSequence();
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (f(sequenceThis->Get(i)))
            {
                s->Append(sequenceThis->Get(i));
            }
        }
        BinaryTree<T>* bt = new BinaryTree<T>(s);
        return bt;
    }

    T Reduce(function<T(T, T)> f)
    {
        Sequence<T>* sequenceThis = (Sequence<T>*) new LinkedListSequence<T>();
        sequenceThis = this->SaveToSequence();
        T c = sequenceThis->Get(0);
        T x = c;
        for (int i = 0; i < this->GetSize(); i++)
        {
            x = f(sequenceThis->Get(i), x);
        }
        return x;
    }

    BinaryTree<T>* Balance()
    {
        vector<T> v (this->GetSize());
        Sequence<T>* s = (Sequence<T>*) new LinkedListSequence<T>();
        s = this->SaveToSequence();
        for (int i = 0; i < this->GetSize(); i++)
        {
            v[i] = s->Get(i);
        }
        sort(v.begin(), v.end());
        int m = this->GetSize() / 2;
        BinaryTree<T>* tree = new BinaryTree<T>();
        BinaryTreeNode<T>* n = new BinaryTreeNode<T>(v[m]);
        tree->root = n;
        tree->root->GetLeft() = tree->root->BalanceAdd(v, 0, m - 1, tree->root->GetLeft());
        tree->root->GetRight() = tree->root->BalanceAdd(v, m + 1, this->GetSize(), tree->root->GetRight());
        return tree;
    }

    Sequence<T>* SaveToSequence()
    {
        Sequence<T>* s = (Sequence<T>*) new ArraySequence<T>();
        function<void(BinaryTreeNode<T>*, Sequence<T>*)> action = BinaryTree::ToSequence;
        this->Traverse(s, action);
        return s;
    }

    BinaryTree<T>* SubTree(BinaryTreeNode<T>* n, function<bool(T, T)> cmp)
    {
        BinaryTree<T>* subtree = new BinaryTree<T>();
        if (Find(n->Get(), cmp) != nullptr)
        {
            subtree->Add(n->Get(), cmp);
            return subtree;
        }
        else
        {
            return nullptr;
        }
    }

    bool isSubTree(BinaryTree<T>* tree)
    {
        if (tree == nullptr)
        {
            throw std::out_of_range("Invalid tree");
        }
        else if (this == nullptr)
        {
            return true;
        }
        else
        {
            if (tree == this)
            {
                return true;
            }
            else
            {
                return ((this->root->GetLeft() == tree->root) || (this->root->GetRight() == tree->root));
            }
        }
    }

    bool operator==(BinaryTree<T>* tree)
    {
        return this->root == tree->root;
    }

    int Count()
    {
        if(this->root == nullptr)
        {
            return 0;
        }
        int k = 0;
        if (this->root->GetLeft() != nullptr)
        {
            k++;
        }
        if (this->root->GetRight() != nullptr)
        {
            k++;
        }
        k += (this->root->GetLeft()->Count() + this->root->GetRight()->Count());
        return k;
    }
    int GetS()
    {
        return this->size;
    }

    template<class T2>
    void TraverseNode(T2 f, BinaryTreeNode<T>* n, function<void(BinaryTreeNode<T>*, T2)> action)
    {
        if (n != nullptr)
        {
            if (n->GetLeft() != nullptr)
            {
                TraverseNode(f, n->GetLeft(), action);
            }
            action(n, f);
            if (n->GetRight() != nullptr)
            {
                TraverseNode(f, n->GetRight(), action);
            }
        }
    }

    static void ToSequence(BinaryTreeNode<T>* n, Sequence<T>* s)
    {
        if (n != nullptr)
        {
            s->Append(n->Get());
        }
    }
    ~BinaryTree<T>()
    {
        if (this != nullptr && this->root != nullptr)
        {
            delete root;
        }
    }
private:
    BinaryTreeNode<T>* root;
    int size;
};

#endif // BINARYTREE_BINARYTREE
