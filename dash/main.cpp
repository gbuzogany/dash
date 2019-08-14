#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <exception>
#include <functional>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#define GL_GLEXT_PROTOTYPES 1
//#include <SDL2/SDL_opengles2.h>
#include <GLES2/gl2.h>

#include "Renderer.hpp"
#include "Texture.hpp"

int main(int argc, char* argv[])
{
    Renderer* r = new Renderer();
    r->initGraphics();
    r->initShaders();
    
//    FT_Library ft;
//
//    if (FT_Init_FreeType(&ft)) {
//        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//        return 1;
//    }
//
//    std::string fontFullPath(realpath(".", NULL));
//    fontFullPath.append("/hnpro-medium-condensed.ttf");
//
//    FT_Face face;
//    if (FT_New_Face(ft, fontFullPath.c_str(), 0, &face)) {
//        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//        return 1;
//    }
    
//    Font font(face, 18);
    
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = r->modelProgram->getId();
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    // Get a handle for our buffers
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
    

//    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.001f, 100.0f);
    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f); // In world coordinates
    
    // Camera matrix
    glm::mat4 View = glm::lookAt(
                                 glm::vec3(0, 0, 1), // Camera is at (4,1,3), in World Space
                                 glm::vec3(0, 0, 0), // and looks at the origin
                                 glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
                                 );
    
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    
    // Transform for Model
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    
    GLuint Texture = Texture::loadBMP("uvtemplate.bmp");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    
    vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    vertices.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
    vertices.push_back(glm::vec3(-1.0f,  1.0f, 0.0f));
    vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    vertices.push_back(glm::vec3( 1.0f, -1.0f, 0.0f));
    vertices.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
    
    uvs.push_back(glm::vec2(0.0f, 0.0f));
    uvs.push_back(glm::vec2(1.0f, 1.0f));
    uvs.push_back(glm::vec2(0.0f, 1.0f));
    uvs.push_back(glm::vec2(0.0f, 0.0f));
    uvs.push_back(glm::vec2(1.0f, 0.0f));
    uvs.push_back(glm::vec2(1.0f, 1.0f));
    
    // Load it into a VBO
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glUseProgram(programID);

    int running = 1;
    while (running)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
                break;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//        r->renderText(font, "Test", 0, 0, 1, glm::vec3(255, 255, 255));

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);
    
        
        Model = translationMatrix * rotationMatrix * scalingMatrix;

        glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glUniform1i(TextureID, 0);
        
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              vertexPosition_modelspaceID, // The attribute we want to configure
                              3, // size
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
                              );
        
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              vertexUVID, // The attribute we want to configure
                              2, // size : U+V => 2
                              GL_FLOAT, // type
                              GL_FALSE, // normalized?
                              0, // stride
                              (void*)0 // array buffer offset
                              );

        glDrawArrays(GL_TRIANGLES, 0, (int) vertices.size() );
        
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        
        SDL_Delay(1000.0f / 60.0f);
        
        r->updateScreen();
    }

    SDL_Quit();
    
    return 0;
}
