#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"

template<typename type>
class RedBlackTree {
private:
    Node<type> *root;

    void RotateLeft(Node<type> *node);

    void RotateRight(Node<type> *node);

    void Insert(Node<type> *node);

    void InsertFixUp(Node<type> *node);

    void Print(Node<type> *node);

    void Remove(Node<type> *node, type key);

    void RemoveFixUp(Node<type> *node, Node<type> *parent);

    Node<type> *Search(Node<type> *node, type key);

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(type key);

    void Print();

    void Remove(type key);

    Node<type> *Search(type key);
};

extern template
class RedBlackTree<double>;

#endif //REDBLACKTREE_H
