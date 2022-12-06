#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"

template<typename type>
class RedBlackTree {
private:
    Node<type> *root;
    Node<type> *head;

    void leftRotate(Node<type> *node);

    void rightRotate(Node<type> *node);

    void FixColor(Node<type> *node);

    void FixRoot();

    void Clean(Node<type> *node);

public:
    RedBlackTree() : root(0), head(0) {}

    void Insert(type _key);

    Node<type> *Search(type _key);

    Node<type> *Search(type _key) const;

    Node<type> *Min();

    Node<type> *Min() const;

    Node<type> *Max();

    Node<type> *Max() const;

    bool Exists(type _key);

    ~RedBlackTree() {
        Clean(root);
        delete head;
        root = nullptr;
        head = nullptr;
    }

    RedBlackTree<type> &operator=(const RedBlackTree<type> &tree);

    bool Erase(type _key);

    Node<type> *Root() const { return root; }

    Node<type> *Head() const { return head; }
};

template<typename type>
void RedBlackTree<type>::Insert(type _key) {
    if (!root) {
        root = new Node<type>(_key);
        root->red = false;
        head = new Node<type>(_key);
    } else {
        Node<type> *temp = root->Add(_key);
        FixColor(temp);
        FixRoot();
    }
}

template<typename type>
Node<type> *RedBlackTree<type>::Search(type _key) {
    Node<type> *temp = root;
    while (temp) {
        if (_key < temp->key) {
            temp = temp->left;
        } else if (temp->key < _key) {
            temp = temp->right;
        } else {
            return temp;
        }
    }
    return temp;
}

template<typename type>
void RedBlackTree<type>::FixColor(Node<type> *node) {
    if (node == root->left or node == root->right or !node or node == root) {
        return;
    } else if (node->red) {
        if (node->parent and node->parent->red) {
            Node<type> *gp = node->GrandParent();
            Node<type> *uncle = node->Uncle();
            if (uncle and uncle->red) {
                uncle->red = false;
                node->parent->red = false;
                gp->red = true;
                FixColor(gp);
            } else if (gp) {
                if (gp->left and node == gp->left->right) {
                    gp->left->SwapChildren();
                    leftRotate(gp);
                    FixColor(node);
                } else if (gp->left and node == gp->left->left) {
                    leftRotate(gp);
                    FixColor(node);
                } else if (gp->right and node == gp->right->left) {
                    gp->right->SwapChildren();
                    rightRotate(gp);
                    FixColor(node);
                } else if (gp->right and node == gp->right->right) {
                    rightRotate(gp);
                    FixColor(node);
                }
            }
        }
    }
}

template<typename type>
void RedBlackTree<type>::leftRotate(Node<type> *node) {
    Node<type> *temp = node->left;
    temp->parent = node->parent;
    if (temp->parent) {
        if (node == temp->parent->left) {
            temp->parent->left = temp;
        } else {
            temp->parent->right = temp;
        }
    }
    node->left = temp->right;
    node->parent = temp;
    temp->right = node;
    if (temp->left->key < temp->key and temp->left->key < temp->right->key and temp->right->key < temp->key) {
        temp->Swap(temp->right);
    } else if (temp->key < temp->left->key and temp->key < temp->right->key) {
        if (temp->left->key < temp->right->key) {
            temp->Swap(temp->left);
        } else {
            temp->Swap(temp->right);
        }
    } else if (temp->right->key < temp->key and temp->right->key < temp->left->key and temp->left->key < temp->key) {
        temp->Swap(temp->left);
    }
    if (temp) temp->red = false;
    if (temp->left) temp->left->red = true;
    if (temp->right) temp->right->red = true;
    if (temp->right and temp->right->right) temp->right->right->red = false;
    FixRoot();
}

