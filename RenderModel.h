//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_RENDERMODEL_H
#define LIBRARY_RENDERMODEL_H


#include <list>
#include <map>
#include "Point.h"
#include "Color.h"
#include "Texture.h"

using namespace std;
class PhysicalModel;

class RenderModel
{
public:
    enum Shape{BOX,CIRCLE};
private:
    unsigned int width;
    unsigned int height;
    Shape model;
    Color* color = nullptr;
    Texture* texture = nullptr;
    bool textured;
    double origin_x,origin_y,box_bottom,box_top,box_left,box_right,circle_radius;
    int angle=0.0;
    PhysicalModel* parentElement;

    enum ConType{INT,DOUBLE,STRING,ENUM,COLOR};
    static map<string,ConType> conImport = {{"origin_x",DOUBLE},{"origin_y",DOUBLE},{"box_top",DOUBLE},{"box_bottom",DOUBLE},
                                            {"box_left",DOUBLE},{"box_right",DOUBLE},{"circle_radius",DOUBLE},{"color",DOUBLE}};
public:

    inline Point getGlobalPos() const;
    inline Point* getRectPoints() const;

    RenderModel(Shape s, PhysicalModel* p)
    {
        model = s;
        parentElement = p;
        color = new Color(255);
    }
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
