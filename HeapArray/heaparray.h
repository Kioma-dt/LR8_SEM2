#pragma once
#include <vector>
#include <limits>

template <typename T>
class HeapArrayMax{
    private:
        std::vector<T> heap_;
        void heapify(std::vector <T>& array, int index);
        void shiftUp(std::vector <T>& array, int index);

    public:
        HeapArrayMax() {}
        HeapArrayMax(const std::vector<T> &array);

        void insert(T value);
        T extractRoot();
        const T &getRoot();
        void remove(int index);

        int size() const;
        bool empty() const;
        void clear();
        std::vector<T> array() const;
};

#include "heaparray.tpp"