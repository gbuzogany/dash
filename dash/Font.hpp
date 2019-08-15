//
//  Font.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 14/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp

#include <stdio.h>
#include "Shader.hpp"

struct Character {
    GLuint     textureID;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
};

class FontWrapper {
    void addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode);
public:
    std::map<GLchar, Character> characters;
    FontWrapper(FT_Face &face, int size);
};

#endif /* Font_hpp */
