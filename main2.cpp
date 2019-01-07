#include <iostream>
#include "Hash.h"
#include "assert.h"
#include "Image.h"
#include "StaticEye.h"

int main() {
    /*
    Hash* hash1=new Hash();
    const int arr_size=200;
    Image* arr[arr_size];
    int index=0;
    try {
        for (int i = 0; i < 200; i++) {
            arr[index]=new Image(i,5);
            hash1->insert(i,arr[index]);
            index++;
            hash1->print();
        }//
        for (int j = 0; j <120; j++) {
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
//uf->testUF();
uf->print();

for (int i = 0; i < 50; ++i) {
    assert(uf->Find(i) == i);
}

for (int j = 0; j < 50; j+=2) {
    assert(uf->Union(j,j+1) == j);
}


assert(uf->getNumOfGroups() == 25);
uf->print();
delete uf;

cout <<"\ngil's tests!!!:\n";
    Image* arr2[100];
    try {
        for (int i = 0; i < 100; ++i) {
            arr2[i] = new Image(i, 6);
        }

        for (int i = 0; i < 100; ++i) {
            arr2[i]->print();
            for (int j = 0; j < 6; ++j) {
                arr2[i]->SetImScore(j, 1, j);
            }
            arr2[i]->print();
        }

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 6; j += 2) {
                arr2[i]->MergeImSuperPixels(j, j + 1);
                arr2[i]->print();
            }
        }


        for (int k = 0; k < 100; ++k) {
            delete arr2[k];
        }
    }
catch(...){
    cout<<"caught";
}*/

    StaticEye *se = new StaticEye(5);
    try {
        for (int i = 0; i < 140; i += 4) {
            cout<<"insert "<<i<<endl;
            se->insertImage(i);
            se->print();
        }

    }
    catch (hash_already_exists &hae) {
        cout << "already exists" << endl;
    }

    for (int i = 0; i < 100; i += 4) {
        try {
            cout << "remove " << i << endl;
            se->removeImage(i);
        }
        catch (hash_doesnt_exist &hde) {
            cout << "doesnt exists" << endl;
        }
        se->print();
     }
    cout<<"Hi";
    se->print();
    delete se;

    return 0;
}
