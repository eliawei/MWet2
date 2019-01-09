//
// Created by elia on 05-Dec-18.
//

#include "Image.h"
#include "exceptions.h"

Image::Image(int imageId, int pixels) : id(imageId),
                                        super_pixels(new UnionFind(pixels)) {}

Image::~Image() {
    delete this->super_pixels;
}

int Image::get_id() {
    return this->id;
}

void Image::SetImScore(int pixel, int label, int score) {
    AVL_Tree<int, shared_ptr<Label>, UpdateLabel>* tree = super_pixels->FindData(pixel);
    shared_ptr<Label> wanted_label= nullptr;
    if(tree) {
      wanted_label = tree->search(label);
    }
    if (!wanted_label&&tree) {
        shared_ptr<Label>new_label( new Label(label, score));
        tree->insert(label, new_label);
    } else if(tree){
        wanted_label->setScore(score);
    }
}

void Image::RemoveImLabel(int pixel, int label) {
    AVL_Tree<int, shared_ptr<Label>, UpdateLabel> *tree = super_pixels->FindData(pixel);
    if (tree && tree->search(label) == nullptr) {
        throw avl_doesnt_exist();
    }
    if (tree) {
        tree->remove_by_key(label);
    }
}

int Image::GetImMaxLabel(int pixel) {
    AVL_Tree<int, shared_ptr<Label>, UpdateLabel> *tree = super_pixels->FindData(pixel);
    shared_ptr<Label> root_label= nullptr;
    if(tree) {
        root_label = tree->getRootData();
    }
    if (!root_label) {
        throw not_labeled();
    }
    return root_label->getMax_label();
}

void Image::MergeImSuperPixels(int pixel1, int pixel2) {
    int super_pixel1 = this->super_pixels->Find(pixel1);
    int super_pixel2 = this->super_pixels->Find(pixel2);
    if (super_pixel1 == super_pixel2) {
        throw same_super_pixel();
    }
    this->super_pixels->Union(super_pixel1, super_pixel2);
}