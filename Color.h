//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_COLOR_H
#define LIBRARY_COLOR_H


class Color {
private:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
public:

    
    Color();
    Color(unsigned char grey);
    Color(unsigned char r,unsigned char g,unsigned char b);
    Color(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
    Color(int h, unsigned char s, unsigned char l);
    Color(int h, unsigned char s, unsigned char l,unsigned char a);

};


#endif //LIBRARY_COLOR_H
