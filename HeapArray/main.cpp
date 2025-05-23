#include <iostream>
#include "heaparray.h"

int main(){
    HeapArrayMax<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(16);
    heap.insert(0);

    heap.remove(2);
    heap.getRoot();

    std::cout << heap.extractRoot() << std::endl;

    std::vector<int> ar = heap.array();
    for (auto i : ar){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}