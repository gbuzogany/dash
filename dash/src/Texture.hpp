//
//  Texture.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

class Texture {
public:
    static GLuint loadBMP(const char * imagepath);
    static GLuint loadTGA(const char * imagepath);
};

#endif /* Texture_hpp */
