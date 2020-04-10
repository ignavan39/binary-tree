#include <iostream>
#include "BTree.h"
#include "BTree.cpp"
using namespace std;
int main() {
    BTree<int> bt;
    bt.insert(2);
    bt.insert(4);
    bt.insert(0);
    bt.insert(60);
    bt.insert(80);
    bt.insert(90);
    bt.insert(20);
    bt.insert(6);
   // bt.insert(10,3);
    //bt.deleteLeaves();
 //   bt.insert(18);
  //  bt.insert(1);
   // bt.insert(4);
  //  bt.insert(1010101,5);
    cout<<bt;
    cout<<endl;
    vector<int> bin = bt.find(6);
    for(int i : bin){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<bt.checkIsBinary();
    return 0;
}
