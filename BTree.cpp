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
double BTree<T>::average() {
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

template<typename T>
void BTree<T>::findMin(node<T> *_node, int &min) {
    if (!_node) {
        return;
    }
    if (_node->value < min) {
        min = _node->value;
    }
    findMin(_node->left, min);
    findMin(_node->right, min);
}

template<typename T>
void BTree<T>::findMax(node<T> *_node, int &max) {
    if (!_node) { return; }
    if (_node->value > max) {
        max = _node->value;
    }
    findMax(_node->left, max);
    findMax(_node->right, max);
}

template<typename T>
bool BTree<T>::checkIsBinary(node<T> *_node, int min, int max) {
    if (!_node) { return true; }
    if (_node->value < min || root->value > max) {
        return false;
    }
    if (_node->value == min && _node->left && this->root->value == _node->value) {
        return false;
    }
    if (_node->value == max && _node->right && this->root->value == _node->value) {
        return false;
    }
    return checkIsBinary(_node->left, min, _node->value) && checkIsBinary(_node->right, _node->value, max);
}

template<typename T>
bool BTree<T>::checkIsBinary() {
    int max = INTMAX_MIN, min = INTMAX_MAX;
    findMin(root->left, min);
    findMax(root->right, max);
    return checkIsBinary(root, min, max);
}

template<typename T>
BTree<T>::BTree(BTree<T> &&copy) noexcept {
    std::swap(root, copy.root);
    theNumberOfEvenNumbers = copy.theNumberOfEvenNumbers;
    size = copy.size;
    _average = copy._average;
    _positive = copy._positive;
}

template<typename T>
BTree<T>::BTree(BTree<T> &_copy) {
    if (!_copy.root) {
        return;
    }
    theNumberOfEvenNumbers = _copy.theNumberOfEvenNumbers;
    size = _copy.size;
    _average = _copy._average;
    _positive = _copy._positive;
    copy(root, _copy.root);
}

template<typename T>
void BTree<T>::copy(node<T> *_node, node<T> *_copy) {
    if (!_copy) {
        return;
    }
    _node = new node<T>;
    _node->value = _copy->value;
    _node->right = nullptr;
    _node->left = nullptr;
    copy(_node->left, _copy->left);
    copy(_node->right, _copy->right);
}

template<typename T>
BTree<T> &BTree<T>::operator=(const BTree<T> &_copy) {
    if (this == &copy) { return *this; }
    this->destroy();

    root = new node<T>;
    root->value = _copy.root->value;
    copy(root, _copy.root);
    theNumberOfEvenNumbers = _copy.theNumberOfEvenNumbers;
    size = _copy.size;
    _average = _copy._average;
    _positive = _copy._positive;
    return *this;
}



