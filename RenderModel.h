//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_RENDERMODEL_H
#define LIBRARY_RENDERMODEL_H


#include <list>
#include <map>
#include <sstream>
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
    static map<string,ConType> conImport;

    // import values
    bool importDouble(string var , double value);
    bool importInt(string var, int value);
    bool importString(string var, string value);
    bool importColor(string var, unsigned char r, unsigned char g, unsigned char b);
public:

    inline Point getGlobalPos() const;
    inline Point* getRectPoints() const;


    inline bool parseConstructorPair(pair<string,string> p)
    {
        map<string,ConType>::iterator it = conImport.find(p.first);
        if(it!=conImport.end())
        {
            switch((*it).second)
            {
                case DOUBLE:
                    return importDouble(p.first,stod(p.second));
                case INT:
                    return importInt(p.first,stoi(p.second));
                case STRING:
                    return importString(p.first,p.second);
                case COLOR:
                    stringstream pS(p.second);
                    string c;
                    getline(pS,c,',');
                    int r=stoi(c);
                    getline(pS,c,',');
                    int g=stoi(c);
                    getline(pS,c,',');
                    int b=stoi(c);
                    if(r>255)
                    {
                        r=255;
                    }
                    if(r<0)
                    {
                        r=0;
                    }
                    if(g>255)
                    {
                        g=255;
                    }
                    if(g<0)
                    {
                        g=0;
                    }
                    if(b>255)
                    {
                        b=255;
                    }
                    if(b<0)
                    {
                        b=0;
                    }
                    return importColor(p.first,(unsigned char)r,(unsigned char)g,(unsigned char)b);
            }
        }
        return false;
    }
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
