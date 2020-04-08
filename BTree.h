//
// Created by necrobuther on 08.04.2020.
//

#ifndef TASK5_BTREE_BTREE_H
#define TASK5_BTREE_BTREE_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
struct node{
    T value;
    node<T> *left;
    node<T> *right;
};


template <typename T>
class BTree {
public:
    BTree();
    ~BTree();
    int average();
    int length();
    int countEven();
    bool allPositive();
    void insert(T key);
    void insert(int chain , T key);
    void inOrderPrint(ostream& os);
    void destroy();
    void deleteLeaves();
    vector<int> find(int x);
    template <typename V> friend ostream& operator<<(ostream& os, BTree<T>& rhs);

private:
    bool find(node<T> * _node, T key, vector<int> &path);
    bool deleteLeaves(node<T>* node);
    void inOrderPrint(node<T> *_node,ostream& os,int level);
    void insert(T key, node<T> *_node);
    void insert(T key,node<T>*_node,int chain);
    void destroy(node<T>* _node);
    node<T>* root;
    int theNumberOfEvenNumbers{};
    int _average{};
    int size{};
    int _positive;
};




#endif //TASK5_BTREE_BTREE_H
