//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_RENDERMODEL_H
#define LIBRARY_RENDERMODEL_H


#include <list>
#include "Point.h"
#include "Color.h"
#include "Texture.h"

using namespace std;
class PhysicalModel;

class RenderModel {
private:
    unsigned int width;
    unsigned int height;
    Color color;
    Texture texture;
    bool textured;
    double origin_x,origin_y,box_bottom,box_top,box_left,box_right,circle_radius;
    int angle;
    PhysicalModel* parentElement;
public:

    inline Point getGlobalPos() const;
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
