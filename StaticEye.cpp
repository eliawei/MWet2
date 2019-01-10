//
// Created by Gchiko on 04-Jan-19.
//

#include "StaticEye.h"

StaticEye::StaticEye(int pixels) : pixels(pixels) ,images(new Hash()){}

StaticEye::~StaticEye() {
    delete images;
}

void StaticEye::insertImage(int image_id) {
    if (images->search(image_id) != nullptr) {
        throw hash_already_exists();
    }
    Image *im = new Image(image_id, pixels);
    images->insert(image_id, im);

}

void StaticEye::removeImage(int image_id) {
    images->remove(image_id);
}

void StaticEye::setScore(int image_id, int pixel, int label, int score) {
    Image* im=images->search(image_id);
    if(!im){
        throw hash_doesnt_exist();
    }
    im->SetImScore(pixel,label,score);
}

void StaticEye::resetScore(int image_id, int pixel, int label) {
    Image* im=images->search(image_id);
    if(!im){
        throw hash_doesnt_exist();
    }
    im->RemoveImLabel(pixel,label);
}

int StaticEye::getMaxLabel(int image_id, int pixel) {
    Image* im=images->search(image_id);
    if(!im){
        throw hash_doesnt_exist();
    }
    return im->GetImMaxLabel(pixel);
}

void StaticEye::mergeSuperPixels(int image_id, int pixel1, int pixel2) {
    Image* im=images->search(image_id);
    if(!im){
        throw hash_doesnt_exist();
    }
    im->MergeImSuperPixels(pixel1,pixel2);
}


int StaticEye::getPixels() const {
    return pixels;
}


