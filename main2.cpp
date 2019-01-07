#include <iostream>

#include "library.h"
using namespace std;
int main() {
    auto ds=Init(5);
    int label=0;
    print(ds);
    AddImage(ds, 3);
    print(ds);
    SetLabelScore(ds, 3, 1, 1, 10);
    print(ds);
    SetLabelScore(ds, 3, 2, 2, 5);
    print(ds);
    GetHighestScoredLabel(ds, 3, 1, &label);
    cout<<"highest label of pixel 1 is "<<label<<endl;
    print(ds);
    GetHighestScoredLabel(ds, 3, 2, &label);
    cout<<"highest label of pixel 2 is "<<label<<endl;
    print(ds);

    MergeSuperPixels(ds, 3, 1, 2);
    cout<<"1 and 2 merged"<<endl;
    GetHighestScoredLabel(ds, 3, 1, &label);
    cout<<"highest label of pixel 1 is "<<label<<endl;
    print(ds);
    GetHighestScoredLabel(ds, 3, 2, &label);
    cout<<"highest label of pixel 2 is "<<label<<endl;
    print(ds);
    ResetLabelScore(ds, 3, 1, 1);
    return 0;
}
