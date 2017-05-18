//
// Created by Ben Dickson on 5/9/17.
//

#include "Entity.h"

inline int Entity::elementCount() const
{
    return ec;
}

/*
inline void Entity::addElement(PhysicalModel aElement)
{
    element.push_back(aElement);
    ++ec;
}
void Entity::addElement(PhysicalModel aElement[], int eCount)
{
    int i = -1;
    while(++i<eCount)
    {
        element.push_back(aElement[i]);
    }
    ec+=eCount;
}
void Entity::addElement(list<PhysicalModel> aElement)
{
    for(list<PhysicalModel>::iterator it = aElement.begin(); it != aElement.end() ; it++)
    {
        element.push_back(*it);
    }
    ec += aElement.size();
}
*/


inline Point Entity::getGlobalPos() const
{
    Point rv;
    rv.x = x;
    rv.y = y;
    rv.r = r;
    return rv;
}
inline int Entity::getRenderLayer()
{
    return renderLayer;
}

inline bool Entity::isMoving() const
{
    return !(vx==0&&vy==0);
}


bool Entity::importBool(string var,bool value)
{
    if(var == "canRotate")
    {
        canRotate = value;
    }
    else if(var=="movable")
    {
        movable = value;
    }
    else if(var=="affectedByGravity")
    {
        affectedByGravity = value;
    }
    else if(var=="invincible")
    {
        invincible = value;
    }
    else
    {
        return false;
    }
    return true;
}

bool Entity::importEnum(string var,string value)
{
    if(var == "collisionDirection")
    {
        if(find(collisionDirections.begin(),collisionDirections.end(),CollisionDirection::ALL)==collisionDirections.end())
        {
            stringstream pS(value);
            string direction;
            while(getline(pS,direction,','))
            {
                if(direction=="ALL")
                {
                    collisionDirections.clear();
                    collisionDirections.push_back(CollisionDirection::ALL);
                    return true;
                }
                else if(direction=="UP")
                {
                    if(find(collisionDirections.begin(),collisionDirections.end(),CollisionDirection::UP)==collisionDirections.end())
                    {
                        collisionDirections.push_back(CollisionDirection::UP);
                    }
                }
                else if(direction=="DOWN")
                {
                    if(find(collisionDirections.begin(),collisionDirections.end(),CollisionDirection::DOWN)==collisionDirections.end())
                    {
                        collisionDirections.push_back(CollisionDirection::DOWN);
                    }
                }
                else if(direction=="LEFT")
                {
                    if(find(collisionDirections.begin(),collisionDirections.end(),CollisionDirection::LEFT)==collisionDirections.end())
                    {
                        collisionDirections.push_back(CollisionDirection::LEFT);
                    }
                }
                else if(direction=="RIGHT")
                {
                    if(find(collisionDirections.begin(),collisionDirections.end(),CollisionDirection::RIGHT)==collisionDirections.end())
                    {
                        collisionDirections.push_back(CollisionDirection::RIGHT);
                    }
                }
            }
        }
    }
    else if(var=="collisionRule")
    {
        pair<string,string> lineVar = getEquals(value,':');
        string entityStr = lineVar.first;
        EntityType entity;
        map<EntityType,list<CollisionRule>>::iterator i;
        list<CollisionRule> rules;
        bool import = true;
        if(entityStr=="PLAYER")
        {
            entity = PLAYER;
        }
        else if(entityStr=="NPC")
        {
            entity = NPC;
        }
        else if(entityStr=="PROJECTILE")
        {
            entity = PROJECTILE;
        }
        else if(entityStr=="BOX")
        {
            entity = BOX;
        }
        else if(entityStr=="SURFACE")
        {
            entity = SURFACE;
        }
        else if(entityStr=="ENEMY")
        {
            entity = ENEMY;
        }
        else if(entityStr=="GENERIC")
        {
            entity = GENERIC;
        }
        else
        {
            import = false;
        }
        if(import)
        {
            i=collisionRules.find(entity);

            if(i==collisionRules.end())
            {
                rules = list<CollisionRule>();
                collisionRules.insert(pair<EntityType,list<CollisionRule>>({entity,rules}));
            }
            else
            {
                rules=(*i).second;
            }
        }
    }
    else if(var=="canCollect")
    {
        stringstream pS(value);
        string thing;
        while(getline(pS,thing,','))
        {
            if(thing=="KEY")
            {
                if(find(collisionDirections.begin(),collisionDirections.end(),Collectibles::KEY)==collisionDirections.end())
                {
                    belt.insert(pair<Collectibles,bool>(Collectibles::KEY,false));
                }
            }
            else if(thing=="JETPACK")
            {
                if(find(collisionDirections.begin(),collisionDirections.end(),Collectibles::JETPACK)==collisionDirections.end())
                {
                    belt.insert(pair<Collectibles,bool>(Collectibles::JETPACK,false));
                }
            }
            else if(thing=="KEY*")
            {
                if(find(collisionDirections.begin(),collisionDirections.end(),Collectibles::KEY)==collisionDirections.end())
                {
                    belt.insert(pair<Collectibles,bool>(Collectibles::KEY,true));
                }
            }
            else if(thing=="JETPACK*")
            {
                if(find(collisionDirections.begin(),collisionDirections.end(),Collectibles::JETPACK)==collisionDirections.end())
                {
                    belt.insert(pair<Collectibles,bool>(Collectibles::JETPACK,true));
                }
            }
            else
            {
                pair<string,string> baggable = getEquals(thing,':');
                string item = baggable.first;
                int q = -1;
                Consumables c;
                if(item=="FUEL")
                {
                    c=FUEL;
                    q=stoi(baggable.second);
                }
                else if(item=="BULLETS")
                {
                    c=BULLETS;
                    q=stoi(baggable.second);
                }
                else if(item=="BATTERY")
                {
                    c=BATTERY;
                    q=stoi(baggable.second);
                }
                else if(item=="OXYGEN")
                {
                    c=OXYGEN;
                    q=stoi(baggable.second);
                }
                if(q>=0)
                {
                    enableCollection(c,q);
                }
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool Entity::importInt(string var,int value)
{
    if(var == "r")
    {
        r = value;
    }
    else if(var == "renderLayer")
    {
        renderLayer = value;
    }
    else if(var == "health")
    {
        health = value;
    }
    else if(var == "damage")
    {
        damage = value;
    }
    else
    {
        return false;
    }
    return true;
}


bool Entity::importDouble(string var,double value)
{
    if(var == "x")
    {
        x = value;
    }
    else if(var == "y")
    {
        y = value;
    }
    else if(var == "vx")
    {
        vx = value;
    }
    else if(var == "vy")
    {
        vy = value;
    }
    else if(var == "m")
    {
        m = value;
    }
    else if(var == "e")
    {
        e = value;
    }
    else if(var == "vMax")
    {
        vMax = value;
    }
    else
    {
        return false;
    }
    return true;
}