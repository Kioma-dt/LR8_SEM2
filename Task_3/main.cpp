#include <iostream>
#include "set.h"

int main(){
    Set<int> set;

    set.insert(10);
    set.insert(20);
    set.insert(30);
    set.insert(100);
    set.insert(200);
    set.insert(150);
    set.insert(300);

    std::vector<int> vector = set.printPostOrder();
    for(auto i: vector){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}