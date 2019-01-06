//
// Created by Gchiko on 02-Jan-19.
//

#ifndef UNIONFIND_UNIONFIND_H
#define UNIONFIND_UNIONFIND_H

#include "stdlib.h"
#include "AVL_Tree.h"
#include "Label.h"

class UpdateLabel {
public:
    /**
    * updates label by it's sons.
    * @param label - data od the node.
    * @param r - data of right son.
    * @param l - data of left son.
    */
    void operator()(Label* label, Label* r, Label* l) {
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
    }
};

class UnionFind {
    int num_of_groups;
    int num_of_pixels;
    int* size;
    int* parent;
    AVL_Tree<int, Label*, UpdateLabel>** labels;


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
        labels = new AVL_Tree<int, Label*, UpdateLabel>*[range];

        for(int i = 0; i < range ; ++i) {
            size[i] = 1; // making singletones - size is 1.
        }

        for(int i = 0; i < range ; ++i) {
            parent[i] = -1; // making singletones - no parent.
        }

        for(int i = 0; i < range ; ++i) {
            labels[i] = new AVL_Tree<int, Label*, UpdateLabel>() ; // data is unknown yet.
        }
    }

    /**
     * union find d'tor - deletes the structure and all of it's fields.
     */
    virtual ~UnionFind() {
        delete[] this->size;
        delete[] this->parent;

        for(int i = 0; i < num_of_pixels; ++i) {
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
        while(parent[root] != -1) {
            root = parent[root];
        }

        // shrinking paths
        int current = i;
        int temp;
        while(parent[current] != -1) {
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
    AVL_Tree<int, Label*, UpdateLabel>* FindData(int i) {
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
        if(size[p] >= size[q]) {
            parent[q] = p;
            size[p] += size[q];
            size[q] = 0;
            //labels[p] = MergeTree(data[p], data[q]);
            labels[q] = nullptr;
            num_of_groups--;

            return p;
        } else {
            parent[p] = q;
            size[q] += size[p];
            size[p] = 0;
            //labels[q] = MergeTree(data[q], data[p]);
            labels[p] = nullptr;
            num_of_groups--;

            return q;
        }
    }

    int getNumOfGroups() {
        return this->num_of_groups;
    }

    void print() {
        cout << "num of groups: " << this->num_of_groups << "\n";
        for (int i = 0; i < this->num_of_groups; ++i) {
            cout << "pixel num: " << i << " size is: " << size[i] << " parent is: " << parent[i] << " tree is: ";
            labels[i]->print();
            cout << "\n";
        }
    }
};


#endif //UNIONFIND_UNIONFIND_H
