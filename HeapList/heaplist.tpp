template <typename T>
std::shared_ptr<Node<T>> HeapListMax<T>::insertParent(){
    if(root_ == nullptr){
        return nullptr;
    }

    std::queue<std::shared_ptr<Node<T>>> queue;
    queue.push(root_);

    while(!queue.empty()){
        auto node = queue.front();
        queue.pop();

        if(node->left == nullptr || node->right == nullptr){
            return node;
        }

        queue.push(node->left);
        queue.push(node->right);
    }

    return nullptr;
}

template <typename T>
void HeapListMax<T>::heapify(std::shared_ptr<Node<T>> node){
    while(node != nullptr){
        auto largest = node;
        if (node->left != nullptr && node->left->value > largest->value){
            largest = node->left;
        }
        if (node->right != nullptr && node->right->value > largest->value){
            largest = node->right;
        }

        if(largest != node){
            std::swap(largest->value, node->value);
            node = largest;
        }
        else{
            break;
        }
    }
}

template <typename T>
void HeapListMax<T>::shiftUp(std::shared_ptr<Node<T>> node){
    auto parent = node->parent.lock();

    while(parent != nullptr){
        if(parent->value >= node->value){
            break;
        }

        std::swap(node->value, parent->value);
        node = parent;
        parent = node->parent.lock();
    }
}

template <typename T>
std::shared_ptr<Node<T>> HeapListMax<T>::lastNode(){
    if(root_ == nullptr){
        return nullptr;
    }

    std::queue<std::shared_ptr<Node<T>>> queue;
    queue.push(root_);

    std::shared_ptr <Node<T>> last;
    while (!queue.empty()){
        last = queue.front();
        queue.pop();

        if(last->left != nullptr){
            queue.push(last->left);
        }

        if(last->right != nullptr){
            queue.push(last->right);
        }
    }

    return last;
}

template <typename T>
void HeapListMax<T>::preOrder(std::vector<T>& temp, std::shared_ptr<Node<T>> node) const{
    if (node != nullptr) {
        temp.push_back(node->value);
        preOrder(temp, node->left);
        preOrder(temp, node->right);
    }
}

template <typename T>
void HeapListMax<T>::insert(T value){
    auto node = std::make_shared<Node<T>>(value);
    size_++;

    if (root_ == nullptr){
        root_ = node;
        return;
    }

    auto parent = insertParent();
    node->parent = parent;
    if (parent->left == nullptr)
    {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    shiftUp(node);
}

template <typename T>
T HeapListMax<T>::extractRoot(){
    if(root_ == nullptr){
        return NULL;
    }

    T max = root_->value;

    auto last = lastNode();

    if(last == root_){
        root_ = nullptr;
        size_ = 0;
        return max;
    }

    root_->value = last->value;
    auto parentLast = last->parent.lock();

    if(parentLast->left == last){
        parentLast->left.reset();
    }
    else if(parentLast->right == last){
        parentLast->right.reset();
    }

    size_--;
    heapify(root_);

    return max;
}

template <typename T>
const T &HeapListMax<T>::getRoot(){
    return root_->value;
}

template <typename T>
int HeapListMax<T>::size() const{
    return size_;
}

template <typename T>
bool HeapListMax<T>::empty() const{
    return size_ == 0;
}

template <typename T>
void HeapListMax<T>::clear(){
    root_.reset();
}

template <typename T>
std::vector<T> HeapListMax<T>::printPreOrder() const{
    std::vector<T> vector;
    preOrder(vector, root_);
    return vector;
}