template<typename type>
void RedBlackTree<type>::rightRotate(Node<type> *node) {
    Node<type> *temp = node->right;
    temp->parent = node->parent;
    if (temp->parent) {
        if (node == temp->parent->left) {
            temp->parent->left = temp;
        } else {
            temp->parent->right = temp;
        }
    }
    node->right = temp->left;
    node->parent = temp;
    temp->left = node;
    if (temp->left->key < temp->key and temp->left->key < temp->right->key and temp->right->key < temp->key) {
        temp->Swap(temp->right);
    } else if (temp->key < temp->left->key and temp->key < temp->right->key) {
        if (temp->left->key < temp->right->key) {
            temp->Swap(temp->left);
        } else {
            temp->Swap(temp->right);
        }
    } else if (temp->right->key < temp->key and temp->right->key < temp->left->key and temp->left->key < temp->key) {
        temp->Swap(temp->left);
    }
    if (temp) temp->red = false;
    if (temp->left) temp->left->red = true;
    if (temp->right) temp->right->red = true;
    if (temp->left and temp->left->left) temp->left->left->red = false;
    FixRoot();
}

template<typename type>
void RedBlackTree<type>::FixRoot() {
    while (root->parent and root->parent != head) {
        root = root->parent;
    }
    head->left = root;
    head->right = root;
    root->parent = head;
    head->key = root->key;
    if (root->red) root->red = false;
}

template<typename type>
Node<type> *RedBlackTree<type>::Min() {
    Node<type> *temp = root;
    if (temp) {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
    }
    return temp;
}

template<typename type>
Node<type> *RedBlackTree<type>::Max() {
    Node<type> *temp = root;
    if (temp) {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
    }
    return temp;
}

template<typename type>
bool RedBlackTree<type>::Exists(type _key) {
    if (Search(_key)) {
        return true;
    }
    return false;
}

template<typename type>
void RedBlackTree<type>::Clean(Node<type> *node) {
    if (node) {
        if (node->left) Clean(node->left);
        if (node->right) Clean(node->right);
    }
    delete node;
}

template<typename type>
RedBlackTree<type> &RedBlackTree<type>::operator=(const RedBlackTree<type> &tree) {
    if (&tree == this) return *this;
    root = tree.root;
    head = tree.head;
    return *this;
}

template<typename type>
bool RedBlackTree<type>::Erase(type _key) {
    auto temp = Search(_key);
    Node<type> *temp2;
    if (temp) {
        if (temp->red and temp->left and temp->right) {
            temp2 = temp->left;
            while (temp2->right) {
                temp2 = temp2->right;
            }
            temp->Swap(temp2);
            temp = temp2;
        } else if (!temp->red and temp->left and temp->right) {
            temp2 = temp->left;
            while (temp2->right) {
                temp2 = temp2->right;
            }
            temp->Swap(temp2);
            temp = temp2;
        }
        if (!temp->red and temp->left and !temp->right) {
            temp->Swap(temp->left);
            delete temp;
        } else if (!temp->red and !temp->left and temp->right) {
            temp->Swap(temp->right);
            delete temp;
        } else if (temp->red and !temp->left and !temp->right) {
            if (temp == temp->parent->left) {
                temp->parent->left = nullptr;
            } else {
                temp->parent->right = nullptr;
            }
            delete temp;
        } else {
            if (temp == root) {
                delete root;
                delete head;
                root = nullptr;
                head = nullptr;
            } else {
                auto node = temp->parent;
                if (temp == node->left) {
                    node->left = nullptr;
                } else {
                    node->right = nullptr;
                }
                delete temp;
                node->red = true;
                FixColor(node);
            }
        }
        return true;
    }
    return false;
}

template<typename type>
Node<type> *RedBlackTree<type>::Search(type _key) const {
    Node<type> *temp = root;
    while (temp) {
        if (_key < temp->key) {
            temp = temp->left;
        } else if (temp->key < _key) {
            temp = temp->right;
        } else {
            return temp;
        }
    }
    return temp;
}

template<typename type>
Node<type> *RedBlackTree<type>::Min() const {
    Node<type> *temp = root;
    if (temp) {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
    }
    return temp;
}

template<typename type>
Node<type> *RedBlackTree<type>::Max() const {
    Node<type> *temp = root;
    {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
    }
    return temp;
}

#endif //REDBLACKTREE_H
