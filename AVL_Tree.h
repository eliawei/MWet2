//
// Created by Gchiko on 04-Dec-18.
//

#ifndef MWET1_AVL_TREE_H
#define MWET1_AVL_TREE_H

#include <stdio.h>
#include <iostream>
#include "exceptions.h"

using namespace std;

template<class S, class T,class UpdateFunc>
class AVL_Tree {
    class Node {
        S key; // the key of the node.
        T data; // the data that the node contains.
        int height; //the height of the node in the tree.
        Node *left = nullptr; // the left son of the node.
        Node *right = nullptr; // the right son of the node.
        Node *parent = nullptr; // the parent of the node.

        friend class AVL_Tree; // now class AVL_Tree can access
        // private members of Node

    public:

        /**
         * the basic c'tor, constructs a node with given data and key.
         * @param key - the key that the link contains.
         * @param data - the data that the link contains.
         */
        Node(const S &key, const T &data) : key(key), data(data) {}

        /**
         * indicates if the node is right or left son.
         * @return true if the node is right son and false otherwise.
         */
        bool is_right_son() {
            return parent->key < key;
        }

        /**
         * getting the next node in order.
         * @return the first node that his key is bigger.
         */
        Node *next_inorder() {
            Node *t = right;
            while (t->left) {
                t = t->left;
            }
            return t;
        }

        /**
         * updates the height of the node by his son's heights.
         */
        void update_height() {
            int right_h = -1, left_h = -1;
            if (right) {
                right_h = right->height;
            }
            if (left) {
                left_h = left->height;
            }
            height = max(right_h, left_h) + 1;
        }

        /**
         * calculates the balance factor of the node by his son's heights.
         * @return the difference between left son's and right son's heights.
         */
        int BF() {
            int right_h = -1, left_h = -1;
            if (right) {
                right_h = right->height;
            }
            if (left) {
                left_h = left->height;
            }
            return ((left_h) - (right_h));
        }

        /**
         * activates the basic LL roll as we studied in class.
         */
        void roll_right() {
            Node *left_son = left;
            Node *left_right_son = nullptr;
            if (left_son->right) {
                left_right_son = left_son->right;
            }

            left_son->right = this;
            left = left_right_son;
            if (left_right_son) {
                left_right_son->parent = this;
            }

            left_son->parent = this->parent;
            if (left_son->parent != NULL) {
                if (left_son->is_right_son()) {
                    left_son->parent->right = left_son;
                } else {
                    left_son->parent->left = left_son;
                }
            }

            this->parent = left_son;
            this->update_height();
            left_son->update_height();
        }

        /**
         * activates the basic RR roll as we studied in class.
         */
        void roll_left() {
            Node *right_son = right;
            Node *right_left_son = nullptr;
            if (right_son->left) {
                right_left_son = right_son->left;
            }

            right_son->left = this;
            right = right_left_son;
            if (right_left_son) {
                right_left_son->parent = this;
            }

            right_son->parent = this->parent;
            if (right_son->parent != NULL) {
                if (right_son->is_right_son()) {
                    right_son->parent->right = right_son;// for normal RR - if it's part of LR need to do something else
                } else {
                    right_son->parent->left = right_son;
                }
            }

            this->parent = right_son;
            this->update_height();
            right_son->update_height();
        }

        /**
         * activates LR roll as we studied in class.
         */
        void LR() {
            this->left->roll_left();
            roll_right();
        }

        /**
         * activates RL roll as we studied in class.
         */
        void RL() {
            this->right->roll_right();
            roll_left();
        }

        /**
         * activates a roll according to the node and his son's BF.
         */
        void roll() {
            int BF_Self = BF();
            int BFL = -2, BFR = 2;
            if (left) {
                BFL = (left->BF());
            }
            if (right) {
                BFR = (right->BF());
            }
            if (BF_Self == 2) {
                if (BFL >= 0) {
                    roll_right();
                }
                if (BFL == -1) {
                    LR();
                }
            } else if (BF_Self == -2) {
                if (BFR == 1) {
                    RL();
                }
                if (BFR <= 0) {
                    roll_left();
                }
            }

        }

