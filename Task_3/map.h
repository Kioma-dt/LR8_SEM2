#include "avltree.h"
#include <exception>

template <typename Key, typename Value>
struct MapNode{
    Key key;
    Value value;
    std::unique_ptr<MapNode> left;
    std::unique_ptr<MapNode> right;
    int height = 1;

    MapNode(const Key &k, const Value& v) : key(k), value(v) {}
};

template <typename Key, typename Value>
class Map : AVLTree<struct MapNode<Key, Value>>{
    private:
    void insert(std::unique_ptr<MapNode<Key, Value>>& node, const Key& key, const Value& value){
        if(node == nullptr){
            node = std::make_unique<MapNode<Key, Value>>(key, value);
            return;
        }

        if(key < node->key){
            insert(node->left, key, value);
        }
        else if(key > node->key){
            insert(node->right, key, value);
        }
        else{
            node->value = value;
            return;
        }

        AVLTree<MapNode<Key, Value>>::balanceNode(node);
    }

    MapNode<Key, Value>* search(const std::unique_ptr<MapNode<Key, Value>>& node, const Key& key) const{
        if(node == nullptr){
            return nullptr;
        }

        if(key < node->key){
            return search(node->left, key);
        }
        else if(key > node->key){
            return search(node->right, key);
        }
        else{
            return node.get();
        }
    }

    void erase(std::unique_ptr<MapNode<Key, Value>>& node, const Key& key){
        if(node == nullptr){
            return;
        }

        if(key < node->key){
            erase(node->left, key);
        }
        else if(key > node->key){
            erase(node->right, key);
        }
        else{
            if(node->left == nullptr){
                node = std::move(node->right);
            }
            else if(node-> right == nullptr){
                node = std::move(node->left);
            }
            else{
                MapNode<Key, Value> *min = node->right.get();
                while(min->left != nullptr){
                    min = min->left.get();
                }
                node->key = min->key;
                node->value = min->value;
                erase(node->right, min->key);
            }
        }

        if(node != nullptr){
            AVLTree<MapNode<Key, Value>>::balanceNode(node);
        }
    }

    void inOrder(const std::unique_ptr<MapNode<Key, Value>>& node, std::vector<Value>& vector) const{
        if(node == nullptr){
            return;
        }

        inOrder(node->left, vector);
        vector.push_back(node->value);
        inOrder(node->right, vector);
    }

    void preOrder(const std::unique_ptr<MapNode<Key, Value>>& node, std::vector<Value>& vector) const{
        if(node == nullptr){
            return;
        }

        vector.push_back(node->value);
        preOrder(node->left, vector);
        preOrder(node->right, vector);
    }

    void postOrder(const std::unique_ptr<MapNode<Key, Value>>& node, std::vector<Value>& vector) const{
        if(node == nullptr){
            return;
        }

        postOrder(node->left, vector);
        postOrder(node->right, vector);
        vector.push_back(node->value);
    }

    public:

    void insert(const Key& key, const Value& value){
        insert(this->root_, key, value);
    }

    bool contains(const Key& key) const{
        return search(this->root_, key) != nullptr;
    }

    const Value* find(const Key& key) const{
        const MapNode<Key, Value> *node = search(this->root_, key);
        return node != nullptr ? &node->value : nullptr;
    }

    Value& operator[] (const Key& key){
        MapNode<Key, Value> *node = search(this->root_, key);
        if(node == nullptr){
            insert(this->root_, key, Value());
            node = search(this->root_, key);
        }

        return node->value;
    }

    const Value& operator[] (const Key& key) const{
        const MapNode<Key, Value> *node = search(this->root_, key);
        if(node == nullptr){
            throw std::exception();
        }

        return node->value;
    }

    void erase(const Key& key){
        erase(this->root_, key);
    }

    std::vector<Value> printInOrder(){
        std::vector<Value> vector;
        inOrder(this->root_, vector);
        return vector;
    }

    std::vector<Value> printPreOrder(){
        std::vector<Value> vector;
        preOrder(this->root_, vector);
        return vector;
    }

    std::vector<Value> printPostOrder(){
        std::vector<Value> vector;
        postOrder(this->root_, vector);
        return vector;
    }
};