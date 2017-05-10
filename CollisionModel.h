//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_COLLISIONMODEL_H
#define LIBRARY_COLLISIONMODEL_H

#include <cstdlib>
#include <list>
#include "Point.h"

class PhysicalModel;

using namespace std;

class CollisionModel {
public:
    static enum Shape{BOX,CIRCLE};
private:
    double origin_x,origin_y,box_bottom,box_top,box_left,box_right,circle_radius=0;
    int angle = 0;
    Shape model;
    PhysicalModel* parentElement;
public:
    inline Shape getModel() const;
    inline Point getGlobalPos() const;
    inline Point* getRectPoints() const;
    inline PhysicalModel* getParentElement() const;

    double getRadius() const
    {
        return circle_radius;
    }

    static inline bool pointInRectangle(Point co, Point a , Point b , Point c , Point d) const;
    static inline bool intersectsCircle(Point co, double cr, Point a , Point b) const;

    inline bool collidesCC(const CollisionModel &cm) const;
    inline bool collidesCB(const CollisionModel &cm) const;
    inline bool collidesBB(const CollisionModel &cm) const;
    inline bool collidesBC(const CollisionModel &cm) const;

    /**
     * Constructor for a circle
     * @param ox
     * @param oy
     * @param cr
     * @param p
     */
    CollisionModel(int ox, int oy, int cr, PhysicalModel* p)
    {
        model = CIRCLE;
        parentElement = p;
        origin_x = ox;
        origin_y = oy;
        circle_radius = cr;
    }

    /**
     * Constructor for a box
     * @param ox
     * @param oy
     * @param bt
     * @param bb
     * @param bl
     * @param br
     * @param p
     */
    CollisionModel(int ox, int oy, int oa, int bt, int bb, int bl, int br, PhysicalModel* p)
    {
        model = BOX;
        parentElement = p;
        origin_x = ox;
        origin_y = oy;
        angle = oa;
        box_top = bt;
        box_bottom = bb;
        box_left = bl;
        box_right = br;
    }
};

/**
 * Overriding equality operator to mean two objects collide or not
 * @param a
 * @param b
 * @return
 */
inline bool operator==(const CollisionModel &a, const CollisionModel &b)
{
    if(a.getModel()==CollisionModel::Shape::CIRCLE)
    {
        if(b.getModel()==CollisionModel::Shape::CIRCLE)
        {
            return a.collidesCC(b);
        }
        else if(b.getModel()==CollisionModel::Shape::BOX)
        {
            return a.collidesCB(b);
        }
    }
    else if(a.getModel()==CollisionModel::Shape::BOX)
    {
        if(b.getModel()==CollisionModel::Shape::CIRCLE)
        {
            return b.collidesCB(a);
        }
        else if(b.getModel()==CollisionModel::Shape::BOX)
        {
            return a.collidesBB(b);
        }
    }
    // Note - should never get here, but if it does, fail to no collision
    return false;
}

/**
 * Overriding inequality operator to mean two objects don't collide
 * @param a
 * @param b
 * @return
 */
inline bool operator!=(const CollisionModel &a, const CollisionModel &b)
{
    // invert equality operator
    return !(a == b);
}



class CollisionPipeline
{
private:
    list<CollisionModel*> pipeline;
    int size=0;
public:
    inline void addModel(CollisionModel* model);
    inline CollisionModel* retrieveModel();
};

inline CollisionModel& operator>>(CollisionModel& cm , CollisionPipeline& cp)
{
    cp.addModel(&cm);
}
inline CollisionModel& operator<<(CollisionModel& cm , CollisionPipeline& cp)
{
    return *cp.retrieveModel();
}

#endif //LIBRARY_COLLISIONMODEL_H
