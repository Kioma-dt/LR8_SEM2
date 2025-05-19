#pragma once
#include <vector>

template <typename T>
class HeapArrayMax{
    private:
        std::vector<T> heap_;
        void heapify(std::vector <T>& array, int index);

    public:
        HeapArrayMax() {}
        HeapArrayMax(const std::vector<T> &array);

        void insert(T value);
        const T &extractRoot();
        const T &getRoot();
        void remove(int index);
};