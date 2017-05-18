//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_COLLISIONMODEL_H
#define LIBRARY_COLLISIONMODEL_H

#include <cstdlib>
#include <list>
#include <map>
#include "Point.h"

class PhysicalModel;

using namespace std;

class CollisionModel
{
public:
    enum Shape{BOX,CIRCLE};
private:
    double origin_x = 0.0f,origin_y = 0.0f,box_bottom=-1.0f,box_top=1.0f,box_left=-1.0f,box_right=1.0f,circle_radius=1.0f;
    int angle = 0;
    Shape model;
    PhysicalModel* parentElement;

    enum ConType{INT,DOUBLE,STRING,ENUM};
    static map<string,ConType> conImport = {{"origin_x",DOUBLE},{"origin_y",DOUBLE},{"box_top",DOUBLE},{"box_bottom",DOUBLE},
                                            {"box_left",DOUBLE},{"box_right",DOUBLE},{"circle_radius",DOUBLE}};

    // import values
    bool importDouble(string var , double value);
    bool importInt(string var, int value);
    bool importString(string var, string value);
public:
    inline Shape getModel() const;
    inline Point getGlobalPos() const;
    inline Point* getRectPoints() const;
    inline PhysicalModel* getParentElement() const;

    double getRadius() const
    {
        return circle_radius;
    }

    static inline bool pointInRectangle(Point co, Point a , Point b , Point c , Point d)
    {
        return false;
    };
    static inline bool intersectsCircle(Point co, double cr, Point la , Point lb)
    {
        return false;
    };
    static inline bool intersectsRectangle(Point ra , Point rb , Point rc , Point rd, Point la, Point lb)
    {
        return false;
    };

    inline bool collidesCC(const CollisionModel &cm) const;
    inline bool collidesCB(const CollisionModel &cm) const;
    inline bool collidesBB(const CollisionModel &cm) const;


    inline bool parseConstructorPair(pair<string,string> p)
    {
        map<string,ConType>::iterator it = conImport.find(p.first);
        if(it!=conImport.end())
        {
            switch((*it).second)
            {
                case DOUBLE:
                    return importDouble(p.first,stod(p.second));
                case INT:
                    return importInt(p.first,stoi(p.second));
                case STRING:
                    return importString(p.first,p.second);
            }
        }
        return false;
    }

    CollisionModel(Shape s, PhysicalModel* p)
    {
        model = s;
        parentElement = p;
    }
    /**
     * Constructor for a circle
     * @param ox
     * @param oy
     * @param cr
     * @param p
     */
    CollisionModel(double ox, double oy, double cr, PhysicalModel* p)
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
    CollisionModel(double ox, double oy, double oa, double bt, double bb, double bl, double br, PhysicalModel* p)
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
    list<CollisionModel*>::iterator it;
public:
    inline void addModel(CollisionModel* model);
    inline CollisionModel* nextModel();
    inline CollisionModel* popModel();
    inline void resetIterator()
    {
        it = pipeline.begin();
    }
};

inline CollisionModel& operator>>(CollisionModel& cm , CollisionPipeline& cp)
{
    cp.addModel(&cm);
}
inline CollisionModel& operator<<(CollisionModel& cm , CollisionPipeline& cp)
{
    return *cp.nextModel();
}

#endif //LIBRARY_COLLISIONMODEL_H
