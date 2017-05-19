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
    static enum Consumables{FUEL,BULLETS,BATTERY,OXYGEN};
    static enum Collectibles{KEY,JETPACK};
private:
    // graphics / physics rules
    map<string,PhysicalModel*> element;
    EntityType modelType = GENERIC;
    int ec = 0 , r=0; // ec =  element count (maintained here for speed) | r = rotation
    double x,y , vx = 0.0,vy=0.0, e=0.0 , m=1.0 , vMax=0; // x/y pos | vx/vy velocities | e = elasticity | m = mass
    bool canRotate = false;
    int renderLayer=3;
    bool movable = false;
    bool affectedByGravity = false;
    string name;

    // gameplay / interaction rules
    map<EntityType,list<CollisionRule>> collisionRules;
    list<CollisionDirection> collisionDirections;
    int health = 100;
    int damage = 0;
    int invincible = true;
    map<Consumables,int> bag;
    map<Collectibles,bool> belt;


    // constructor based stuff
    enum ConType{INT,DOUBLE,STRING,ENUM,BOOL};
    static map<string,ConType> conImport;

    // import values
    bool importDouble(string var , double value);
    bool importInt(string var, int value);
    bool importString(string var, string value);
    bool importEnum(string var, string value);
    bool importBool(string var, bool value);
public:
    inline int elementCount() const;

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

    inline void enableCollection(Consumables c, int v=0)
    {
        if(v<0)
        {
            v=0;
        }
        map<Consumables,int>::iterator bf=bag.find(c);
        if(bf==bag.end())
        {
            bag.insert(pair<Consumables ,int>(c,v));
        }
        else
        {
            ((*bf).second)+=v;
        }
    }
    inline void enableCollection(Collectibles c, bool v=false)
    {
        map<Collectibles,bool>::iterator bf=belt.find(c);
        if(bf==belt.end())
        {
            belt.insert(pair<Collectibles ,bool>(c,v));
        }
        else
        {
            ((*bf).second)=v;
        }
    }

    bool inline canCollect(Consumables c)
    {
        return bag.find(c)!=bag.end();
    }
    bool inline canCollect(Collectibles c)
    {
        return belt.find(c)!=belt.end();
    }

    inline int collectConsumable(Consumables c,int count)
    {
        map<Consumables,int>::iterator bf=bag.find(c);
        if(bf==bag.end())
        {
            return 0;
        }
        else
        {
            ((*bf).second)+=count;
            if(((*bf).second)<0)
            {
                ((*bf).second)=0;
            }
            return ((*bf).second);
        }
    }
    inline bool collectCollectibles(Collectibles c)
    {
        map<Collectibles,bool>::iterator bf=belt.find(c);
        if(bf==belt.end())
        {
            return false;
        }
        else
        {
            return (((*bf).second)=true);
        }
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
    inline void setX(double nx)
    {
        x = nx;
    }
    inline void setY(double ny)
    {
        y = ny;
    }
    // constructors and Entity construction methods

    inline bool addPhysicalModel(string name, PhysicalModel* m)
    {
        if(element.find(name)==element.end())
        {
            element.insert(pair<string,PhysicalModel*>(name,m));
            return true;
        }
        else
        {
            return false;
        }
    }


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
                case ENUM:
                    return importEnum(p.first,p.second);
                case BOOL:
                    return importBool(p.first,p.second=="true");
            }
        }
        return false;
    }

    Entity(string c_name)
    {
        name = c_name;
    }

    /*
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
    */
};


#endif //LIBRARY_ENTITY_H
