//
// Created by Ben Dickson on 5/9/17.
//

#include "PhysicalModel.h"


inline Entity* PhysicalModel::getParentElement() const
{
    return parentElement;
}

inline CollisionModel* PhysicalModel::getCollider() const
{
    return collider;
}

inline RenderModel* PhysicalModel::getRenderer() const
{
    return renderer;
}

bool PhysicalModel::importDouble(string var,double value)
{
    if(var == "x")
    {
        x = value;
    }
    else if(var == "y")
    {
        y = value;
    }
    else
    {
        return false;
    }
    return true;
}