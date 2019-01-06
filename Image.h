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
    UnionFind super_pixels;

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
     * setter of the segment's label.
     * @param seg_id - the segment to be labeled..
     * @param label - the label number.
     */
    void add_label(int seg_id,int label);

    /**
     * getter of the segment's label.
     * @param seg_id - the segment number.
     * @return the segment's label number.
     */
    int get_label(int seg_id);

    /**
     * remove the segment's label.
     * @param seg_id - the segment number.
     */
    void delete_label(int seg_id);

    /**
     * exporting all the unlabeled segments og the image to an array.
     * @param numOfSegments - pointer for a variable that will
     *                        contain the amount of the unlabeled segments.
     * @return an array filled with the unlabeled segments numbers.
     */
    int* get_all_unlabled_segments(int* numOfSegments);

    /**
     * exporting all the segments that are labeled with the given label.
     * @param label - the wanted label.
     * @return an array filled with the labeled segments numbers.
     */
    int* get_all_segments_by_label(int label);

    /**
     * counting the amount of segments that are labeled with the given label.
     * @param label - the wanted label.
     * @return the amount of the wanted segments.
     */
    int get_num_of_segments_by_label(int label);

};


#endif //TAGGER_IMAGE_H
