//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_PHYSICALMODEL_H
#define LIBRARY_PHYSICALMODEL_H

#include <cstdlib>
#include <string>
#include "Point.h"
#include "RenderModel.h"
#include "CollisionModel.h"

class Entity;


using namespace std;

class PhysicalModel
{
private:
    string name;
    double x=0.0f,y=0.0f;
    int r=0;
    bool collides,rendered;
    RenderModel* renderer;
    CollisionModel* collider;
    Entity* parentElement;
public:
    inline Entity* getParentElement() const;
    inline CollisionModel* getCollider() const;
    inline RenderModel* getRenderer() const;

    inline Point getGlobalPos() const;


    // constructors
    /**
     * Constructor for rendered and collision object
     * @param cx
     * @param cy
     * @param cr
     * @param rm
     * @param cm
     * @param p
     */
    PhysicalModel(string cname, double cx, double cy,int cr,RenderModel* rm, CollisionModel* cm, Entity* p)
    {
        name = cname;
        x = cx;
        y = cy;
        r = cr;
        renderer = rm;
        collider = cm;
        parentElement = p;
        collides = true;
        rendered = true;
    }

    /**
     * Constructor for rendered object that does not collide
     * @param cx
     * @param cy
     * @param cr
     * @param rm
     * @param p
     */
    PhysicalModel(string cname, double cx, double cy,int cr,RenderModel* rm, Entity* p)
    {
        name = cname;
        x = cx;
        y = cy;
        r = cr;
        renderer = rm;
        parentElement = p;
        collides = false;
        rendered = true;
    }


    /**
     * Constructor for invisible object that collides
     * @param cx
     * @param cy
     * @param cr
     * @param cm
     * @param p
     */
    PhysicalModel(string cname, double cx, double cy,int cr,CollisionModel* cm, Entity* p)
    {
        name = cname;
        x = cx;
        y = cy;
        r = cr;
        collider = cm;
        parentElement = p;
        collides = true;
        rendered = false;
    }

    PhysicalModel(string cname)
    {
        name = cname;
    }
};


#endif //LIBRARY_PHYSICALMODEL_H
