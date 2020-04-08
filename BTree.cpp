//
// Created by necrobuther on 08.04.2020.
//

#include "BTree.h"

template<typename T>
BTree<T>::BTree() {
    theNumberOfEvenNumbers = 0;
    size = 0;
    _average = 0;
    _positive = 0;
    root = nullptr;
}

template<typename T>
void BTree<T>::insert(T key, node<T> *_node) {
    if (key < _node->value) {
        if (_node->left != nullptr) {
            insert(key, _node->left);
        } else {
            _node->left = new node<T>;
            _node->left->value = key;
            _node->left->right = nullptr;
            _node->left->left = nullptr;
            size++;
            _average += key;
            if (key % 2 == 0) {
                theNumberOfEvenNumbers++;
            }
            if (key > 0) {
                _positive++;
            }
        }
    } else {
        if (_node->right != nullptr) {
            insert(key, _node->right);
        } else {
            size++;
            _average += key;
            if (key % 2 == 0) {
                theNumberOfEvenNumbers++;
            }
            if (key > 0) {
                _positive++;
            }
            _node->right = new node<T>;
            _node->right->value = key;
            _node->right->right = nullptr;
            _node->right->left = nullptr;
        }
    }

}

template<typename T>
void BTree<T>::insert(T key) {
    if (root != nullptr) {
        insert(key, root);
    } else {
        root = new node<T>;
        root->value = key;
        root->left = nullptr;
        root->right = nullptr;
        size++;
        _average += key;
        if (key % 2 == 0) {
            theNumberOfEvenNumbers++;
        }
        if (key > 0) {
            _positive++;
        }
    }
}

template<typename T>
void BTree<T>::inOrderPrint(node<T> *_node, ostream &os, int level) {

    if (_node) {

        inOrderPrint(_node->left, os, level + 1);
        for (int i = 0; i < level * 2; i++) {
            os << " ";
        }
        os << _node->value << endl;
        inOrderPrint(_node->right, os, level + 1);
    }
}

template<typename T>
ostream &operator<<(ostream &os, BTree<T> &rhs) {
    //rhs.representation.clear();
    rhs.inOrderPrint(os);
    return os;

}

template<typename T>
void BTree<T>::inOrderPrint(ostream &os) {

    int level = 1;
    inOrderPrint(root, os, level);
}

template<typename T>
void BTree<T>::destroy(node<T> *_node) {
    if (_node != nullptr) {
        destroy(_node->left);
        destroy(_node->right);
        delete _node;
    }
}

template<typename T>
void BTree<T>::destroy() {
    destroy(root);
    theNumberOfEvenNumbers = 0;
    size = 0;
    _average = 0;
    _positive = 0;

}

template<typename T>
BTree<T>::~BTree() {
    destroy();
}

template<typename T>
int BTree<T>::average() {
    return _average / size;
}

template<typename T>
int BTree<T>::length() {
    return size;
}

template<typename T>
int BTree<T>::countEven() {
    return theNumberOfEvenNumbers;
}

template<typename T>
bool BTree<T>::allPositive() {
    return _positive == size;
}

template<typename T>
void BTree<T>::insert(int chain, T key) {
    insert(key, root, chain);
}

template<typename T>
void BTree<T>::insert(T key, node<T> *_node, int chain) {
    if (chain % 10 == 0 && chain > 0) {
        if (_node->left != nullptr) {
            insert(key, _node->left, chain / 10);
        } else {
            _node->left = new node<T>;
            _node->left->value = key;
            _node->left->right = nullptr;
            _node->left->left = nullptr;
            size++;
            _average += key;
            if (key % 2 == 0) {
                theNumberOfEvenNumbers++;
            }
            if (key > 0) {
                _positive++;
            }

            insert(key, _node->left, chain / 10);
        }
    }
    if (chain % 10 == 1 && chain > 0) {
        if (_node->right != nullptr) {
            insert(key, _node->right, chain / 10);
        } else {

            _node->right = new node<T>;
            _node->right->value = key;
            _node->right->right = nullptr;
            _node->right->left = nullptr;
            size++;
            _average += key;
            if (key % 2 == 0) {
                theNumberOfEvenNumbers++;
            }
            if (key > 0) {
                _positive++;
            }
            insert(key, _node->right, chain / 10);
        }
    }
}

template<typename T>
bool BTree<T>::deleteLeaves(node<T> *_node) {
    if (!_node) { return false; }
    if (!_node->left && !_node->right) {
        delete _node;
        return true;
    } else {
        if (deleteLeaves(_node->left)) {
            _node->left = nullptr;
        }
        if (deleteLeaves(_node->right)) {
            _node->right = nullptr;
        }
    }
    return false;
}

template<typename T>
void BTree<T>::deleteLeaves() {
    deleteLeaves(root);
}

template<typename T>
vector<int> BTree<T>::find(int x) {
    std::vector<int> path = {};
    if (!find(root, x, path)) {
        throw exception();
    }
    return path;
}

template<typename T>
bool BTree<T>::find(node<T> *_node, T key, vector<int> &path) {
    if (!_node) { return false; }
    if (_node->value == key) {
        return true;
    }
    path.push_back(0);
    if (find(_node->left, key, path)) { return true; }
    path.pop_back();
    path.push_back(1);
    if (find(_node->right, key, path)) { return true; }
    path.pop_back();
    return false;
}

