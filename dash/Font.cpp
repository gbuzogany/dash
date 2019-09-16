//
//  Font.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 14/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#include <map>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font.hpp"

void FontWrapper::addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode, int x, int y) {
    FT_GlyphSlot glyph = face->glyph;
    
    // Load character glyph
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, glyph->bitmap.width, glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
}

int FontWrapper::closestPowerOf2(int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

FontWrapper::FontWrapper(FT_Face &face, int size) {
    FT_Set_Pixel_Sizes(face, 0, size);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    
    for (GLubyte c = 0; c < 177; c++)
    {
        loadCharProperties(face, size, c);
    }
    
    
    
    int numChars = ceil(sqrt(177));
    
    int texWidth = closestPowerOf2(numChars * maxWidth);
    int texHeight = closestPowerOf2(numChars * maxHeight);
    
    if (texWidth > texHeight) {
        texSize = texWidth;
    }
    else {
        texSize = texHeight;
    }
    
    printf("%d, %d -> %f, %f\n", maxWidth, maxHeight, texSize, texSize);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texSize, texSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
    
    int x = 0;
    int y = 0;
    
    for (GLubyte c = 0; c < 177; c++)
    {
        characters[c].texCoords = glm::ivec2(x, y);
        addCharFromCharCode(face, size, c, x, y);
        x += maxWidth;
        if (x + maxWidth >= texWidth) {
            x = 1;
            y += maxHeight;
        }
        if (y > texHeight) {
            printf("Error: Font doesn't fit in texture.");
        }
    }
}

void FontWrapper::loadCharProperties(FT_Face &face, int size, FT_ULong charCode) {
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    if (face->glyph->bitmap.width > maxWidth) {
        maxWidth = face->glyph->bitmap.width;
    }
    if (face->glyph->bitmap.rows > maxHeight) {
        maxHeight = face->glyph->bitmap.rows;
    }
    
    Character character = {
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint) face->glyph->advance.x,
        glm::ivec2(0, 0)
    };
    characters.insert(std::pair<GLchar, Character>(charCode, character));
}
