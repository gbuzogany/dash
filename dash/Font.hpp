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
#include <vector>

struct Character {
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
    glm::ivec2 texCoords;
};

class FontWrapper {
    void addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode, int x, int y);
    void loadCharProperties(FT_Face &face, int size, FT_ULong charCode);
    int closestPowerOf2(int n);
public:
    int maxWidth = 0;
    int maxHeight = 0;
    
    float texSize;
    int fontSize;
    
    GLuint texture;
    
    int getFontSize();
    
    std::map<GLchar, Character> characters;
    FontWrapper(FT_Face &face, int size, std::vector<FT_ULong> charList);
};

#endif /* Font_hpp */