        void print_node() {
            int left_key;
            if (left) {
                left_key = left->key;
            } else {
                left_key = -1;
            }
            int right_key;
            if (right) {
                right_key = right->key;
            } else {
                right_key = -1;
            }

            int parent_key;
            if (parent) {
                parent_key = parent->key;
            } else {
                parent_key = -1;
            }

            cout << " key: " << key << " parent: " << parent_key <<
                 //" Data: " << data  <<
                 " left: " << left_key << " right: " << right_key << " height: " << height << endl;
        }
    };

private:
    Node *root = nullptr; // pointer for the root of the tree.
    int size = 0; // indicates the amount od nodes in the tree.
    UpdateFunc update_data; // update label node.

    /**
     * updates the data's in the path to the root.
     * @param node - leaf of the path.
     */
    void update_path_data(Node* node) {
        while(node){
            T lData = nullptr;
            if(node->left) {
                lData = node->left->data;
            }

            T rData = nullptr;
            if(node->left) {
                rData = node->left->data;
            }

            update_data(node->data, lData, rData);
            node=node->parent;
        }
    }

    /**
     * aux function for the d'tor - recursively deletes the nodes of the tree.
     * @param node - root of the sub-tree that need to be deleted.
     */
    void destroy_tree(Node *node) {
        if (node == nullptr) {
            return;
        }
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }

    /**
     * aux function for the insert - find a parent
     *                               for a new node that match the given key.
     * @param node - root of the sub-tree that the new node have space at.
     * @param key - key that match the new node.
     * @return the parent node for the new node.
     */
    Node *find_free_space(Node *node, const S &key) {
        if (node->key == key) {
            return nullptr;
        } else if (node->key > key) {
            if (node->left == nullptr) {
                return node;
            }
            find_free_space(node->left, key);
        } else if (node->key < key) {
            if (node->right == nullptr) {
                return node;
            }
            find_free_space(node->right, key);
        }
    }

    /**
     * aux function for the find - find the node that match the given key.
     * @param node - root of the sun-tree
     *               that should have a offspring that match the given key
     * @param key - key of the wanted node.
     * @return the wanted node, or nullptr if it doesn't exists.
     */
    Node *internal_find(Node *node, const S &key) {
        if (!node) {
            return nullptr;
        }
        if (node->key == key) {
            return node;
        }
        if (node->key > key) {
            return internal_find(node->left, key);
        } else {
            return internal_find(node->right, key);
        }
    }

    /**
     * updates the tree after inserting new node.
     * @param node - the new node that was added to the tree.
     */
    void update_heights_insertion(Node *node) {
        node->height = 0;
        while (node != root) {
            Node *p = node->parent;
            if (p->height >= (node->height + 1)) {
                break;
            }
            p->height = node->height + 1;
            if (abs(p->BF()) > 1) {
                p->roll();
                update_root(p);
                break;
            }
            node = p;
        }
    }

    /**
     * updates the tree after deleting a node.
     * @param node - the parent of the deleted node.
     */
    void balance_fix(Node* node) {
        while (node) {
            int old_height = node->height;
            node->update_height();
            // need to move to the original parent of the node (before the roll)
            Node* parent = node->parent;
            if (abs(node->BF()) == 2) {
                node->roll();
                update_root(node);
            } else if (old_height == node->height) {
                break;
            }
            node = parent;
        }
    }

    /**
     * updates root of the tree by the given node after a roll was activated.
     * @param node - the node that the roll was activated on.
     */
    void update_root(Node* node) {
        if (node->parent->parent == NULL) {
            this->root = node->parent;
        }
    }

    /**
    * aux function for tree_to_array - exporting inorder the tree to array.
    * @param arr - an empty array.
    * @param node - the node that will be added to the array.
    * @param i - index for inserting to the array.
    */
    void tree_to_array_aux(T* arr,Node* node,int& i){
        if (node == nullptr) {
            return;
        }
        tree_to_array_aux(arr,node->left,i);
        arr[i++]=node->data;
        tree_to_array_aux(arr,node->right,i);
    }

public:

    /**
     * tree d'tor - deletes the tree and all of it's nodes.
     */
    virtual ~AVL_Tree() {
        destroy_tree(root);
    }

