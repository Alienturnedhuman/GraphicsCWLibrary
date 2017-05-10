//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_POINT_H
#define LIBRARY_POINT_H

#include <math.h>


struct Point
{
    double x,y,r;
};

class Rotation
{
private:
    double sinValue[360];
    double cosValue[360];
public:
    const static float PI = 3.1415926535897932384626433832795f;

    inline double cos(int angle) const
    {
        if(angle<0)
        {
            return cosValue[(angle%360+360)%360];
        }
        return cosValue[angle%360];
    }
    inline double sin(int angle) const
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
        cosValue[0] = 1;
        cosValue[90] = 0;
        cosValue[180] = -1;
        cosValue[270] = 0;
        sinValue[0] = 0;
        sinValue[90] = 1;
        sinValue[180] = 0;
        sinValue[270] = -1;
    }

};


#endif //LIBRARY_POINT_H
