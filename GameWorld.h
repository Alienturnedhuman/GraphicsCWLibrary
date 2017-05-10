//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_GAMEWORLD_H
#define LIBRARY_GAMEWORLD_H


#include "Entity.h"

class GameWorld
{
private:

    CollisionPipeline collisionPipeline;
    CollisionPipeline movingPipeline;
    RenderPipeline renderLayer[5];
    list<Entity> entities;
public:
    static Rotation angles;
};


#endif //LIBRARY_GAMEWORLD_H
