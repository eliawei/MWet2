#include <iostream>
#include "Hash.h"
#include "assert.h"
#include "Image.h"

int main() {
    Hash* hash1=new Hash();
    const int arr_size=225;
    Image* arr[arr_size];
    int index=0;
    try {
        for (int i = 0; i < 897; i+=4) {
            arr[index]=new Image(i,5);
            hash1->insert(i,arr[index]);
            index++;
            hash1->print();
        }//
        for (int j = 0; j <120; j+=2) {
            try {
                cout << hash1->search(j)->get_id() << "was searched!" << endl;
            }catch(...) {
                cout<<j<<"not found";
            }
        }

        for (int k = 0; k <arr_size; ++k) {
                delete arr[k];
        }

    }


catch (exception& e){
        cout<<"kfiloot";
    }

delete hash1;


UnionFind* uf = new UnionFind(50);

for (int i = 0; i < 50; ++i) {
    assert(uf->Find(i) == i);
}

for (int j = 0; j < 50; j+=2) {
    assert(uf->Union(j,j+1) == j);
}


assert(uf->getNumOfGroups() == 25);

delete uf;

cout <<"\ngil's tests!!!:\n";
    Image* arr2[100];
    try {
        for (int i = 0; i < 100; ++i) {
            arr2[i]=new Image(i,6);
        }

        for (int i = 0; i < 100; ++i) {
            arr2[i]->print();
            for (int j = 0; j < 6; ++j) {
                arr2[i]->SetImScore(j, 1, j);
            }
            arr2[i]->print();
        }

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 6; j+=2) {
                arr2[i]->MergeImSuperPixels(j, j+1);
                arr2[i]->print();
            }
        }


        for (int k = 0; k < 100; ++k) {
            delete arr2[k];
        }

    }


    catch (exception& e){
        cout<<"gil failed";
    }

return 0;
}