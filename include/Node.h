#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename type>
struct Node {
    Node<type> *parent, *left, *right;
    type key;
    bool red;

    Node() : parent(nullptr), left(0), right(0), red(true) {}

    explicit Node(type key) : parent(0), left(0), right(0), key(key), red(true) {}

    Node<type> *Add(type _key);

    Node<type> *GrandParent();

    Node<type> *Uncle();

    Node<type> *Swap(Node<type> *node);

    void SwapChildren();

private:
    Node<type> *Add(Node<type> *node);

};

template<typename type>
Node<type> *Node<type>::Add(type _key) {
    return Add(new Node<type>(_key));
}

template<typename type>
Node<type> *Node<type>::Add(Node<type> *node) {
    if (node->key < key) {
        if (!left) {
            left = node;
            left->parent = this;
            return left;
        } else {
            left->Add(node);
        }
    } else {
        if (!right) {
            right = node;
            right->parent = this;
            return right;
        } else {
            right->Add(node);
        }
    }
}

template<typename type>
Node<type> *Node<type>::GrandParent() {
    if (parent) {
        return parent->parent;
    }
    return nullptr;
}

template<typename type>
Node<type> *Node<type>::Uncle() {
    if (parent) {
        Node<type> *gp = GrandParent();
        if (gp) {
            if (parent == gp->left) {
                return gp->right;
            } else {
                return gp->left;
            }
        }
    }
    return nullptr;
}

template<typename type>
Node<type> *Node<type>::Swap(Node<type> *node) {
    if (this->left == node or this->right == node or this->parent == node) {
        std::swap(key, node->key);
    } else {
        if (left and node->left) {
            std::swap(left->parent, node->left->parent);
        }
        std::swap(left, node->left);
        if (right and node->right) {
            std::swap(right->parent, node->right->parent);
        }
        std::swap(right, node->right);
        if (parent and node->parent) {
            if (this == parent->left) {
                if (node == node->parent->left) {
                    std::swap(parent->left, node->parent->left);
                } else {
                    std::swap(parent->left, node->parent->right);
                }
            } else {
                if (node == node->parent->left) {
                    std::swap(parent->left, node->parent->left);
                } else {
                    std::swap(parent->left, node->parent->right);
                }
            }
        }
        std::swap(parent, node->parent);
    }
    return node;
}

template<typename type>
void Node<type>::SwapChildren() {
    std::swap(left, right);
}


#endif //NODE_H
