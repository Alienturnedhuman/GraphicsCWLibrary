//
// Created by Ben Dickson on 5/9/17.
//

#ifndef LIBRARY_POINT_H
#define LIBRARY_POINT_H

#include <math.h>
#include <cstdlib>
#include <string>


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
    const double PI = 3.1415926535897932384626433832795f;

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

// white space trimmer
// taken from http://stackoverflow.com/a/1798170
std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

#endif //LIBRARY_POINT_H
