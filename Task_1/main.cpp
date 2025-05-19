#include <iostream>
#include "binarytree.h"

int main(){
    BinaryTree<int, int> bst;
    bst.insert(10, 10);
    bst.insert(5, 2);
    bst.insert(100, 34);
    bst.insert(15, 3);

    bst.balance();
    bst.insertAt(10, 16, -4, false);
    bst.balance();
    std::vector<int> a;
    a = bst.printPreOrder();

    for(int i : a){
        std::cout << i << ' ';
    }
    std::cout <<  "Hello"<<std::endl;
}