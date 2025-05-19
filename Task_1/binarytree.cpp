#include "binarytree.h"

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::insert(Node<Key, Value>* node, Key key, Value value) {


    if (node == nullptr) {
        return new Node(key, value);
    }


    else if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else {
        node->right = insert(node->right, key, value);
    }

    return node;
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::remove(Node<Key, Value>* node, Key key) {


    if (node == nullptr) {
        return nullptr;
    }


    if (key < node->key) {
        node->left = remove(node->left, key);
    }


    else if (key > node->key) {
        node->right = remove(node->right, key);
    }

    else {


        if (node->left == nullptr) {
            Node<Key, Value>* temp = node->right;
            delete node->left;
            return temp;
        }


        else if (node->right == nullptr) {
            Node<Key, Value>* temp = node->left;
            delete node->right;
            return temp;
        }

        Node<Key, Value>* min = findMin(node->right);
        node->key = min->key;
        node->value = min->value;
        node->right = remove(node->right, min->key);
    }

    return node;
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::removeSubtree(Node<Key, Value>* node, Key key){
    if(node == nullptr){
        return node;
    }

    if(key < node->key){
        return removeSubtree(node->left);
    }
    else if(key > node->key){
        return removeSubtree(node->right);
    }
    else{
        destroy(node);
        return nullptr;
    }

    return node;
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::search(Node<Key, Value>* node, Key key) {


    if (node == nullptr || node->key == key) {
        return node;
    }


    else if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::findMin(Node<Key, Value>* node) {


    while (node->left != nullptr) {
        return findMin(node->left);
    }

    return node;
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::findMax(Node<Key, Value>* node) {


    while (node->right != nullptr) {
        return findMax(node->right);
    }

    return node;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::destroy(Node<Key, Value>* node) {


    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::preOrder(Node<Key, Value>* node) {
    std::vector<Value> temp;


    if (node != nullptr) {
        temp.push_back(node->value);
        temp.push_back(preOrder(node->left));
        temp.push_back( preOrder(node->right));
    }

    return temp;
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::postOrder(Node<Key, Value>* node) {
    std::vector<Value> temp;

    if (node != nullptr) {
        temp.push_back(postOrder(node->left));
        temp.push_back(postOrder(node->right));
        temp.push_back(node->value);
    }

    return temp;
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::inOrder(Node<Key, Value>* node) {
    std::vector<Value> temp;

    if (node != nullptr) {
        temp.push_back( inOrder(node->left));
        temp.push_back (node->value);
        temp.push_back(inOrder(node->right));
    }

    return temp;
}

template <typename Key, typename Value>
int BinaryTree<Key, Value>::bstToVine(Node<Key, Value>* grand) {
    int count = 0;

    Node<Key, Value>* tmp = grand->right;


    while (tmp != nullptr) {
        if (tmp->left != nullptr) {
            Node<Key, Value>* oldTmp = tmp;
            tmp = tmp->left;
            oldTmp->left = tmp->right;
            tmp->right = oldTmp;
            grand->right = tmp;
        }

        else {
            count++;
            grand = tmp;
            tmp = tmp->right;
        }
    }

    return count;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::compress(Node<Key, Value>* grand, int m) {
    Node<Key, Value>* tmp = grand->right;


    for (int i = 0; i < m; i++) {
        Node<Key, Value>* oldTmp = tmp;
        tmp = tmp->right;
        grand->right = tmp;
        oldTmp->right = tmp->left;
        tmp->left = oldTmp;
        grand = tmp;
        tmp = tmp->right;
    }
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::balanceBst(Node<Key, Value>* root) {
    Node<Key, Value>* grand = new Node<Key, Value>(NULL);

    grand->right = root;

    int count = bstToVine(grand);
    int height = log2(count + 1);
    int m = pow(2, height) - 1;

    compress(grand, count - m);


    for (m = m / 2; m > 0; m /= 2) {
        compress(grand, m);
    }

    return grand->right;
}

template <typename Key, typename Value>
Node<Key, Value> *BinaryTree<Key, Value>::lowestCommonAncestor(Node<Key, Value>* node, Key key_1, Key key_2){
    if (node == nullptr){
        return nullptr;
    }

    if(key_1 < node->key && key_2 < node->key){
        return lowestCommonAncestor(node->left, key_1, key_2);
    }
    else if(key_1 > node->key && key_2 > node->key){
        return lowestCommonAncestor(node->right, key_1, key_2);
    }

    return node;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::~BinaryTree() {
    destroy(root);
}

template <typename Key, typename Value>
Node<Key, Value>* BinaryTree<Key, Value>::getRoot() const {
    return root;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::insert(Key key, Value value) {
    root = insert(root, key, value);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::insertSubtree(Node<Key, Value> *subtree){
    if(subtree != nullptr){
        insert(subtree->key, subtree->value);
        insertSubtree(subtree->left);
        insertSubtree(subtree->right);
    }
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::insertAt(Key *parentKey, Key key, Value value, bool left){
    Node<Key, Value> parent = search(parentKey);
    if(parent == nullptr){
        return false;
    }

    if(left){
        if(parent->left != nullptr){
            return false;
        }
        parent->left = new Node(key, value);
    }
    else{
        if(parent->right != nullptr){
            return false;
        }
        parent->right = new Node(key, value);
    }

    return true;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::remove(Key key) {
    root = remove(root, key);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::removeSubtree(Key key){
    root = removeSubtree(root, key);
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::find(Key key) {
    return search(root, key) != nullptr;
}

template <typename Key, typename Value>
Value BinaryTree<Key, Value>::value(Key key) {
    Node<Key, Value>* founded = search(root, key);


    if (founded != nullptr) {
        return founded->value;
    }

    return NULL;
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::printPreOrder() {
    return preOrder(root);
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::printPostOrder() {
    return postOrder(root);
}

template <typename Key, typename Value>
std::vector<Value> BinaryTree<Key, Value>::printInOrder() {
    return inOrder(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::balance() {
    root = balanceBst(root);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::changeMinAndMax() {


    if (root != nullptr) {
        Node<Key, Value>* min = findMin(root);
        Node<Key, Value>* max = findMax(root);
        Value temp = min->value;
        min->value = max->value;
        max->value = temp;
    }
}

template <typename Key, typename Value>
Key BinaryTree<Key, Value>::lowestCommonAncestor(Key key_1, Key key_2){
    return lowestCommonAncestor(root, key_1, key_2)->key;
}
