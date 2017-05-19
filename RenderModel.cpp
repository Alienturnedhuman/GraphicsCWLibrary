//
// Created by Ben Dickson on 5/4/17.
//

#include "RenderModel.h"

map<string,ConType> RenderModel::conImport = {{"origin_x",DOUBLE},{"origin_y",DOUBLE},{"box_top",DOUBLE},{"box_bottom",DOUBLE},
{"box_left",DOUBLE},{"box_right",DOUBLE},{"circle_radius",DOUBLE},{"color",COLOR}};

bool RenderModel::importDouble(string var,double value)
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
    else if(var == "circle_radius")
    {
        circle_radius = value;
    }
    else
    {
        return false;
    }
    return true;
}

bool RenderModel::importColor(string var, unsigned char r, unsigned char g, unsigned char b)
{
    if (var == "color") {
        if(color== nullptr)
        {
            color = new Color(r,g,b);
        }
        else
        {
            color->setColor(r,g,b);
        }
    }
    else
    {
        return false;
    }
    return true;
}


inline void RenderPipeline::addModel(RenderModel* model)
{
    pipeline.push_back(model);
    ++size;
}
inline RenderModel* RenderPipeline::retrieveModel()
{
    if(size==0)
    {
        return nullptr;
    }
    RenderModel* r = pipeline.back();
    pipeline.pop_back();
    --size;
    return r;
}