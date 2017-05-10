//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_ENTITY_H
#define LIBRARY_ENTITY_H

#include <cstdlib>
#include <list>
#include <map>

#include "Point.h"
#include "PhysicalModel.h"

using namespace std;

class Entity {
public:
    static enum EntityType{PLAYER,NPC,PROJECTILE,BOX,SURFACE,ENEMY,GENERIC};
    static enum CollisionRule{DAMAGE,HEALTH,KILLS,DIES,BOUNCES,STOPS,GAMEOVER,LEVELCOMPLETE};
    static enum CollisionDirection{ALL,UP,DOWN,LEFT,RIGHT};
private:
    list<PhysicalModel> element;
    int ec = 0 , r=0; // element count (maintained here for speed)
    double x,y,vx = 0.0,vy=0.0,e=0.0,m=1.0;
    bool canRotate;
    EntityType modelType = GENERIC;
    int renderLayer;
    bool movable;
    map<EntityType,list<CollisionRule>> collisionRules;
    list<CollisionDirection> collisionDirections;
public:
    inline int elementCount() const;

    inline void addElement(PhysicalModel aElement);
    void addElement(PhysicalModel aElement[],int eCount);
    void addElement(list<PhysicalModel> aElement);
    inline int getRenderLayer();

    inline Point getGlobalPos() const;

    // constructors
    Entity(double cx,double cy)
    {
        x = cx;
        y = cy;
    };

    Entity(double cx,double cy , EntityType cModelType)
    {
        Entity(cx,cy);
        modelType = cModelType;
    };

    Entity(double cx,double cy , int cr)
    {
        Entity(cx,cy);
        r = cr;
    };
    Entity(double cx,double cy , int cr, EntityType cModelType)
    {
        Entity(cx,cy,cr);
        modelType = cModelType;
    };
    Entity(double cx,double cy , EntityType cModelType , double ce)
    {
        Entity(cx,cy,cModelType);
        e = ce;
    };
    Entity(double cx,double cy , int cr, EntityType cModelType , double ce)
    {
        Entity(cx,cy,cr,cModelType);
        e = ce;
    };
    Entity(double cx,double cy , int cr, EntityType cModelType , double ce , double cm)
    {
        Entity(cx,cy,cr,cModelType,ce);
        m = cm;
    };
    Entity(double cx,double cy ,EntityType cModelType , double ce , double cm)
    {
        Entity(cx,cy,cModelType,ce);
        m = cm;
    };
    Entity(double cx,double cy , int cr , bool cCanRotate)
    {
        Entity(cx,cy,cr);
        canRotate = cCanRotate;
    };
    Entity(double cx,double cy , int cr, bool cCanRotate, EntityType cModelType)
    {
        Entity(cx,cy,cr,cModelType);
        canRotate = cCanRotate;
    };
    Entity(double cx,double cy , bool cCanRotate , EntityType cModelType , double ce)
    {
        Entity(cx,cy,cModelType,ce);
        canRotate = cCanRotate;
    };
    Entity(double cx,double cy , int cr, bool cCanRotate, EntityType cModelType , double ce)
    {
        Entity(cx,cy,cr,cModelType,ce);
        canRotate = cCanRotate;
    };
    Entity(double cx,double cy , int cr, bool cCanRotate, EntityType cModelType , double ce , double cm)
    {
        Entity(cx,cy,cr,cModelType,ce,cm);
        canRotate = cCanRotate;
    };
    Entity(double cx,double cy, bool cCanRotate ,EntityType cModelType , double ce , double cm)
    {
        Entity(cx,cy,cModelType,ce,cm);
        canRotate = cCanRotate;
    };

};


#endif //LIBRARY_ENTITY_H
