//
// Created by elia on 31-Dec-18.
//

#include "Hash.h"


Hash::Hash() : table(new List<int, Image *> *[table_size]) {

    for (int i = 0; i < table_size; ++i) {
        table[i] = nullptr;//initial will always be for small size table =7, so it wont be o(m)
        // because 7 is const so it be o(1)??????
    }

}

Hash::~Hash() {
    //needs to delete every object?
    for (int i = 0; i < table_size; ++i) {
        if(table[i]) {
            table[i]->destroy();
        }
        delete table[i];
        table[i]= nullptr;
    }
    delete[] table;
}

void Hash::insert(int key, Image *data) {
    insertToTable(table, key, data, table_size);
    num_elements++;
    resize();
}

void Hash::remove(int key) {
    int index = getIndex(key);//hash int
    table[index]->remove(key);
    if (table[index]->getSize() == 0) {
        delete table[index];
        table[index] = nullptr;
    }
    num_elements--;
    resize();
}

Image *Hash::search(int key) {
    int index;
    try {
        index= getIndex(key);
    }catch(hash_doesnt_exist& hde){
        return nullptr;
    }
    Image *data = table[index]->dataSearch(key);
    return data;
}

int Hash::getIndex(int key) {
    int location;

    location = hashingFunc(key, table_size);
    Image *data = nullptr;    //=-1;//int hash

    if (table[location]) {
        data = table[location]->dataSearch(key);
    }
    if (data != nullptr) {
        return location;
    }
    throw hash_doesnt_exist();
}

/**
 * ---hash table functions---
*/
void Hash::insertToTable(List<int, Image *> **table_t, int key, Image* data, int table_s) {
    int location = 0;

    location = hashingFunc(key, table_s);

    //check no duplication
    if (table_t[location]) {
        if (table_t[location]->dataSearch(key)) {
            throw hash_already_exists();
        }
    }

    void *node;
    if (table_t[location] == nullptr) {
        table_t[location] = new List<int, Image*>();
    }
    table_t[location]->insert(key, data, &node);
}

int Hash::hashingFunc(int x, int table_s) {
    return (x % table_s);
}

/**
 * ---dynamic array functions---
 */

void Hash::resize() {
    if (num_elements == table_size) {
        expand();
    } else if (table_size > min_size &&
               num_elements == ((int) (0.25 * table_size))) {
        compress();
    }
}

void Hash::expand() {
    //assign and initialize new array
    int new_size = table_size * 2;
    List<int, Image*> **new_t = new List<int, Image*> *[new_size]();
    for (int i = 0; i < new_size; ++i) {
        new_t[i] = nullptr;
    }

    copyElements(new_t, new_size);
    table_size = new_size;
    table = new_t;
}

void Hash::compress() {
    //assign and initialize new array
    int new_size = table_size / 2;
    List<int, Image*> **new_t = new List<int, Image*> *[new_size]();
    for (int i = 0; i < new_size; ++i) {
        new_t[i] = nullptr;
    }
    copyElements(new_t, new_size);

    table_size = new_size;
    table = new_t;
}

void Hash::copyElements(List<int, Image*> **dst, int new_size) {
    for (int i = 0; i < table_size; ++i) {
        if (table[i]) {

            for (Image* iter = table[i]->GetFirst(); iter != nullptr; iter = table[i]->GetNext()) {
                insertToTable(dst, iter->get_id(), iter, new_size);
            }
            //delete old lists from table
            delete table[i];
            table[i]= nullptr;
        }
    }
    delete [] table;
}



