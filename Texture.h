//
// Created by Ben Dickson on 5/4/17.
//

#ifndef LIBRARY_TEXTURE_H
#define LIBRARY_TEXTURE_H


class Texture {
private:
    unsigned int width;
    unsigned int height;
    unsigned int frames;
    unsigned int byteCount;
    unsigned int dataSize;
    unsigned char* data;
    unsigned int bytesPerPixel = 4;
public:
    unsigned char* renderFrame(unsigned int frameNumber);

    Texture(unsigned char* textureData , unsigned int  textureDataSize ,
            unsigned int textureWidth , unsigned int textureHeight);
};


#endif //LIBRARY_TEXTURE_H
