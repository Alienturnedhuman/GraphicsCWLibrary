//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_GAMEWORLD_H
#define LIBRARY_GAMEWORLD_H

#include <sstream>
#include <fstream>
#include "Point.h"
#include "Entity.h"
#include "NonPlayerCharacter.h"

class GameWorld
{
private:
    CollisionPipeline collisionPipeline;
    CollisionPipeline movingPipeline;
    RenderPipeline renderLayer[5];
    map<string,Entity> entities;    // UID , Entity
    list<NonPlayerCharacter> npc;

    double gravity = 10.0;

public:
    static Rotation angles;
    void loadLevel(stringstream levelStream);
    bool hasEntityID(string uid)
    {
        return entities.find(uid)==entities.end();
    }
    Entity* createEntity(string uid)
    {
        if(!hasEntityID(uid))
        {

        }
        else
        {
            return nullptr;
        }
    }
};


/**
 * Level importer
 * @param is
 * @param gw
 * @return
 */
inline std::ifstream& operator>>(ifstream &is, GameWorld& gw)
{
    string lineString;
    Entity* currentEnt = nullptr;
    PhysicalModel* currentPM = nullptr;
    RenderModel* currentRM = nullptr;
    CollisionModel* currentCM = nullptr;

    string entName;
    while(getline(is,lineString))
    {
        lineString = trim(lineString);
        int lineLen = lineString.length();
        if(lineLen > 2)
        {
            if (lineString.at(0)=='<' && lineString.at(lineLen-1)=='>')
            {
                entName = lineString.substr(1,lineLen-2);
                currentEnt = gw.createEntity(entName);
                currentPM = nullptr;
                currentRM = nullptr;
                currentCM = nullptr;
            }
            else if(currentEnt != nullptr)
            {
                if(lineString.at(0)=='[')
                {
                    if(lineString == "[PhysicalModel]")
                    {

                    }
                }
                else if(lineString.at(0)=='(')
                {
                    if(lineString=="(CollisionModel)")
                    {

                    }
                    else if(lineString=="(RenderModel)")
                    {

                    }
                    else
                    {

                    }
                }
                else
                {
                    if(currentCM != nullptr && currentPM != nullptr)
                    {

                    }
                    else if(currentRM != nullptr && currentPM != nullptr)
                    {

                    }
                    else if(currentPM != nullptr)
                    {

                    }
                    else
                    {

                    }
                }
            }
        }
    }
    return is;
}

#endif //LIBRARY_GAMEWORLD_H
