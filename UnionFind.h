//
// Created by Gchiko on 02-Jan-19.
//

#ifndef UNIONFIND_UNIONFIND_H
#define UNIONFIND_UNIONFIND_H

#include "stdlib.h"
#include "AVL_Tree.h"
#include "Label.h"

class UpdateLabel {

    Label *maxLabel(Label *l1, Label *l2) {
        if (l1 && l2) {
            if (l1->getScore() > l2->getScore()) {
                return l1;
            } else if (l2->getScore() > l1->getScore()) {
                return l2;
            } else if (l1->getLabel_id() > l2->getLabel_id()) {
                return l1;
            } else {
                return l2;
            }
        }
        if (l1) {
            return l1;
        }
        if (l2) {
            return l2;
        }
    }
public:
    /**
    * updates label by it's sons.
    * @param label - data od the node.
    * @param r - data of right son.
    * @param l - data of left son.
    */
    void operator()(Label *label, Label *r, Label *l) {

        Label *max = maxLabel(maxLabel(label, r), l);
        label->setMax_label(max->getLabel_id());
        label->setMax_score(max->getScore());
        /*
        int max_score = label->getScore();
        int max_label = label->getLabel_id();

        if(l && l->getScore() > max_score) {
            max_score = l->getScore();
            max_label = l->getLabel_id();
        }

        if(r && r->getScore() >= max_score) {
            max_score = r->getScore();
            max_label = r->getLabel_id();
        }

        label->setMax_label(max_label);
        label->setMax_score(max_score);
         */
    }
};

class UnionFind {
    int num_of_groups;
    int num_of_pixels;
    int *size;
    int *parent;
    AVL_Tree<int, Label *, UpdateLabel> **labels;

    Label **mergeArrays(Label **arr_a, Label **arr_b, int size_a, int size_b,int* new_size) {

        Label **merged_arr = new Label *[size_a + size_b];
        for (int i = 0; i < size_a + size_b; ++i) {
            merged_arr[i] = nullptr;
        }
        int i_a = 0;
        int i_b = 0;
        int i_merged = 0;

        while (i_a < size_a && i_b < size_b) {
            if (arr_a[i_a]->getLabel_id() < arr_b[i_b]->getLabel_id()) {
                merged_arr[i_merged++] = arr_a[i_a++];
                (*new_size)++;
            } else if (arr_a[i_a]->getLabel_id() > arr_b[i_b]->getLabel_id()) {
                merged_arr[i_merged++] = arr_b[i_b++];
                (*new_size)++;
            } else if (arr_a[i_a]->getLabel_id() == arr_b[i_b]->getLabel_id()) {
                int new_score = arr_a[i_a]->getScore() + arr_b[i_b]->getScore();
                arr_a[i_a]->setScore(new_score);
                merged_arr[i_merged++] = arr_a[i_a];
                i_a++;
                i_b++;
                (*new_size)++;
            }
        }
        while (i_a < size_a) {
            merged_arr[i_merged++] = arr_a[i_a++];
            (*new_size)++;
        }
        while (i_b < size_b) {
            merged_arr[i_merged++] = arr_b[i_b++];
            (*new_size)++;
        }
        return merged_arr;
    }

    AVL_Tree<int, Label *, UpdateLabel> *insertToTree(Label **arr, int size) {
        AVL_Tree<int, Label *, UpdateLabel> *merged_tree = new AVL_Tree<int, Label *,
                UpdateLabel>();
        int *keys = new int[size];
        for (int i = 0; i < size; ++i) {
            keys[i] = arr[i]->getLabel_id();
        }
        merged_tree->sorted_arr_to_tree(keys, arr, size);
        delete []keys;
        return merged_tree;

    }


