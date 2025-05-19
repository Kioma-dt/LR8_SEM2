#include "heaparray.h"

template <typename T>
void HeapArrayMax<T>::heapify(std::vector <T>& array, int index){
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (array[largest] < array[left]){
        largest = left;
    }
    
    if (array[largest] < array[right]){
        largest = right;
    }

    if (largest != index){
        std::swap(array[index], array[largest]);
        heapify(array, largest);
    }
};

template <typename T>
HeapArrayMax<T>::HeapArrayMax(const std::vector<T> &array){
    heap_ = array;
    for (int i = heap_.size() / 2 - 1; i >= 0; i--)
    {
        heapify(heap_, i);
    }
}

template <typename T>
void HeapArrayMax<T>::insert(T value){
    wh
}