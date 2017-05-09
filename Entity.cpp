//
// Created by Ben Dickson on 5/9/17.
//

#include "Entity.h"

inline int Entity::elementCount() const
{
    return ec;
}

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

