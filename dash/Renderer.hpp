//
//  Renderer.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#include "ShaderProgram.hpp"

class Renderer {
private:
    SDL_Window *window;
    SDL_GLContext context;
    ShaderProgram *shaderProgram;
public:
    Renderer();
    GLuint loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath);
    void initGraphics();
    void updateScreen();
};

#endif /* Renderer_hpp */
