#pragma once

#include <memory>
#include <vector>

template <typename Node>
class AVLTree{
    protected:
        std::unique_ptr<Node> root_;

        int height(const std::unique_ptr<Node>& node) const{
            return node != nullptr ? node->height : 0;
        }

        int balanceFactor(const std::unique_ptr<Node>& node) const{
            if(node == nullptr)
                return 0;

            return height(node->right) - height(node->left);
        }

        void updateHeight(std::unique_ptr<Node>& node){
            node->height = 1 + std::max(height(node->left), height(node->right));
        }

        void rotateLeft(std::unique_ptr<Node>& node){
            std::unique_ptr<Node> childR = std::move(node->right);
            node->right = std::move(childR->left);
            updateHeight(node);
            childR->left = std::move(node);
            updateHeight(childR);
            node = std::move(childR);
        }

        void rotateRight(std::unique_ptr<Node>& node){
            std::unique_ptr<Node> childL = std::move(node->left);
            node->left = std::move(childL->right);
            updateHeight(node);
            childL->right = std::move(node);
            updateHeight(childL);
            node = std::move(childL);
        }

        void balanceNode(std::unique_ptr<Node>& node){
            updateHeight(node);
            int balance = balanceFactor(node);


            if(balance < -1){
                if(balanceFactor(node->left) > 0){
                    rotateLeft(node->left);
                }
                rotateRight(node);
            }
            else if(balance > 1){
                if(balanceFactor(node->right) < 0){
                    rotateRight(node->right);
                }
                rotateLeft(node);
            }
        }
};