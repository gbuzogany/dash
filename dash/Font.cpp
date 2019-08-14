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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font.hpp"

void Font::addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode) {
    // Load character glyph
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }

    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 GL_ALPHA,
                 face->glyph->bitmap.width,
                 face->glyph->bitmap.rows,
                 0,
                 GL_ALPHA,
                 GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer
                 );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint) face->glyph->advance.x
    };
    characters.insert(std::pair<GLchar, Character>(charCode, character));
}

Font::Font(FT_Face &face, int size) {
    FT_Set_Pixel_Sizes(face, 0, size);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    
    for (GLubyte c = 0; c < 177; c++)
    {
        addCharFromCharCode(face, size, c);
    }

}
