//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_COLLISIONMODEL_H
#define LIBRARY_COLLISIONMODEL_H

class PhysicalModel;

class CollisionModel {
public:
    static enum Shape{BOX,CIRCLE};
private:
    double origin_x,origin_y,box_bottom,box_top,box_left,box_right,circle_radius;
    Shape model;
    PhysicalModel parent;
public:
    Shape getModel() const;

    /**
     * Constructor for a circle
     * @param ox
     * @param oy
     * @param cr
     * @param p
     */
    CollisionModel(int ox, int oy, int cr, PhysicalModel p)
    {
        model = CIRCLE;
        parent = p;
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
    CollisionModel(int ox, int oy, int bt, int bb, int bl, int br, PhysicalModel p)
    {
        model = BOX;
        parent = p;
        origin_x = ox;
        origin_y = oy;
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
            // put code for circle/circle collision here
        }
        else if(b.getModel()==CollisionModel::Shape::BOX)
        {
            // put code for circle/circle collision here
        }
    }
    else if(a.getModel()==CollisionModel::Shape::BOX)
    {
        if(b.getModel()==CollisionModel::Shape::CIRCLE)
        {

        }
        else if(b.getModel()==CollisionModel::Shape::BOX)
        {

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


#endif //LIBRARY_COLLISIONMODEL_H
