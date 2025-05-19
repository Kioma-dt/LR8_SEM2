#include <memory>
#include <vector>
#include <queue>

template <typename T>
struct Node{
    T value;
    std::shared_ptr<Node<T>> left = nullptr;
    std::shared_ptr<Node<T>> right = nullptr;
    std::weak_ptr<Node<T>> parent;

    Node(T val = NULL) : value(val) {}
};

template <typename T>
class HeapListMax{
    private:
        std::shared_ptr<Node<T>> root_;
        int size_;

        std::shared_ptr<Node<T>> insertParent();
        void heapify(std::shared_ptr<Node<T>> node);
        void shiftUp(std::shared_ptr<Node<T>> node);
        std::shared_ptr<Node<T>> lastNode();

        void preOrder(std::vector<T>& temp, std::shared_ptr<Node<T>> node) const;

    public:
        HeapListMax() : root_(nullptr), size_(0) {}

        void insert(T value);
        T extractRoot();
        const T &getRoot();

        int size() const;
        bool empty() const;
        void clear();

        std::vector<T> printPreOrder() const;
};

#include "heaplist.tpp"