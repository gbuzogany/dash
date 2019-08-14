//
//  Renderer.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <stdio.h>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "ShaderProgram.hpp"
#include "Font.hpp"

class Renderer {
private:
    SDL_GLContext context;
    
    GLuint VAO, VBO;
public:
    ShaderProgram *modelProgram;
    ShaderProgram *textProgram;
    
    SDL_Window *window;
    Renderer();
    ShaderProgram* loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath);
    void initGraphics();
    void updateScreen();
    void renderText(Font &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

#endif /* Renderer_hpp */
