#include <iostream>
#include <string>
#include "set.h"
#include "map.h"

int main(){
    Map <int, std::string> map;

    map.insert(10, "10");
    map.insert(20, "20");
    map.insert(30, "Fuck");
    map.insert(100, "100");
    map.insert(200, "200");
    map.insert(150, "150");
    map.insert(300, "300");

    // if(map.find(200) == nullptr){
    //     std::cout << "Not Good";
    // }
    // else
    map[30] = "LOL";
    map.erase(12);
    std::cout << map.contains(30);
    // std::vector<std::string> vector = map.printPostOrder();
    // for(auto i: vector){
    //     std::cout << i << ' ';
    // }
    std::cout << std::endl;
}