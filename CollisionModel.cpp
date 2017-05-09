//
// Created by Ben Dickson on 5/9/17.
//

#include "CollisionModel.h"


inline CollisionModel::Shape CollisionModel::getModel() const
{
    return model;
}
inline PhysicalModel CollisionModel::getParentElement() const
{
    return parentElement;
}
inline bool CollisionModel::collidesCC(const CollisionModel &cm) const
{
    // code for Circle/Circle collision here
}
inline bool CollisionModel::collidesCB(const CollisionModel &cm) const
{
    // code for Circle/Box collision here
}
inline bool CollisionModel::collidesBB(const CollisionModel &cm) const
{
    // code for Box/Box collision here
}
inline bool CollisionModel::collidesBC(const CollisionModel &cm) const
{
    return cm.collidesCB((CollisionModel &) this);
}