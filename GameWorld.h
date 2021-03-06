//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_GAMEWORLD_H
#define LIBRARY_GAMEWORLD_H

#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "Point.h"
#include "Entity.h"
#include "NonPlayerCharacter.h"

using namespace std;

class GameWorld
{
private:
    CollisionPipeline collisionPipeline;
    CollisionPipeline movingPipeline;
    RenderPipeline renderLayer[5];
    map<string,Entity*> entities;    // UID , Entity
    list<NonPlayerCharacter> npc;

    double gravity = 10.0;

    string name;
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
            Entity* newEnt = new Entity(uid);
            entities.insert(pair<string,Entity*>(uid,newEnt));
            return newEnt;
        }
        else
        {
            return nullptr;
        }
    }

    inline string getName()
    {
        return name;
    }

    GameWorld(string ln)
    {
        name = ln;
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
        cout << "linelength " << lineLen <<": ";
        if(lineLen > 2)
        {
            cout << " >> ";
            if (lineString.at(0)=='<' && lineString.at(lineLen-1)=='>')
            {
                entName = lineString.substr(1,lineLen-2);
                currentEnt = gw.createEntity(entName);
                currentPM = nullptr;
                currentRM = nullptr;
                currentCM = nullptr;

                cout << "Entity name '" << entName << "'";
            }
            else if(currentEnt != nullptr)
            {
                if(lineString.at(0)=='[')
                {
                    if(lineString.at(lineLen-1) == ']')
                    {
                        string pmName = lineString.substr(1,lineLen-2);
                        currentPM = new PhysicalModel(pmName);
                        if(!currentEnt->addPhysicalModel(pmName,currentPM))
                        {
                            free(currentPM);
                            currentPM = nullptr;
                        }

                        cout << "PhysicalModel name '" << pmName << "'";
                    }
                }
                else if(lineString.at(0)=='(' && currentPM != nullptr)
                {
                    if(lineLen > 18 && currentPM->getCollider() == nullptr && lineString.substr(0,17)=="(CollisionModel::"
                       && lineString.at(lineLen-1)==')')
                    {
                        string colType = lineString.substr(17,lineLen-18);
                        CollisionModel::Shape s;
                        if(colType=="BOX")
                        {
                            s = CollisionModel::BOX;
                        }
                        else if(colType=="CIRCLE")
                        {
                            s = CollisionModel::CIRCLE;
                        }
                        currentCM = new CollisionModel(s,currentPM);

                        cout << "PhysicalModel type '" << colType << "'";
                    }
                    else if(lineLen > 15 && currentPM->getRenderer() == nullptr && lineString.substr(0,14)=="(RenderModel::"
                            && lineString.at(lineLen-1)==')')
                    {
                        string renType = lineString.substr(14,lineLen-15);
                        RenderModel::Shape s;
                        if(renType=="BOX")
                        {
                            s = RenderModel::BOX;
                        }
                        else if(renType=="CIRCLE")
                        {
                            s = RenderModel::CIRCLE;
                        }
                        currentRM = new RenderModel(s,currentPM);

                        cout << "PhysicalModel type '" << renType << "'";
                    }
                    else
                    {
                        currentPM = nullptr;
                        currentRM = nullptr;
                        currentCM = nullptr;
                    }
                }
                else
                {
                    pair<string,string> lineVar = getEquals(lineString);
                    if(currentCM != nullptr && currentPM != nullptr)
                    {
                        currentCM->parseConstructorPair(lineVar);
                    }
                    else if(currentRM != nullptr && currentPM != nullptr)
                    {
                        currentRM->parseConstructorPair(lineVar);
                    }
                    else if(currentPM != nullptr)
                    {
                        currentPM->parseConstructorPair(lineVar);
                    }
                    else
                    {
                        currentPM = nullptr;
                        currentRM = nullptr;
                        currentCM = nullptr;
                    }

                    cout << "equals line '" << lineVar.first << "' is equal to  '" << lineVar.second << "'";
                }
            }
        }
        cout << endl;
    }
    return is;
}

#endif //LIBRARY_GAMEWORLD_H
