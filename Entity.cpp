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