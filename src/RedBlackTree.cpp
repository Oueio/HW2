#include "REDBLACKTree.h"

template<typename type>
void RedBlackTree<type>::Insert(Node<type> *node) {
    Node<type> *t1 = this->root;
    Node<type> *t2 = nullptr;
    while (t1 != nullptr) {
        t2 = t1;
        if (node->_key < t1->_key) {
            t1 = t1->left;
        } else {
            t1 = t1->right;
        }
    }
    node->parent = t2;
    if (t2 != nullptr) {
        if (node->_key < t2->_key) {
            t2->left = node;
        } else {
            t2->right = node;
        }
    } else {
        root = node;
    }
    node->color = RED;
    InsertFixUp(node);
}

template<typename type>
void RedBlackTree<type>::RotateLeft(Node<type> *node) {
    Node<type> *temp = node->right;
    node->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else {
        if (node == node->parent->left) {
            node->parent->left = temp;
        } else {
            node->parent->right = temp;
        }
    }
    temp->left = node;
    node->parent = temp;
}

template<typename type>
void RedBlackTree<type>::RotateRight(Node<type> *node) {
    Node<type> *temp = node->left;
    node->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else {
        if (node == node->parent->right) {
            node->parent->right = temp;
        } else {
            node->parent->left = temp;
        }
    }
    temp->right = node;
    node->parent = temp;
}

template<typename type>
void RedBlackTree<type>::InsertFixUp(Node<type> *node) {
    Node<type> *parent = node->parent;
    while (node != root && parent->color == RED) {
        Node<type> *grand_parent = node->GrandParent();
        if (grand_parent->left == parent) {
            Node<type> *uncle = grand_parent->right;
            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand_parent->color = RED;
                node = grand_parent;
                parent = node->parent;
            } else {
                if (parent->right == node) {
                    RotateLeft(parent);
                    std::swap(node, parent);
                }
                RotateRight(grand_parent);
                grand_parent->color = RED;
                parent->color = BLACK;
                break;
            }
        } else {
            Node<type> *uncle = grand_parent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grand_parent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;

                node = grand_parent;
                parent = node->parent;
            } else {
                if (parent->left == node) {
                    RotateRight(parent);
                    std::swap(parent, node);
                }
                RotateLeft(grand_parent);
                parent->color = BLACK;
                grand_parent->color = RED;
                break;
            }
        }
    }
    root->color = BLACK;
}

template<typename type>
void RedBlackTree<type>::Insert(type key) {
    auto temp = new Node<type>(key);
    Insert(temp);
}

template<typename type>
void RedBlackTree<type>::Print() {
    if (this->root == nullptr) {
        std::cout << "Empty RBT";
    } else {
        Print(root);
    }
}

template<typename type>
void RedBlackTree<type>::Print(Node<type> *node) {
    if (node == nullptr)
        return;
    if (node->parent == nullptr)
        std::cout << node->_key << "(" << node->color << ") is root" << std::endl;
    else if (node->parent->left == node) {
        std::cout << node->_key << "(" << node->color << ") is " << node->parent->_key << ' ' << "left child"
                  << std::endl;
    } else {
        std::cout << node->_key << "(" << node->color << ") is "<< node->parent->_key << ' ' << "right child"
                  << std::endl;
    }
    Print(node->left);
    Print(node->right);
}

template<typename type>
void RedBlackTree<type>::Remove(type key) {
    Node<type> *temp = Search(this->root, key);
    if (temp != nullptr) {
        Remove(this->root, key);
    }
}

template<typename type>
Node<type> *RedBlackTree<type>::Search(Node<type> *node, type key) {
    if (node == nullptr || node->_key == key) {
        return node;
    } else if (key > node->_key) {
        return Search(node->right, key);
    } else {
        return Search(node->left, key);
    }
}

template<typename type>
Node<type> *RedBlackTree<type>::Search(type key) {
    return Search(this->root, key);
}

template<class type>
void RedBlackTree<type>::RemoveFixUp(Node<type> *node, Node<type> *parent) {
    Node<type> *temp;
    while ((!node) || node->color == BLACK && node != this->root) {
        if (parent->left == node) {
            temp = parent->right;
            if (temp->color == RED) {
                temp->color = BLACK;
                parent->color = RED;
                RotateLeft(parent);
                temp = parent->right;
            } else {
                if (!(temp->right) || temp->right->color == BLACK) {
                    temp->left->color = BLACK;
                    temp->color = RED;
                    RotateRight(temp);
                    temp = parent->right;
                }
                temp->color = parent->color;
                parent->color = BLACK;
                temp->right->color = BLACK;
                RotateLeft(parent);
                node = this->root;
                break;
            }
        } else {
            temp = parent->left;
            if (temp->color == RED) {
                temp->color = BLACK;
                parent->color = RED;
                RotateRight(parent);
                temp = parent->left;
            }
            if ((!temp->left || temp->left->color == BLACK) &&
                (!temp->right || temp->right->color == BLACK)) {
                temp->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (!(temp->left) || temp->left->color == BLACK) {
                    temp->right->color = BLACK;
                    temp->color = RED;
                    RotateLeft(temp);
                    temp = parent->left;
                }
                temp->color = parent->color;
                parent->color = BLACK;
                temp->left->color = BLACK;
                RotateRight(parent);
                node = this->root;
                break;
            }
        }
    }
    if (node) {
        node->color = BLACK;
    }
}

template<typename type>
void RedBlackTree<type>::Remove(Node<type> *node, type key) {
    Node<type> *child, *parent;
    colors color;
    if (node->left != nullptr && node->right != nullptr) {
        Node<type> *replace = node;
        replace = node->right;
        while (replace->left != nullptr) {
            replace = replace->left;
        }
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = replace;
            } else {
                node->parent->right = replace;
            }
        } else {
            this->root = replace;
        }
        child = replace->right;
        parent = replace->parent;
        color = replace->color;
        if (parent == node) {
            parent = replace;
        } else {
            if (child != nullptr) {
                child->parent = parent;
            }
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == BLACK) {
            RemoveFixUp(child, parent);
        }
        delete node;
        return;
    }
    if (node->left != nullptr) {
        child = node->left;
    } else {
        child = node->right;
    }
    parent = node->parent;
    color = node->color;
    if (child) {
        child->parent = parent;
    }
    if (parent) {
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    } else {
        this->root = child;
    }
    if (color == BLACK) {
        RemoveFixUp(child, parent);
    }
    delete node;
}

template
class RedBlackTree<double>;