    /**
     * indicates the amount of nodes in the tree.
     * @return size field of the tree.
     */
    int getSize() const {
        return size;
    }

    /**
     * gets root's data.
     * @return data of the root.
     */
    T getRootData() {
        return this->root->data;
    }

    /**
     * inserts a new node to the tree with the given key and data.
     * @param key - key of the new node.
     * @param data - data of the new node.
     * @param node - pointer for the new node that was added to the tree.
     */
    void insert(const S &key, const T &data) {
        Node* new_node = new Node(key, data);
        if (!root) {
            root = new_node;
        } else {
            Node *parent = find_free_space(root, key);
            new_node->parent = parent;
            if (new_node->is_right_son()) {
                parent->right = new_node;
            } else {
                parent->left = new_node;
            }
        }
        size++;
        update_heights_insertion(new_node);
        update_path_data(new_node);
    }

    /**
     * search for the data of the node that match the given key.
     * @param key - key of the wanted node.
     * @param value - a pointer to a variable which will contain
     *                the data of the wanted node.
     */
    T search(const S &key) {
        Node* wanted_node = find(key);
        if(wanted_node) {
            wanted_node->data;
        }
        return nullptr;
    }

    /**
     * find the node that match the given key.
     * @param key - key of the wanted node.
     * @return
     */
    Node* find(const S &key) {
        Node *found = internal_find(root, key);
        if (!found) {
            return nullptr;
        }
        return found;
    }

    /**
     * removes a node from the tree that match the given key.
     * @param key - key of the node that need to be deleted.
     */
    void remove_by_key(const S &key) {
        Node *node = find(key);
        remove_by_pointer(node);
    }

    /**
     * removes a node from the tree that the given pointer points at.
     * @param p - pointer for the node that need to be deleted.
     */
    void remove_by_pointer(void* p) {
        Node* node = (Node*)p;
        Node* parent;
        if (node->right && node->left) {
            parent = node->next_inorder()->parent;
        } else {
            parent = node->parent;
        }

        root = remove_by_pointer(root, node->key);
        size--;
        balance_fix(parent);
        update_path_data(parent);
    }

    /**
     * deletes the node with the given key from the tree.
     * @param node - the node that one of his offspring is
     *               the node that need to be deleted.
     * @param key - key of the node that need to be deleted.
     * @return  the root of the handled tree.
     */
    Node *remove_by_pointer(Node *node, const S &key) {
        //Step 1- find the wanted node,recursively (and fix the path)
        //stop condition-no node
        if (!node) {
            return node;
        }
        if (key < node->key) {
            node->left = remove_by_pointer(node->left, key);
        } else if (key > node->key) {
            node->right = remove_by_pointer(node->right, key);
        }
            //FOUND IT
        else {
            //Step 2- delete it
            //Case 1- no children/one child
            if (!node->right) {
                Node *temp = node->left;

                if (temp) {
                    temp->parent = node->parent;
                }
                delete node;
                return temp;
            }
            if (!node->left) {
                Node *temp = node->right;

                if (temp) {
                    temp->parent = node->parent;
                }

                temp->parent = node->parent;
                delete node;
                return temp;
            }
            //Case 2- has 2 children
            Node *temp = node->next_inorder();
            node->key = temp->key;
            delete node->data;
            node->data = temp->data;
            temp->data = nullptr;
            node->right = remove_by_pointer(node->right, temp->key);
        }
        return node;
    }

    /**
    * exporting inorder the tree to array.
    * @return array filled with the tree nodes inorder.
    */
    T* tree_to_array(){
        T* arr=new T[(this->size)* sizeof(T)];
        int i=0;
        tree_to_array_aux(arr,root,i);
        return arr;
    }

    /**
    * prints out the tree.
    */
    void print() {
        this->print_in_order(root);
    }

    /**
    * Prints out the tree in an in order method.
    * @param root: starts from given root.
    */
    void print_in_order(Node *node) {

        if (node == nullptr) {
            return;
        }
        print_in_order(node->left);
        node->print_node();
        print_in_order(node->right);
    }


};

#endif //MWET1_AVL_TREE_H
