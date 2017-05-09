//
// Created by Ben Dickson on 5/9/17.
//

#include "GameWorld.h"

inline Point PhysicalModel::getGlobalPos() const
{
    Point rv;
    Point p = parentElement->getGlobalPos();
    rv.x = p.x + GameWorld::angles.cos(p.r) * x + GameWorld::angles.sin(p.r) * y;
    rv.y = p.y - GameWorld::angles.sin(p.r) * x + GameWorld::angles.cos(p.r) * y;
    rv.r = p.r + r;

    free(&p);

    return rv;
}
inline Point RenderModel::getGlobalPos() const
{
    Point rv;
    Point p = parentElement->getGlobalPos();
    rv.x = p.x + GameWorld::angles.cos(p.r) * origin_x + GameWorld::angles.sin(p.r) * origin_y;
    rv.y = p.y - GameWorld::angles.sin(p.r) * origin_x + GameWorld::angles.cos(p.r) * origin_y;
    rv.r = p.r + angle;

    free(&p);

    return rv;
}
inline Point CollisionModel::getGlobalPos() const
{
    Point rv;
    Point p = parentElement->getGlobalPos();
    rv.x = p.x + GameWorld::angles.cos(p.r) * origin_x + GameWorld::angles.sin(p.r) * origin_y;
    rv.y = p.y - GameWorld::angles.sin(p.r) * origin_x + GameWorld::angles.cos(p.r) * origin_y;
    rv.r = p.r + angle;

    free(&p);

    return rv;
}