#include "avltree.h"

template <typename Key>
struct SetNode{
    Key key;
    std::unique_ptr<SetNode> left;
    std::unique_ptr<SetNode> right;
    int height = 1;

    SetNode(const Key &k) : key(k) {}
};


template <typename Key>
class Set : AVLTree<struct SetNode<Key>>{

    private:
        void insert(std::unique_ptr<SetNode<Key>>& node, const Key& key){
            if(node == nullptr){
                node = std::make_unique<SetNode<Key>>(key);
                return;
            }

            if(key < node->key){
                insert(node->left, key);
            }
            else if(key > node->key){
                insert(node->right, key);
            }

            AVLTree<SetNode<Key>>::balanceNode(node);
        }

        const SetNode<Key>* search(const std::unique_ptr<SetNode<Key>>& node, const Key& key) const{
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

        void erase(std::unique_ptr<SetNode<Key>>& node, const Key& key){
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
                    SetNode<Key> *min = node->right.get();
                    while(min->left != nullptr){
                        min = min->left.get();
                    }
                    node->key = min->key;
                    erase(node->right, min->key);
                }
            }

            if(node != nullptr){
                AVLTree<SetNode<Key>>::balanceNode(node);
            }
        }

        void inOrder(const std::unique_ptr<SetNode<Key>>& node, std::vector<Key>& vector) const{
            if(node == nullptr){
                return;
            }

            inOrder(node->left, vector);
            vector.push_back(node->key);
            inOrder(node->right, vector);
        }

        void preOrder(const std::unique_ptr<SetNode<Key>>& node, std::vector<Key>& vector) const{
            if(node == nullptr){
                return;
            }

            vector.push_back(node->key);
            preOrder(node->left, vector);
            preOrder(node->right, vector);
        }

        void postOrder(const std::unique_ptr<SetNode<Key>>& node, std::vector<Key>& vector) const{
            if(node == nullptr){
                return;
            }

            postOrder(node->left, vector);
            postOrder(node->right, vector);
            vector.push_back(node->key);
        }


    public:
        void insert(const Key& key){
            insert(this->root_, key);
        }

        bool contains(const Key& key) const{
            return search(this->root_, key) != nullptr;
        }

        void erase(const Key& key){
            erase(this->root_, key);
        }

        std::vector<Key> printInOrder(){
            std::vector<Key> vector;
            inOrder(this->root_, vector);
            return vector;
        }

        std::vector<Key> printPreOrder(){
            std::vector<Key> vector;
            preOrder(this->root_, vector);
            return vector;
        }

        std::vector<Key> printPostOrder(){
            std::vector<Key> vector;
            postOrder(this->root_, vector);
            return vector;
        }
};