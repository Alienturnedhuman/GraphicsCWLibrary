//
// Created by Ben Dickson on 5/9/17.
//

#include "CollisionModel.h"


inline CollisionModel::Shape CollisionModel::getModel() const
{
    return model;
}
inline PhysicalModel* CollisionModel::getParentElement() const
{
    return parentElement;
}
inline bool CollisionModel::collidesCC(const CollisionModel &cm) const
{
    // code for Circle/Circle collision here
    Point aPos = this->getGlobalPos();
    Point bPos = cm.getGlobalPos();

    double xDiff = aPos.x - bPos.x;
    double yDiff = aPos.y - bPos.y;
    double rSum = this->getRadius()+cm.getRadius();

    free(&aPos);
    free(&bPos);

    return rSum*rSum < (xDiff*xDiff + yDiff*yDiff);
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


inline void CollisionPipeline::addModel(CollisionModel* model)
{
    pipeline.push_back(model);
    ++size;
}
inline CollisionModel* CollisionPipeline::retrieveModel()
{
    if(size==0)
    {
        return nullptr;
    }
    CollisionModel* r = pipeline.back();
    pipeline.pop_back();
    --size;
    return r;
}