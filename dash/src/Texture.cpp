//
//  Texture.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Texture.hpp"
#include <GLES2/gl2.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLuint Texture::loadBMP(const char * imagepath){
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    unsigned char * data;

    FILE * file = fopen(imagepath,"rb");
    if (!file) {
        printf("Could not be open file: %s.\n", imagepath);
        return 0;
    }
    
    // Read the header, i.e. the 54 first bytes
    
    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54){
        printf("Invalid BMP file\n");
        return 0;
    }

    // check magic bytes
    if (header[0]!='B' || header[1]!='M'){
        printf("Invalid BMP file\n");
        return 0;
    }

    int color = header[0x1E];
    int bpp = header[0x1C];
    if (color != 0) {
        printf("Invalid BMP file\n");
        return 0;
    }
    
    if (bpp != 24) {
        printf("Expecting a 24bpp file\n");
        return 0;
    }
    
    // Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    if (imageSize == 0) {
        imageSize= width * height * 3; // RGB
    }
    if (dataPos == 0) {
        dataPos = 54; // BMP header
    }

    data = new unsigned char [imageSize];
    fread(data,1,imageSize,file);
    fclose (file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    delete [] data;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}

GLuint Texture::loadTGA(const char * imagepath) {
    
    int width, height, channels;
    unsigned char *image = stbi_load(imagepath, &width, &height, &channels, STBI_rgb_alpha);
    if (image == NULL) {
        printf("Could not be open file: %s.\n", imagepath);
        return 0;
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    delete [] image;
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return textureID;
}
