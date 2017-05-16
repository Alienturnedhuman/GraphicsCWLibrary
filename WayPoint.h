//
// Created by Ben Dickson on 5/14/17.
//

#ifndef LIBRARY_WAYPOINT_H
#define LIBRARY_WAYPOINT_H


#include "Entity.h"


class PathNode
{
public:
    enum action{NONE,JUMP,TRIGGER};
private:
    double x;
    double y;
    double radius;


};

class Path
{
private:
    list<PathNode> node;
    bool forwards;
    list<PathNode>::iterator i;
};

class PathRouter
{
private:
    Path route;

};


class WayPoint {
public:
    enum Type{ENTITY,PATHROUTER};
    enum Logic{SIMPLE,CHARACTER};
private:
    Type following;
    Entity entityTarget;
    PathRouter pathRouter;
};


#endif //LIBRARY_WAYPOINT_H
