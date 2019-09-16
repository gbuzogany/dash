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
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
}

void Renderer::initShaders() {
    textureProgram = loadShaders( "TransformVertexShader.glsl", "TextureFragmentShader.glsl" );
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
    
    window = SDL_CreateWindow("ANGLE", 100, 100, 800, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    assert(window);
    
    context = SDL_GL_CreateContext(window);
    assert(context);
    
    assert(SDL_GL_MakeCurrent(window, context) == 0);
    SDL_GL_SetSwapInterval(1);
    SDL_ShowCursor(SDL_DISABLE);
    
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("Started with GLSL %s\n",  glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGenBuffers(1, &vertexbuffer);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

}

void Renderer::updateScreen() {
    SDL_GL_SwapWindow(window);
}

void Renderer::startFrame() {
    if (!startTime) {
        // get the time in ms passed from the moment the program started
        startTime = SDL_GetTicks();
    } else {
        delta = endTime - startTime; // how many ms for a frame
    }
    
    if (delta < timePerFrame) {
        SDL_Delay(timePerFrame - delta);
    }
    
    if (delta > timePerFrame) {
        fps = 1000 / delta;
    }
}

void Renderer::endFrame() {
    startTime = endTime;
    endTime = SDL_GetTicks();
}

short Renderer::getFrameRate() {
    return fps;
}

void Renderer::renderTexture(GLuint textureId, GLfloat x, GLfloat y, GLfloat width, GLfloat height) {

    GLuint textureProgramId = textureProgram->getId();
    GLuint u_squareTextureId = glGetUniformLocation(textureProgramId, "textureSampler");
    
    GLuint u_projectionID = glGetUniformLocation(textureProgramId, "projection");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_squareTextureId, 0);
    glActiveTexture(GL_TEXTURE0);
    bindTexture(textureId);
    
    GLfloat xpos = x;
    GLfloat ypos = 480.0 - y - height;
    GLfloat vertices[6][4] = {
        { xpos,         ypos + height,   0.0, 1.0 }, // 0
        { xpos,         ypos,       0.0, 0.0 },      // 1
        { xpos + width, ypos,       1.0, 0.0 },      // 2
        
        { xpos,         ypos + height,   0.0, 1.0 }, // 3
        { xpos + width, ypos,       1.0, 0.0 },      // 4
        { xpos + width, ypos + height,   1.0, 1.0 }  // 5
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, &vertices[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
}

void Renderer::bindTexture(GLuint texId) {
    if (lastTexture != texId) {
        glBindTexture(GL_TEXTURE_2D, texId);
        lastTexture = texId;
    }
}

float Renderer::renderText(FontWrapper &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
    } coords[6 * text.length()];
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLuint programId = textProgram->getId();
    
    GLuint uTexID = glGetUniformLocation(programId, "tex");
    GLuint uProjectionID = glGetUniformLocation(programId, "projection");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    glUniformMatrix4fv(uProjectionID, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(uTexID, 0);
    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    
    // Iterate through all characters
    std::string::const_iterator c;
    FT_ULong previous = NULL;
    
    bindTexture(font.texture);
    
    int n = 0;
    
    for (c = text.begin(); c != text.end(); c++)
    {
        long kerning = 0;
        Character ch = font.characters[*c];

        // hardcoded kerning instead of using GPOS table
        if ((*c == 'e' || *c == 'o') && previous == 'T'){
            kerning = 2.0f;
        }
        previous = *c;

        x -= kerning;
        
        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = 480.0f - y - (ch.size.y - ch.bearing.y) * scale;
        
        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        coords[n++] = (point){xpos,     ypos + h,   ch.texCoords.x / font.texSize, ch.texCoords.y / font.texSize};
        coords[n++] = (point){xpos,     ypos,       ch.texCoords.x / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};
        coords[n++] = (point){xpos + w, ypos,       (ch.texCoords.x + ch.size.x) / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};

        coords[n++] = (point){xpos,     ypos + h,   ch.texCoords.x / font.texSize, ch.texCoords.y / font.texSize};
        coords[n++] = (point){xpos + w, ypos,       (ch.texCoords.x + ch.size.x) / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};
        coords[n++] = (point){xpos + w, ypos + h,   (ch.texCoords.x + ch.size.x) / font.texSize, ch.texCoords.y / font.texSize};

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0, // The attribute we want to configure
                          4, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          4 * sizeof(GLfloat), // stride
                          0 // array buffer offset
                          );
    
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, n);
    
    glDisableVertexAttribArray(0);
    bindTexture(0);
    
    return x;
}

Renderer::~Renderer() {
    SDL_GL_DeleteContext(context);
}
