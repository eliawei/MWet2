//
// Created by elia on 07-Jan-19.
//

#include "library.h"
#include "StaticEye.h"

void *Init(int pixels) {
    if(pixels<=0){
        return NULL;
    }
        try {
        StaticEye *se = new StaticEye(pixels);
        return (void *) se;
    } catch (bad_alloc &ba) {
        return NULL;
    }

}

StatusType AddImage(void *DS, int imageID) {
    if (!DS || imageID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((StaticEye *) DS)->insertImage(imageID);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (hash_already_exists &hae) {
        return FAILURE;
    }
    return SUCCESS;

}

StatusType DeleteImage(void *DS, int imageID) {
    if (!DS || imageID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((StaticEye *) DS)->removeImage(imageID);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (hash_doesnt_exist &hde) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score) {
    if (!DS || imageID <= 0 || pixel < 0 || label <= 0 || score <= 0 ||
        pixel >= (((StaticEye *) DS)->getPixels())) {
        return INVALID_INPUT;
    }
    try {
        ((StaticEye *) DS)->setScore(imageID, pixel, label, score);

    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (hash_doesnt_exist &hde) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label) {
    if (!DS || imageID <= 0 || pixel < 0 || label <= 0 || pixel >= (((StaticEye *) DS)
            ->getPixels())) {
        return INVALID_INPUT;
    }
    try {
        ((StaticEye *) DS)->resetScore(imageID, pixel, label);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (hash_doesnt_exist &hde) {
        return FAILURE;
    } catch (avl_doesnt_exist &ade) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label) {
    if (!DS || !label || imageID <= 0 || pixel < 0 || pixel >= (((StaticEye *) DS)
            ->getPixels())) {
        return INVALID_INPUT;
    }
    try {
        *label = ((StaticEye *) DS)->getMaxLabel(imageID, pixel);
    } catch (bad_alloc &ba) {
        return ALLOCATION_ERROR;
    } catch (hash_doesnt_exist &hde) {
        return FAILURE;
    } catch (not_labeled &nl) {
        return FAILURE;
    }
    return SUCCESS;

}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2) {
    if (!DS || imageID <= 0 || pixel1 < 0 || pixel1 >= (((StaticEye *) DS)
            ->getPixels()) || pixel2 < 0 || pixel2 >= (((StaticEye *) DS)
            ->getPixels())) {
        return INVALID_INPUT;
    }
    try {
        ((StaticEye *) DS)->mergeSuperPixels(imageID, pixel1, pixel2);
    } catch (hash_doesnt_exist &hde) {
        return FAILURE;
    } catch (same_super_pixel& ssp) {
        return FAILURE;
    }
    return SUCCESS;

}

void Quit(void **DS) {
    if(!DS){
        return;
    }
    delete  ((StaticEye *) *DS);
    *DS=NULL;
}

/**
 * ---for testing---
 */
void print(void *DS){
    if(DS){
        ((StaticEye *) DS)->print();
        cout<<endl;
    }
}

