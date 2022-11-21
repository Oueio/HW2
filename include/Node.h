#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <iostream>

enum colors {
    BLACK, RED
};

template<typename type>
struct Node {
    Node<type> *parent, *left, *right;
    type _key;
    enum colors color;

    Node() : parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

    explicit Node(type key) : parent(nullptr), left(nullptr), right(nullptr), _key(key), color(RED) {}

    void Add(Node<type> *node);

    Node<type> *GrandParent();

    Node<type> *Uncle();
};

extern template
class Node<double>;

#endif //NODE_H
