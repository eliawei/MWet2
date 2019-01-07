//
// Created by Gchiko on 04-Jan-19.
//

#ifndef HASH_STATICEYE_H
#define HASH_STATICEYE_H
#include "Hash.h"

class StaticEye {
    int pixels;
    Hash* images;

public:
    StaticEye(int pixels);

    virtual ~StaticEye();

    void insertImage(int image_id);

    void removeImage(int image_id);

    void setScore(int image_id, int pixel,int label,int score);

    void resetScore(int image_id, int pixel,int label);

    int getMaxLabel(int image_id,int pixel);

    void mergeSuperPixels(int image_id,int pixel1,int pixel2);

    int getPixels() const;

    /**
     * -----testing functions-----
     */
    void print();
};


#endif //HASH_STATICEYE_H
