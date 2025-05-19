#include <iostream>
#include "heaplist.h"

int main(){
    HeapListMax<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(16);
    heap.insert(0);

    std::cout << heap.size() << std::endl;

    std::vector<int> ar = heap.printPreOrder();
    for (auto i : ar){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << heap.extractRoot();
}