#include <iostream>
#include "hashtable.h"

int main(){
    HashTable<int, std::string> hash;
    hash.insert(10, "10");
    hash.insert(20, "FUCK");
    hash[10] = "KEK";
    hash[30];
    std::cout << hash[30] << std::endl;
}