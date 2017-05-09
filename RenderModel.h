//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_RENDERMODEL_H
#define LIBRARY_RENDERMODEL_H


#include <list>
#include "Color.h"
#include "Texture.h"

using namespace std;

class RenderModel {
private:
    unsigned int width;
    unsigned int height;
    Color color;
    Texture texture;
    bool textured;
public:

    RenderModel();
};



class RenderPipeline
{
private:
    list<RenderModel*> pipeline;
    int size=0;
public:
    inline void addModel(RenderModel* model);
    inline RenderModel* retrieveModel();
};

inline RenderModel& operator>>(RenderModel& cm , RenderPipeline& cp)
{
    cp.addModel(&cm);
}
inline RenderModel& operator<<(RenderModel& cm , RenderPipeline& cp)
{
    return *cp.retrieveModel();
}

#endif //LIBRARY_RENDERMODEL_H
