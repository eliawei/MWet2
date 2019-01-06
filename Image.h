//
// Created by elia on 05-Dec-18.
//

#ifndef TAGGER_IMAGE_H
#define TAGGER_IMAGE_H

#include <ostream>
#include "UnionFind.h"


class Image {
private:
    int id; // image id number
    UnionFind* super_pixels;

public:
    /**
     * Image c'tor - construct a new Image with given parameters.
     * @param id - the image id number.
     * @param pixels - amount of pixels.
     */
    Image(int id, int pixels);

    /**
     * Image d'tor - deletes the given Image.
     */
    ~Image();

    /**
     * getter of the image id number.
     * @return id field.
     */
    int get_id();

    /**
     * tagging the pixel's super pixel with the given label and score.
     * @param pixel - pixel that we want to tag his super pixel.
     * @param label - label for tagging.
     * @param score - score of the label for tagging.
     */
    void SetImScore(int pixel, int label, int score);

    /**
     * removing the label from the pixel's super pixel.
     * @param pixel - pixel that we want to un-tag his super pixel.
     * @param label - label to un-tag.
     */
    void RemoveImLabel(int pixel, int label);

    /**
     * getting the label-id with the highest score at the pixel's super pixel.
     * @param pixel - pixel that we want to find the highest score in his group.
     * @return - label number that has the maximum score.
     */
    int GetImMaxLabel(int pixel);

    /**
     * merging two super pixels.
     * @param pixel1 - pixel included in the first wanted super pixel.
     * @param pixel2 - pixel included in the second wanted super pixel.
     */
    void MergeImSuperPixels(int pixel1, int pixel2);

    void print() {
        cout << "\nthe id is: " << this->id << " the UF is:\n";
        this->super_pixels->print();
        cout << "\n";
    }
};


#endif //TAGGER_IMAGE_H
