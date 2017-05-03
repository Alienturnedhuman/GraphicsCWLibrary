//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_COLOR_H
#define LIBRARY_COLOR_H


class Color {
private:
    unsigned char vR;
    unsigned char vG;
    unsigned char vB;
    unsigned char vA;
public:
    // getters
    unsigned char r();
    unsigned char g();
    unsigned char b();
    unsigned char a();
    unsigned char h();
    unsigned char s();
    unsigned char l();

    // setters
    void setColor(unsigned char grey);
    void setColor(unsigned char r,unsigned char g,unsigned char b);
    void setColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
    void setColor(int h, unsigned char s, unsigned char l);
    void setColor(int h, unsigned char s, unsigned char l,unsigned char a);

    // constructors
    Color();
    Color(unsigned char grey);
    Color(unsigned char r,unsigned char g,unsigned char b);
    Color(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
    Color(int h, unsigned char s, unsigned char l);
    Color(int h, unsigned char s, unsigned char l,unsigned char a);
};


#endif //LIBRARY_COLOR_H
