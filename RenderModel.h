//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_RENDERMODEL_H
#define LIBRARY_RENDERMODEL_H


#include "Color.h"
#include "Texture.h"

class RenderModel {
private:
    unsigned int width;
    unsigned int height;
    Color color;
    Texture texture;
    bool textured;
public:

    RenderModel();
};


#endif //LIBRARY_RENDERMODEL_H
