//
// Created by Ben Dickson on 5/4/17.
//

#include <cstdlib>
#include "Texture.h"

/**
 * Basic Constructor
 * @param textureData
 * @param textureDataSize
 * @param textureWidth
 * @param textureHeight
 */
Texture::Texture(unsigned char* textureData , unsigned int  textureDataSize ,
                 unsigned int textureWidth , unsigned int textureHeight)
{
    width = textureWidth;
    height = textureHeight;
    byteCount = width*height*bytesPerPixel;
    dataSize = textureDataSize;
    data = textureData;
    frames = dataSize / byteCount;
}

/**
 * generates a texture frame as unique image data
 * @param frameNumber
 * @return
 */
unsigned char* Texture::renderFrame(unsigned int frameNumber)
{
    unsigned char* r;

    r = (unsigned char*) malloc (byteCount);

    int i = -1;
    int startByte = byteCount * frameNumber;
    if(startByte+byteCount>dataSize)
    {
        // error state -> return first frame
        startByte = 0;
    }
    while(++i<byteCount)
    {
        r[i] = data[startByte+i];
    }
    return r;
}