//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_POINT_H
#define LIBRARY_POINT_H

#include <math.h>

#define PI 3.14159265

struct Point {
    double x,y,r;
};

class Rotation
{
private:
    double sinValue[360];
    double cosValue[360];
public:
    inline double cos(int angle)
    {
        if(angle<0)
        {
            return cosValue[(angle%360+360)%360];
        }
        return cosValue[angle%360];
    }
    inline double sin(int angle)
    {
        if(angle<0)
        {
            return sinValue[(angle%360+360)%360];
        }
        return sinValue[angle%360];
    }

    Rotation()
    {
        int i=-1;
        while(++i<360)
        {
            sinValue[i] = sin(((double)i*PI)/180);
            cosValue[i] = cos(((double)i*PI)/180);
        }
    }

};


#endif //LIBRARY_POINT_H
