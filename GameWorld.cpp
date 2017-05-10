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

inline Point* CollisionModel::getRectPoints() const
{
    Point* rv[4];

    Point p = getGlobalPos();

    Point tb;
    tb.x = GameWorld::angles.sin(p.r) * box_bottom;
    tb.y = GameWorld::angles.cos(p.r) * box_bottom;

    Point tt;
    tt.x = GameWorld::angles.sin(p.r) * box_top;
    tt.y = GameWorld::angles.cos(p.r) * box_top;

    Point tl;
    tl.x = GameWorld::angles.cos(p.r) * box_left;
    tl.y = -GameWorld::angles.sin(p.r) * box_left;

    Point tr;
    tr.x = GameWorld::angles.cos(p.r) * box_right;
    tr.y = -GameWorld::angles.sin(p.r) * box_right;

    rv[0]->x = p.x + tb.x + tl.x;
    rv[0]->y = p.y + tb.y + tl.y;
    rv[1]->x = p.x + tb.x + tr.x;
    rv[1]->y = p.y + tb.y + tr.y;
    rv[2]->x = p.x + tt.x + tr.x;
    rv[2]->y = p.y + tt.y + tr.y;
    rv[3]->x = p.x + tt.x + tl.x;
    rv[3]->y = p.y + tt.y + tl.y;

    free(&p);
    return *rv;
}
inline Point* RenderModel::getRectPoints() const
{
    Point* rv[4];

    Point p = getGlobalPos();

    Point tb;
    tb.x = GameWorld::angles.sin(p.r) * box_bottom;
    tb.y = GameWorld::angles.cos(p.r) * box_bottom;

    Point tt;
    tt.x = GameWorld::angles.sin(p.r) * box_top;
    tt.y = GameWorld::angles.cos(p.r) * box_top;

    Point tl;
    tl.x = GameWorld::angles.cos(p.r) * box_left;
    tl.y = -GameWorld::angles.sin(p.r) * box_left;

    Point tr;
    tr.x = GameWorld::angles.cos(p.r) * box_right;
    tr.y = -GameWorld::angles.sin(p.r) * box_right;

    rv[0]->x = p.x + tb.x + tl.x;
    rv[0]->y = p.y + tb.y + tl.y;
    rv[1]->x = p.x + tb.x + tr.x;
    rv[1]->y = p.y + tb.y + tr.y;
    rv[2]->x = p.x + tt.x + tr.x;
    rv[2]->y = p.y + tt.y + tr.y;
    rv[3]->x = p.x + tt.x + tl.x;
    rv[3]->y = p.y + tt.y + tl.y;

    free(&p);
    return *rv;
}