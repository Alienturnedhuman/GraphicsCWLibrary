//
// Created by Ben Dickson on 5/4/17.
//

#include "Color.h"

/**
 * returns the red value
 * @return
 */
inline unsigned char Color::r()
{
    return vR;
}

/**
 * return the green value
 * @return
 */
inline unsigned char Color::g()
{
    return vG;
}

/**
 * returns the blue value
 * @return
 */
inline unsigned char Color::b()
{
    return vB;
}

/**
 * returns the alpha value
 * @return
 */
inline unsigned char Color::a()
{
    return vA;
}

/**
 * calculates and returns the hue for the color
 *
 * based on Zarokka's answer (and improved by me) from the thread:
 * http://stackoverflow.com/questions/23090019/fastest-formula-to-get-hue-from-rgb
 *
 * @return
 */
inline unsigned int Color::h()
{
    int min,max;
    /*
     *  speed is the most important thing, so I have 'unrolled'
     *  the if statements rather than use max/min functions as these
     *  would duplicate many checks
     */
    if(vR>vG)
    {
        if(vB>vG)
        {
            // vB > vG > vR
            min = vR;
            max = vB;
        }
        else
        {
            // vG > VR||vB
            max = vG;
            min = vB>vR?vR:vB;
        }
    }
    else
    {
        if(vB>vR)
        {
            // vB > vR > vG
            min = vG;
            max = vB;
        }
        else
        {
            // vR > VG||VB
            max = vR;
            min = vB>vG?vG:vB;
        }
    }
    float hue = 0.0;
    if(max == vR)
    {
        hue = 6.0 + (double)(vG - vB) / (max - min);
    }
    else if(max == vG)
    {
        hue = 2.0 + (double)(vB - vR) / (max - min);
    }
    else
    {
        hue = 4.0 + (double)(vR - vG) / (max - min);
    }
    hue *= 60;
    return ((unsigned int)hue)%360;
}

/**
 * calculates and returns the saturation of the color
 *
 * based (but modified by me) on code here:
 * https://gist.github.com/mjackson/5311256
 * @return
 */
inline unsigned char Color::s()
{
    int min,max;
    /*
     *  speed is the most important thing, so I have 'unrolled'
     *  the if statements rather than use max/min functions as these
     *  would duplicate many checks
     */
    if(vR>vG)
    {
        if(vB>vG)
        {
            // vB > vG > vR
            min = vR;
            max = vB;
        }
        else
        {
            // vG > VR||vB
            max = vG;
            min = vB>vR?vR:vB;
        }
    }
    else
    {
        if(vB>vR)
        {
            // vB > vR > vG
            min = vG;
            max = vB;
        }
        else
        {
            // vR > VG||VB
            max = vR;
            min = vB>vG?vG:vB;
        }
    }
    if(min == max)
    {
        return 0;
    }
    float l = (float)(max + min)/512;
    float d = (float)(max - min)/256;
    return (unsigned char)((l > 0.5 ? d / (2 - max - min) : d / (max + min))*256);
}
/**
 * calculates and returns the lightness of the color
 *
 * based (but modified by me) on code here:
 * https://gist.github.com/mjackson/5311256
 * @return
 */
inline unsigned char Color::l()
{
    int min,max;
    /*
     *  speed is the most important thing, so I have 'unrolled'
     *  the if statements rather than use max/min functions as these
     *  would duplicate many checks
     */
    if(vR>vG)
    {
        if(vB>vG)
        {
            // vB > vG > vR
            min = vR;
            max = vB;
        }
        else
        {
            // vG > VR||vB
            max = vG;
            min = vB>vR?vR:vB;
        }
    }
    else
    {
        if(vB>vR)
        {
            // vB > vR > vG
            min = vG;
            max = vB;
        }
        else
        {
            // vR > VG||VB
            max = vR;
            min = vB>vG?vG:vB;
        }
    }
    return (max + min)/2;
}

/**
 * Sets the alpha of the color (without modifying color)
 * @param alpha
 */
inline void Color::setAlpha(unsigned char alpha)
{
    vA = alpha;
}

/**
 * Sets the color to the greyscale value (without modifying alpha)
 * @param grey
 */
inline void Color::setColor(unsigned char grey)
{
    vR = grey;
    vG = grey;
    vB = grey;
}

/**
 * Sets the color to the rgb values provided (without modifying alpha)
 * @param r
 * @param g
 * @param b
 */
inline void Color::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    vR = r;
    vG = g;
    vB = b;
}

/**
 * Sets the color to the rgba values provided
 * @param r
 * @param g
 * @param b
 * @param a
 */
inline void Color::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    setColor(r,g,b);
    setAlpha(a);
}

/**
 * Required for the HSL import
 *
 * based on Javascript code found on the blog here (original source defunct):
 * http://axonflux.com/handy-rgb-to-hsl-and-rgb-to-hsv-color-model-c
 *
 * I rewrote it in C++
 *
 * @param p
 * @param q
 * @param t
 * @return
 */
inline double Color::hue2rgb(double p, double q, double t)
{
    if (t < 0)
    {
        t += 1;
    }
    if (t > 1)
    {
        t -= 1;
    }
    if (t < (double)(1.0 / 6))
    {
        double r= (p + (q - p) * 6 * t);
        return r;
    }
    if (t < (double)(1.0 / 2))
    {
        double r = q;
        return r;
    }
    if (t < (double)(2.0 / 3))
    {
        double r = (p + (q - p) * (2 / 3 - t) * 6);
        return r;
    }
    p = p < 0 ? 0 : (p>1?1:p);
    return p;
}

/**
 * Sets color based on hsl values (does not modify alpha)
 *
 * based on Javascript code found on the blog here (original source defunct):
 * http://axonflux.com/handy-rgb-to-hsl-and-rgb-to-hsv-color-model-c
 *
 * I rewrote it in C++
 *
 * @param h
 * @param s
 * @param l
 */
inline void Color::setColor(int h, unsigned char s, unsigned char l) {
    if (s == 0)
    {
        vR = (vG = (vB = l));
    }
    else
    {
        double dh = (double)h/360;
        double ds = (double)s/256;
        double dl = (double)l/256;
        double q = dl < 0.5 ? dl * (1 + ds) : dl + ds - l * ds;
        double p = 2 * dl - q;
        vR = (unsigned char)(hue2rgb(p, q, (dh + (double)(1.0 / 3.0)))*256);
        vG = (unsigned char)((hue2rgb(p, q, dh)) * 256);
        vB = (unsigned char)((hue2rgb(p, q, (dh - (double)(1.0/ 3.0)))) * 256);
    }
}

/**
 * Sets color based on hsla values
 *
 * @param h
 * @param s
 * @param l
 * @param a
 */
inline void Color::setColor(int h, unsigned char s, unsigned char l, unsigned char a)
{
    setColor(h,s,l);
    setAlpha(a);
}