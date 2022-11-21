#include "Node.h"

template<typename type>
void Node<type>::Add(Node<type> *node) {
    if (_key < node->_key) {
        if (this->right == nullptr) {
            right = node;
            node->parent = this;
            node->color = RED;
        } else {
            right->Add(node);
        }
    } else {
        if (this->left == nullptr) {
            left = node;
            node->parent = this;
            node->color = RED;
        } else {
            left->Add(node);
        }
    }
}

template<typename type>
Node<type> *Node<type>::GrandParent() {
    if (this->parent != nullptr) {
        return this->parent->parent;
    }
    return nullptr;
}

template<typename type>
Node<type> *Node<type>::Uncle() {
    Node<type> *grand_parent = GrandParent();
    if (grand_parent == nullptr) {
        return nullptr;
    }
    if (this->parent == grand_parent->left) {
        return grand_parent->right;
    } else {
        return grand_parent->left;
    }
}

template class Node<double>;
