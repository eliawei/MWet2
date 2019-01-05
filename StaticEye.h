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
    StaticEye(int pixels): pixels(pixels), images(new Hash()){}




};


#endif //HASH_STATICEYE_H
