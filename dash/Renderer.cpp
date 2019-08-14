//
//  Renderer.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Renderer.hpp"
#include <assert.h>
#include <iostream>

Renderer::Renderer()
{

}

void Renderer::initShaders() {
    modelProgram = loadShaders( "TransformVertexShader.glsl", "TextureFragmentShader.glsl" );
    textProgram = loadShaders( "TextVertex.glsl", "TextFragment.glsl" );
}

ShaderProgram* Renderer::loadShaders(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    ShaderProgram *program = new ShaderProgram();
    Shader *vertex = new Shader();
    Shader *fragment = new Shader();
    
    vertex->loadVertexShader(vertexShaderPath);
    fragment->loadFragmentShader(fragmentShaderPath);
    program->create(vertex, fragment);
    assert(glGetError() == 0);
    glUseProgram(program->getId());
    assert(glGetError() == 0);
    return program;
}

void Renderer::initGraphics()
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    
#if defined(_WIN32) || defined(__MACOSX__)
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1"); // Force SDL to use ANGLE for it's OpenGLES2 implementation
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    
    window = SDL_CreateWindow("ANGLE", 100, 100, 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    assert(window);
    
    context = SDL_GL_CreateContext(window);
    assert(context);
    
    assert(SDL_GL_MakeCurrent(window, context) == 0);
    SDL_GL_SetSwapInterval(1);
    
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("Started with GLSL %s\n",  glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGenVertexArraysOES(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArrayOES(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArrayOES(0);
}

void Renderer::updateScreen() {
    SDL_GL_SwapWindow(window);
}

void Renderer::renderText(Font &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLuint programId = textProgram->getId();
    
    GLuint uTexID = glGetUniformLocation(programId, "tex");
    GLuint uProjectionID = glGetUniformLocation(programId, "projection");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 640.0f);
    glUniformMatrix4fv(uProjectionID, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(uTexID, 0);
    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArrayOES(VAO);
    
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = font.characters[*c];
        
        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
        
        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArrayOES(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::~Renderer() {
    SDL_GL_DeleteContext(context);
}
