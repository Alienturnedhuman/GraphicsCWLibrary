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
    bool rv = false;
    Point o = getGlobalPos();
    Point* rp = cm.getRectPoints();
    rv = CollisionModel::pointInRectangle(o,rp[0],rp[1],rp[2],rp[3]);
    int circIterator = 0;
    double cr = getRadius();
    while(!rv && !(rv = CollisionModel::intersectsCircle(o,cr,rp[circIterator],rp[++circIterator%4])) &&
            circIterator>0){};  // empty while loop, checks and changes occur in condition part
    free(&o);
    free(&rp);
    return rv;
}
inline bool CollisionModel::collidesBB(const CollisionModel &cm) const
{
    bool rv = false;
    Point aO = getGlobalPos();
    Point* aRP = getRectPoints();
    Point bO = cm.getGlobalPos();
    Point* bRP = cm.getRectPoints();

    if(CollisionModel::pointInRectangle(aO,bRP[0],bRP[1],bRP[2],bRP[3]) ||
            CollisionModel::pointInRectangle(bO,aRP[0],aRP[1],aRP[2],aRP[3]))
    {
        rv = true;
    }
    else
    {

    }
    return rv;
}

void CollisionModel::importDouble(string var,double value)
{
    if(var == "origin_x")
    {
        origin_x = value;
    }
    else if(var == "origin_y")
    {
        origin_y = value;
    }
    else if(var == "box_top")
    {
        box_top = value;
    }
    else if(var == "box_bottom")
    {
        box_bottom = value;
    }
    else if(var == "box_left")
    {
        box_left = value;
    }
    else if(var == "box_right")
    {
        box_right = value;
    }
    else if(var == "circle_radius") {
        circle_radius = value;
    }
}


inline void CollisionPipeline::addModel(CollisionModel* model)
{
    pipeline.push_back(model);
    ++size;
}
inline CollisionModel* CollisionPipeline::nextModel() {
    if (it != pipeline.end()) {
        CollisionModel *r = *it;
        ++it;
    } else {
        return nullptr;
    }
}
inline CollisionModel* CollisionPipeline::popModel()
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