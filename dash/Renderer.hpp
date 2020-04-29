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
#include "Texture.hpp"

enum {LEFT, CENTER, RIGHT, TOP, BOTTOM};

class Renderer {
private:
    SDL_GLContext context;
    GLuint vertexbuffer;
    GLuint VAO, VBO;
    
    GLuint lastTexture = -1;
    
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    Uint32 delta = 0;
    float fps = 60.0;
    Uint32 timePerFrame = 16; // miliseconds
public:
    FT_Library ft;

    ShaderProgram *textureProgram;
    ShaderProgram *ringArcProgram;
    ShaderProgram *ringTexArcProgram;
    ShaderProgram *textProgram;
    ShaderProgram *lineProgram;
    SDL_Window *window;
    
    Renderer();
    ~Renderer();
    
    void initGraphics();
    void initShaders();
    ShaderProgram* loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath);
    void updateScreen();
    
    void startFrame();
    void endFrame();
    short getFrameRate();
    
    GLuint getVertexBuffer();
    
    float renderText(FontWrapper &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, uint hAlign = LEFT, uint vAlign = BOTTOM);
    void renderTexture(GLuint textureId, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    
    void bindTexture(GLuint texId);
    
    void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLint numberOfSides);
    void drawRingArc(float value, float max, GLfloat x, GLfloat y, GLfloat outerRadius, GLfloat innerRadius, GLfloat startAngle, GLfloat endPercent, vec3 color);
    void drawRingArcTexture(float value, float max, GLfloat x, GLfloat y, GLfloat outerRadius, GLfloat innerRadius, GLfloat startAngle, GLfloat endPercent, GLint texId);
};

#endif /* Renderer_hpp */
