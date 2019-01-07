//
// Created by Gchiko on 28-Nov-18.
//

#ifndef MWET1_LIST_H
#define MWET1_LIST_H

#include <iostream>
#include "exceptions.h"

using namespace std;

template<class K, class D>
class List {
    class Node {
        K key; // the key of the node.
        D data; // the data that the node contains.
        Node *next; // the next node in the list.
        Node *prev; // the previous node in the list.

        /**
         * functions for testing
         */
        void print() {

            cout << key << " ";
        }

        friend class List; // now class List can access private members of Node

    public:
        /**
         * the basic c'tor, constructs a node with given data and key.
         * @param key - the key that the link contains.
         * @param data - the data that the link contains.
         */
        Node(const K &key, const D &data) :
                key(key),
                data(data),
                next(NULL),
                prev(NULL) {};


        /**
         * node d'tor - deletes the given node.
         */
        ~Node()= default;
    };

private:
    int size; // indicates the amount of nodes in the list.
    Node *head; // pointer for the first node in the list.
    Node *iterator= nullptr;
public:

    /**
     * list c'tor' - construct an empty list.
     */
    List() : size(0), head(NULL) {}

    /**
     * list d'tor - deletes the list and all of it's nodes.
     */
    ~List() {
        Node *node = this->head;
        Node *next;
        while (node != NULL) {
            next = node->next;
            delete node;
            this->size--;
            node = next;
        }
    }

    /**
     * indicates the amount of nodes in the list.
     * @return size field of the list.
     */
    int getSize() const {
        return this->size;
    }

    /**
     * inserting a new data with it's key to the start of the list.
     * @param key - key of the new node.
     * @param data - data of the new node.
     * @param node - pointer for the new node that was added to the list.
     */
    void insert(const K &key, const D &data, void **node) {
        Node *new_node = new Node(key, data);

        if (this->size != 0) {
            new_node->next = this->head;
            this->head->prev = new_node;
        }
        this->head = new_node;
        this->size++;
        *node = new_node;
    }

    /**
     * search for the data of the node that match the given key.
     * @param key - key of the wanted node.
     * @param value - a pointer to a variable which will contain
     *                the data of the wanted node.
     */
    void search(const K &key, void **value) {
        Node *wanted_node = this->head;
        while (wanted_node != NULL && wanted_node->key != key) {
            wanted_node = wanted_node->next;
        }
        if (wanted_node == NULL) {
            throw not_found();
        }

        *value = wanted_node->data;
    }

    D dataSearch(const K &key) {
        Node *wanted_node = this->head;
        while (wanted_node != NULL && wanted_node->key != key) {
            wanted_node = wanted_node->next;
        }
        if (wanted_node == NULL) {
            return nullptr;
        } else {
            return wanted_node->data;
        }
    }

    /**
     * removes a node from the list that match the given key.
     * @param key - key of the node that need to be deleted.
     */
    void remove(const K &key) {
        Node *node_to_delete = this->head;
        while (node_to_delete != NULL && node_to_delete->key != key) {
            node_to_delete = node_to_delete->next;
        }
        if (node_to_delete == NULL) {
            throw not_found();
        }

        removeByPointer(node_to_delete);
    }

    /**
     * removes a node from the list that the given pointer points at.
     * @param node_to_delete - pointer for the nodethat need  to be deleted.
     */
    void removeByPointer(void *node_to_delete) {
        Node *node = (Node *) node_to_delete;
        if (node == this->head) {
            this->head = this->head->next;
        }

        if (node->prev != NULL) {
            node->prev->next = node->next;
        }

        if (node->next != NULL) {
            node->next->prev = node->prev;
        }

        delete node->data;//---------added------------
        delete node;
        this->size--;
    }
    /**
       * exporting the list's keys to array.
       * @param keys_arr - an empty array.
       * @return the array filled with the list's keys.
       */
    K* list_to_array_keys(K* keys_arr){

        int i=0;

        for (Node* node=head; node!= nullptr ; node=node->next) {
            keys_arr[i++]=node->data;
        }

        return keys_arr;
    }

    /**
     * test functions
     */
    void print() {
        Node *node = this->head;
        while (node != NULL) {
            node->print();
            node = node->next;
        }
    }

    D GetFirst(){
        iterator=head;
        return iterator->data;
    }
    D GetNext(){
        iterator=iterator->next;
        if(iterator) {
            return iterator->data;
        }else{
            return nullptr;
        }
    }
    void destroy() {
        if (head) {
            Node *node = this->head;
            Node *next;
            while (node != NULL) {
                next = node->next;
                delete node->data;
                this->size--;
                node = next;
            }
        }
    }
};

#endif //MWET1_LIST_H
