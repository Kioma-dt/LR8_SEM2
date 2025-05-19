#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <cmath>

template <typename Key, typename Value>
struct Node {
    Key key;
    Value value;
    Node* left;
    Node* right;

    Node(Key k = NULL, Value val = NULL)
        : key(k), value(val), left(nullptr), right(nullptr) {}
};

template <typename Key, typename Value> 
class BinaryTree {
   private:
    Node<Key, Value>* root;

    Node<Key, Value>* insert(Node<Key, Value>* node, Key key, Value value);

    Node<Key, Value>* remove(Node<Key, Value>* node, Key key);  
    Node<Key, Value>* removeSubtree(Node<Key, Value>* node, Key key);  

    Node<Key, Value>* search(Node<Key, Value>* node, Key key);

    Node<Key, Value>* findMin(Node<Key, Value>* node);
    Node<Key, Value>* findMax(Node<Key, Value>* node);

    void destroy(Node<Key, Value>* node);

    std::vector<Value> preOrder(Node<Key, Value>* node);
    std::vector<Value> postOrder(Node<Key, Value>* node);
    std::vector<Value> inOrder(Node<Key, Value>* node);

    int bstToVine(Node<Key, Value>* grand);
    void compress(Node<Key, Value>* grand, int m);
    Node<Key, Value>* balanceBst(Node<Key, Value>* root);

    Node<Key, Value> *lowestCommonAncestor(Node<Key, Value>* node, Key key_1, Key key_2);

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree();
    Node<Key, Value>* getRoot() const;
    void insert(Key key, Value value);
    void insertSubtree(Node<Key, Value> *subtree);
    bool insertAt(Key *parentKey, Key key, Value value, bool left);
    void remove(Key key);
    void removeSubtree(Key key);  
    bool find(Key key);
    Value value(Key key);
    std::vector<Value> printPreOrder();
    std::vector<Value> printPostOrder();
    std::vector<Value> printInOrder();
    void balance();
    void changeMinAndMax();
    Key lowestCommonAncestor(Key key_1, Key key_2);
};

#endif	// BINARYTREE_H
