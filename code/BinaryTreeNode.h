#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include "SEQUENCE.H"
#include <utility>
#include <functional>
#include <vector>
#include "STUDENTS.H"
#include "TEACHER.H"

template<class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode()
    {
        this->left = nullptr;
        this->right = nullptr;
    }

    BinaryTreeNode(T item)
    {
        this->item = item;
        this->left = nullptr;
        this->right = nullptr;
    }

    BinaryTreeNode(const BinaryTreeNode<T>& n)
    {
        this->item = n.item;
        this->left = n.GetLeft();
        this->right = n.GetRight();
    }

    BinaryTreeNode(BinaryTreeNode<T>* n)
    {
        this->item = n->item;
        this->left = n->left;
        this->right = n->right;
    }

    T& Get()
    {
        return this->item;
    }

    void SetItem(T element)
    {
        this->item = element;
    }

    BinaryTreeNode<T>*& GetLeft()
    {
        return this->left;
    }

    void SetLeft(BinaryTreeNode<T>* left)
    {
        this->left = new BinaryTreeNode<T>();
        this->left = left;
    }

    BinaryTreeNode<T>*& GetRight()
    {
        return this->right;
    }

    void SetRight(BinaryTreeNode<T>* right)
    {
        this->right = new BinaryTreeNode<T>();
        this->right = right;
    }

    void Add(T item, function<bool(T, T)> cmp)
    {
        if (cmp(item, this->Get()))
        {
            if (this->GetLeft() ==  nullptr)
            {
                this->GetLeft() = new BinaryTreeNode<T>(item);
            }
            else
            {
                this->GetLeft()->Add(item, cmp);
            }
        }
        else if (cmp(this->Get(), item) && (this->Get() != item))
        {
            if (this->GetRight() ==  nullptr)
            {
                this->GetRight() = new BinaryTreeNode<T>(item);
            }
            else
            {
                this->GetRight()->Add(item, cmp);
            }
        }
        else if (this->Get() == item)
        {
            this->item = item;
        }
    }

    BinaryTreeNode<T>* Find(T item, function<bool(T, T)> cmp)
    {
        if (this != nullptr && this->item == item)
        {
            return this;
        }
        else if (this != nullptr && cmp(this->item, item))
        {
            if (this->right != nullptr)
            {
                return this->GetRight()->Find(item, cmp);
            }
            else
            {
                return nullptr;
            }

        }
        else if (this != nullptr && cmp(item, this->item))
        {
            if (this->left != nullptr)
            {
                return this->GetLeft()->Find(item, cmp);
            }
            else
            {
                return nullptr;
            }
        }
    }

    BinaryTreeNode<T>* Previous(T element)
    {
        if (this == nullptr || this->Get() == element)
        {
            return nullptr;
        }
        if ((this->left != nullptr && this->left->Get() == element) || (this->right != nullptr && this->right->Get() == element))
        {
            return this;
        }
        BinaryTreeNode<T>* prev = this->left->Previous(element);
        if (prev != nullptr)
        {
            return prev;
        }
        prev = this->right->Previous(element);
        return prev;
    }

    BinaryTreeNode<T>* BalanceAdd(vector<T> v, int first, int last, BinaryTreeNode<T>*& node)
    {
        int m = (first + last) / 2;
        BinaryTreeNode<T>* n = new BinaryTreeNode<T>();
        if (m < v.size())
        {
            n->item = v[m];
            node = n;
        }
        if (m - 1 >= first)
        {
            n->left = n->GetLeft()->BalanceAdd(v, first, m - 1, node->GetLeft());
        }
        if (last >= m + 1)
        {
            n->right = n->GetRight()->BalanceAdd(v, m + 1, last, node->GetRight());
        }
        return node;
    }

    void RemoveNode(BinaryTreeNode<T>*& n, BinaryTreeNode<T>* parent, function<bool(T, T)> cmp)
    {
        if (n->left == nullptr && n->right != nullptr)
        {
            BinaryTreeNode<T>* r = new BinaryTreeNode<T>(n->right);
            if (cmp(parent->Get(), n->Get()))
            {
                parent->right = r;
            }
            else if (cmp(n->Get(), parent->Get()))
            {
                parent->left = r;
            }
            n = nullptr;
        }
        else if (n->right == nullptr && n->left != nullptr)
        {
            BinaryTreeNode<T>* l = new BinaryTreeNode<T>(n->left);
            if (cmp(parent->Get(), n->Get()))
            {
                parent->right = l;
            }
            else if (cmp(n->Get(),parent->Get()))
            {
                parent->left = l;
            }
            n = nullptr;
        }
        else if (n->right == nullptr && n->left == nullptr)
        {
            if (cmp(parent->Get(), n->Get()))
            {
                parent->right = nullptr;
            }
            else if (cmp(n->Get(), parent->Get()))
            {
                parent->left = nullptr;
            }
            n = nullptr;
        }
        else if (n->right != nullptr && n->left != nullptr)
        {
            pair<BinaryTreeNode<T>*, BinaryTreeNode<T>*> pair1;
            if (n->right->left == nullptr)
            {
                pair1.first = n;
                pair1.second = n->right;
            }
            else
            {
                pair1 = Min(n->right);
            }
            n->item = pair1.second->item;
            if (pair1.first->left == pair1.second)
            {
                pair1.first->left = pair1.second->right;
            }
            else
            {
                pair1.first->right = pair1.second->right;
            }
            delete pair1.second;
        }
    }

    int Count()
    {
        if(this == nullptr)
        {
            return 0;
        }
        int k = 0;
        if (this->GetLeft() != nullptr)
        {
            k++;
        }
        if (this->GetRight() != nullptr)
        {
            k++;
        }
        k += (this->GetLeft()->Count() + this->GetRight()->Count());
        return k;
    }

    bool operator==(BinaryTreeNode<T>* n)
    {
        if (this == nullptr && n == nullptr)
        {
            return true;
        }
        else if (this == nullptr || n == nullptr)
        {
            return false;
        }
        else
        {
            return (this->Get() == n->Get() && this->GetLeft() == n->GetLeft() && this->GetRight() == n->GetRight());
        }
    }
public:
    pair<BinaryTreeNode<T>*, BinaryTreeNode<T>*> Min(BinaryTreeNode<T>* n)
    {
        pair<BinaryTreeNode<T>*, BinaryTreeNode<T>*> pair1;
        if (n == nullptr)
        {
            pair1.first = nullptr;
            pair1.second = nullptr;
            return pair1;
        }
        else
        {
            while (n->left != nullptr)
            {
                pair1.first = n;
                n = n->left;
                pair1.second = n;
            }
            return pair1;
        }
    }
private:
    T item;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
};

#endif // BINARYTREENODE_H
