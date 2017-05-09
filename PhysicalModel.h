//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_PHYSICALMODEL_H
#define LIBRARY_PHYSICALMODEL_H


#include "RenderModel.h"
#include "CollisionModel.h"

class PhysicalModel {
private:
    double x,y,r;
    bool collides,rendered;
    RenderModel render;
    CollisionModel collider;

};


#endif //LIBRARY_PHYSICALMODEL_H
