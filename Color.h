//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_COLOR_H
#define LIBRARY_COLOR_H

#include <cstdlib>
using namespace std;

class Color
{
private:
    unsigned char vR;
    unsigned char vG;
    unsigned char vB;
    unsigned char vA;

    inline double hue2rgb(double p, double q, double t);
public:
    // getters
    inline unsigned char r();
    inline unsigned char g();
    inline unsigned char b();
    inline unsigned char a();
    inline unsigned int h();
    inline unsigned char s();
    inline unsigned char l();

    // setters
    inline void setAlpha(unsigned char alpha);
    inline void setColor(unsigned char grey);
    inline void setColor(unsigned char r,unsigned char g,unsigned char b);
    inline void setColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
    inline void setColor(int h, unsigned char s, unsigned char l);
    inline void setColor(int h, unsigned char s, unsigned char l,unsigned char a);

    // constructors
    Color();
    Color(unsigned char grey);
    Color(unsigned char r,unsigned char g,unsigned char b);
    Color(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
    Color(int h, unsigned char s, unsigned char l);
    Color(int h, unsigned char s, unsigned char l,unsigned char a);
};


#endif //LIBRARY_COLOR_H
