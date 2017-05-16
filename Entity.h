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

class Entity
{
public:
    static enum EntityType{PLAYER,NPC,PROJECTILE,BOX,SURFACE,ENEMY,GENERIC};
    static enum CollisionRule{DAMAGE,HEALTH,KILLS,DIES,BOUNCES,STOPS,GAMEOVER,LEVELCOMPLETE,TRIGGER};
    static enum CollisionDirection{ALL,UP,DOWN,LEFT,RIGHT};
private:
    // graphics / physics rules
    list<PhysicalModel> element;
    EntityType modelType = GENERIC;
    int ec = 0 , r=0; // ec =  element count (maintained here for speed) | r = rotation
    double x,y , vx = 0.0,vy=0.0, e=0.0 , m=1.0 , vMax=0; // x/y pos | vx/vy velocities | e = elasticity | m = mass
    bool canRotate = false;
    int renderLayer;
    bool movable;
    bool affectedByGravity = false;

    // gameplay / interaction rules
    map<EntityType,list<CollisionRule>> collisionRules;
    list<CollisionDirection> collisionDirections;
    int health = 100;
    int damage = 0;
    int invincible = true;

public:
    inline int elementCount() const;

    inline void addElement(PhysicalModel aElement);
    void addElement(PhysicalModel aElement[],int eCount);
    void addElement(list<PhysicalModel> aElement);
    inline int getRenderLayer();

    inline bool isMoving() const;

    inline Point getGlobalPos() const;

    // modifiers
    inline int healthModifier(int h)
    {
        health+=h;
        return health;
    }

    // getters
    inline bool isAffectedByGravity()
    {
        return affectedByGravity;
    }
    inline bool isMovable()
    {
        return movable;
    }

    // collection setters
    inline void addCollisionRule(EntityType k , CollisionRule m)
    {
        map<EntityType,list<CollisionRule>>::iterator it = find(collisionRules.begin(),collisionRules.end(),k);
        if(it == collisionRules.end())
        {
            list<CollisionRule> ne;
            ne.push_back(m);
            collisionRules.insert(pair<EntityType,list<CollisionRule>>(k,ne));
        }
        else
        {
            ((*it).second).push_back(m);
        }
    }
    inline void addCollisionDirection(CollisionDirection c)
    {
        list<CollisionDirection>::iterator it = find(collisionDirections.begin(),collisionDirections.end(),c);
        if(it == collisionDirections.end())
        {
            collisionDirections.push_back(c);
        }
    }

    // setters
    inline void setAffectedByGravity(bool c)
    {
        affectedByGravity = c;
    }
    inline void setMovable(bool c)
    {
        movable = c;
    }
    inline void setRenderLayer(int c)
    {
        renderLayer = c;
    }
    inline void setHealth(int c)
    {
        health = c;
    }
    inline void setDamage(int c)
    {
        damage = c;
    }
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
