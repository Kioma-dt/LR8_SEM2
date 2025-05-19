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
void HeapArrayMax<T>::shiftUp(std::vector <T>& array, int index){
    while (index > 0){
        int parentIndex = (index - 1) / 2;

        if(heap_[parentIndex] >= heap_[index]){
            break;
        }

        std::swap(heap_[parentIndex], heap_[index]);
        index = parentIndex;
    }
}

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
    heap_.push_back(value);
    int index = heap_.size() - 1;
    shiftUp(heap_, index);
}

template <typename T>
T HeapArrayMax<T>::extractRoot(){
    T max = heap_.front();
    heap_.front() = heap_.back();
    heap_.pop_back();

    heapify(heap_, 0);
    return max;
}

template <typename T>
const T &HeapArrayMax<T>::getRoot(){
    return heap_.front();
}

template <typename T>
void HeapArrayMax<T>::remove(int index){
    heap_[index] = std::numeric_limits<T>::max();

    shiftUp(heap_, index);
    extractRoot();
}

template <typename T>
int HeapArrayMax<T>::size() const{
    return heap_.size();
}

template <typename T>
bool HeapArrayMax<T>::empty() const{
    return heap_.empty();
}

template <typename T>
std::vector<T> HeapArrayMax<T>::array() const{
    return heap_;
}

template <typename T>
void HeapArrayMax<T>::clear(){
    heap_.clear();
}