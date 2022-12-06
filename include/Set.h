#ifndef SET_H
#define SET_H

#include "RedBlackTree.h"

template<typename type>
class Set {
private:
    RedBlackTree<type> list;
    int _size;
public:

    class iterator {
    private:
        Node<type> *it;
    public:
        iterator() : it(nullptr) {}

        explicit iterator(Node<type> *node) : it(node) {}

        explicit iterator(type _key) : it(new Node<type>(_key)) {}

        type operator*();

        iterator &operator++(int unused);

        iterator &operator++();

        iterator &operator--(int unused);

        iterator &operator--();

        iterator &operator=(const iterator &obj);

        bool operator!=(const iterator &obj);

        bool operator==(const iterator &obj);

        type *operator->();
    };

    Set() : _size(0) {}

    void insert(type _key);

    Set<type> &operator++(int unused);

    Set<type> &operator--(int unused);

    Set(const iterator &it1, const iterator &it2);

    Set(const type *it1, const type *it2);

    Set(type *it1, type *it2);

    Set(const std::initializer_list<type> &list);

    Set(const Set<type> &obj);

    type operator*();

    Set<type> &operator=(const Set<type> &set);

    ~Set() = default;

    iterator begin();

    iterator begin() const;

    iterator end();

    iterator end() const;

    void erase(type _key);

    int size() { return _size; }

    [[nodiscard]] int size() const { return _size; }

    bool empty() { return _size < 1; }

    [[nodiscard]] bool empty() const { return _size == 0; }

    iterator find(type _key);

    iterator find(type _key) const;

    iterator lower_bound(type _key);

    iterator lower_bound(type _key) const;

private:
    iterator it;
};

template<typename type>
void Set<type>::insert(type _key) {
    if (!list.Exists(_key)) {
        list.Insert(_key);
        if (_size == 0) {
            it = iterator(list.Root());
        }
        ++_size;
    }
}

template<typename type>
Set<type> &Set<type>::operator++(int unused) {
    it++;
    return *this;
}

template<typename type>
Set<type> &Set<type>::operator--(int unused) {
    it--;
    return *this;
}

template<typename type>
type Set<type>::operator*() {
    return *(it);
}

template<typename type>
Set<type>::Set(const iterator &it1, const iterator &it2) : _size(0) {
    insert(*it1);
    insert(*it2);
    it = iterator(list.Min());
}

template<typename type>
Set<type>::Set(const std::initializer_list<type> &_list) {
    _size = 0;
    for (auto i: _list) {
        insert(i);
    }
    _size = _list.size();
    it = iterator(list.Min());
}

template<typename type>
Set<type>::Set(const Set<type> &obj) {
    _size = 0;
    for (auto i = obj.begin(); i != obj.end(); i++) {
        insert(*i);
    }
    _size = obj._size;
}

template<typename type>
Set<type> &Set<type>::operator=(const Set<type> &set) {
    if (&set == this) {
        return *this;
    }
    list.~RedBlackTree();
    list = RedBlackTree<type>();
    for (auto i = set.begin(); i != set.end(); i++) {
        insert(*i);
    }
    _size = set._size;
    return *this;
}

template<typename type>
typename Set<type>::iterator Set<type>::begin() {
    return iterator(list.Min());
}

template<typename type>
typename Set<type>::iterator Set<type>::end() {
    return iterator(list.Head());
}

template<typename type>
void Set<type>::erase(type _key) {
    if (list.Erase(_key)) {
        --_size;
    }
}

template<typename type>
typename Set<type>::iterator Set<type>::find(type _key) {
    auto temp = list.Search(_key);
    if (temp) {
        return iterator(temp);
    }
    return end();
}

template<typename type>
typename Set<type>::iterator Set<type>::lower_bound(type _key) {
    for (auto i = begin(); i != end(); i++) {
        if (_key < *i) {
            return i;
        }
    }
}

template<typename type>
typename Set<type>::iterator Set<type>::find(type _key) const {
    auto temp = list.Search(_key);
    if (temp) {
        return iterator(temp);
    }
    return end();
}

template<typename type>
typename Set<type>::iterator Set<type>::lower_bound(type _key) const {
    if (list.Max()->key <= _key) {
        return end();
    }
    if (_key <= list.Min()->key) {
        return iterator(list.Min());
    }
    for (auto i = begin(); i != end(); i++) {
        if (_key < *i) {
            return i;
        }
    }
}

template<typename type>
typename Set<type>::iterator Set<type>::begin() const {
    return iterator(list.Min());
}

template<typename type>
typename Set<type>::iterator Set<type>::end() const {
    return iterator(list.Head());
}

template<typename type>
Set<type>::Set(const type *it1, const type *it2) {
    type *i;
    for (i = it1; i != it2; ++i) {
        insert(*i);
    }
    _size = it2 - it1;
}

template<typename type>
Set<type>::Set(type *it1, type *it2) {
    type *i;
    _size = 0;
    for (i = it1; i != it2; ++i) {
        insert(*i);
    }
    _size = it2 - it1;
}

template<typename type>
typename Set<type>::iterator &Set<type>::iterator::operator++(int unused) {
    if (it->parent) {
        auto key = it->key;
        do {
            if (it->right and key < it->right->key) {
                it = it->right;
                while (it->left) {
                    it = it->left;
                }
            } else {
                it = it->parent;
            }
        } while (it and it->key < key and it->parent);
        return *this;
    }
}

template<typename type>
type Set<type>::iterator::operator*() {
    return it->key;
}

template<typename type>
typename Set<type>::iterator &Set<type>::iterator::operator=(const iterator &obj) {
    if (&obj == this) return *this;
    it = obj.it;
    return *this;
}

template<typename type>
typename Set<type>::iterator &Set<type>::iterator::operator--(int unused) {
    if (it->parent) {
        auto key = it->key;
        do {
            if (it->left and it->left->key < key) {
                it = it->left;
                while (it->right) {
                    it = it->right;
                }
            } else {
                it = it->parent;
            }
        } while (it and key < it->key);
    } else {
        it = it->left;
        while (it->right) {
            it = it->right;
        }
    }
    return *this;
}

template<typename type>
bool Set<type>::iterator::operator!=(const Set::iterator &obj) {
    if (it != obj.it) {
        return true;
    }
    return false;
}

template<typename type>
typename Set<type>::iterator &Set<type>::iterator::operator++() {
    if (it->parent) {
        auto key = it->key;
        do {
            if (it->right and key < it->right->key) {
                it = it->right;
                while (it->left) {
                    it = it->left;
                }
            } else {
                it = it->parent;
            }
        } while (it and it->key < key and it->parent);
    }
    return *this;
}

template<typename type>
typename Set<type>::iterator &Set<type>::iterator::operator--() {
    if (it->parent) {
        auto key = it->key;
        do {
            if (it->left and it->left->key < key) {
                it = it->left;
                while (it->right) {
                    it = it->right;
                }
            } else {
                it = it->parent;
            }
        } while (it and key < it->key);
    } else {
        it = it->left;
        while (it->right) {
            it = it->right;
        }
    }
    return *this;
}

template<typename type>
bool Set<type>::iterator::operator==(const Set::iterator &obj) {
    if (it == obj.it) {
        return true;
    }
    return false;
}

template<typename type>
type *Set<type>::iterator::operator->() {
    return &it->key;
}

#endif //SET_H