    AVL_Tree<int, Label *, UpdateLabel> *MergeTree(AVL_Tree<int, Label *, UpdateLabel> *a,
                                                   AVL_Tree<int, Label *, UpdateLabel> *b) {


        int size_a = a->getSize();
        if(size_a<0){
            size_a=0;
        }
        int size_b = b->getSize();
        if(size_b<0){
            size_b=0;
        }

        Label **arr_a = nullptr;
        Label **arr_b = nullptr;
        Label **merged_arr = nullptr;
        AVL_Tree<int, Label *, UpdateLabel> *merged = nullptr;
        if (size_a > 0) {
            arr_a = a->tree_to_array();
        }
        if (size_b > 0) {
            arr_b = b->tree_to_array();
        }

        if (size_a > 0 || size_b > 0) {
            int new_size=0;
            merged_arr = mergeArrays(arr_a, arr_b, size_a, size_b,&new_size);
            merged = insertToTree(merged_arr, new_size);

        }

        delete a;
        delete b;

        delete[] arr_a;
        delete[] arr_b;
        delete[] merged_arr;
        return merged;


    }

public:



    /**
     * initialize UnionFind class based on arrays with default values.
     * @param range - amount of pixels in each image.
     */
    UnionFind(int range) {
        num_of_groups = range;
        num_of_pixels = range;
        size = new int[range];
        parent = new int[range];
        labels = new AVL_Tree<int, Label *, UpdateLabel> *[range];

        for (int i = 0; i < range; ++i) {
            size[i] = 1; // making singletones - size is 1.
        }

        for (int i = 0; i < range; ++i) {
            parent[i] = -1; // making singletones - no parent.
        }

        for (int i = 0; i < range; ++i) {
            labels[i] = new AVL_Tree<int, Label *, UpdateLabel>(); // data is unknown yet.
        }
    }

    /**
     * union find d'tor - deletes the structure and all of it's fields.
     */
    virtual ~UnionFind() {
        delete[] this->size;
        delete[] this->parent;

        for (int i = 0; i < num_of_pixels; ++i) {
            delete this->labels[i];
        }

        delete[] this->labels;
    }

    /**
     * finding the root of the group that i is include in.
     * @param i - element that we want his root.
     * @return root of the group that i is include in.
     */
    int Find(int i) {
        int root = i;
        while (parent[root] != -1) {
            root = parent[root];
        }

        // shrinking paths
        int current = i;
        int temp;
        while (parent[current] != -1) {
            temp = parent[current];
            parent[current] = root;
            current = temp;
        }

        return root;
    }

    /**
     * finding the root's data of the group that i is include in.
     * @param i - element that we want his root's data
     * @return root's data.
     */
    AVL_Tree<int, Label *, UpdateLabel> *FindData(int i) {
        int dataId = this->Find(i);

        return this->labels[dataId];
    }

    /**
     * unite two groups to one group.
     * @param p - root of the first groups to unite.
     * @param q - root of the second groups to unite.
     * @return new root of the united groups.
     */
    int Union(int p, int q) {
        if (size[p] >= size[q]) {
            parent[q] = p;
            size[p] += size[q];
            size[q] = 0;
            labels[p] = MergeTree(labels[p], labels[q]);
            labels[q] = nullptr;
            num_of_groups--;

            return p;
        } else {
            parent[p] = q;
            size[q] += size[p];
            size[p] = 0;
            labels[q] = MergeTree(labels[q], labels[p]);
            labels[p] = nullptr;
            num_of_groups--;

            return q;
        }
    }

    int getNumOfGroups() {
        return this->num_of_groups;
    }

    void print() {
        cout << "num of groups: " << this->num_of_groups << endl;
        for (int i = 0; i < this->num_of_groups; ++i) {
            cout << "pixel num: " << i << " size is: " << size[i] << " parent is: " <<
                 parent[i] << " tree is: " << endl;
            if (labels[i]) {
                labels[i]->print();
            } else {
                cout << "doesnt exist" << endl;
            }
            cout << endl;
        }
    }
};


#endif //UNIONFIND_UNIONFIND_H
