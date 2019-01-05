//
// Created by elia on 31-Dec-18.
//


#ifndef HASH_HASH_H
#define HASH_HASH_H

#include "List.h"
#include "Image.h"
#include <iostream>
using namespace std;

class Hash {

    int table_size=8;
                     //HASH INTS SHOULD I LET IT COMPRESS TO LESS THAN 8?
    int min_size=8;//for making sure table size will always be prime number table won't
                    // compress to size lesser than min_size;
    int num_elements=0;
    List<int,Image*>** table;
    /**
     * ---dynamic array functions---
     */
    /**
     * expands/compresses table according to load factor.
     */
    void resize();
    void expand();
    void compress();

    /**
     * ---general aux functions---
     */
    /**
     * copy elements from this-> table to dst + updates table size
     * @param dst destination table
     * @param new_size new table size
     */
    void copyElements(List<int,Image*>** dst,int new_size);
    /**
     * inserts data to given table
     */
    void insertToTable(List<int,Image*>** table,int key,Image* data,int table_size);

   /**
    * searches for the index of data with specific key in the table, and returns it.
    */
    int getIndex(int key);

    /**
     * ---hash table functions---
     *
     */
     int hashingFunc(int x,int table_s);

public:
    /**
     * initializes new hash table
     */
    explicit Hash();
    /**
     * destructs the hash table
     */
    ~Hash();
    /**
     * inserts to element to table
     * @param key of element
     * @param data of element
     */
    void insert(int key,Image* data);
    /**
     * removes specific element
     * @param key of the element
     */
    void remove(int key);
    /**
     * returns data withe specific key
     */
    Image* search(int key);

    /**
     * testing functions
     */
    void print(){
        int cnt=0;
        for (int i = 0; i <table_size ; ++i) {
            if(table[i]){
                cnt++;
              //  cout<<"list number: "<<i<<endl;
                table[i]->print();
            }else{
                cout<<"--- ";
            }
        }
        cout<<"num of lists:"<<cnt<<endl;
        cout<<"num of elements:"<<num_elements<<endl;

        cout<<endl;
        cout<<"table size is:"<<table_size<<endl;
    }

};



#endif //HASH_HASH_H
