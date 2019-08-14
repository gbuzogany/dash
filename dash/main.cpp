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
#include <sstream>
#include <iomanip>

#include "Renderer.hpp"
#include "Texture.hpp"

int main(int argc, char* argv[])
{
    Renderer* r = new Renderer();
    r->initGraphics();
    r->initShaders();
    
    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return 1;
    }

//    std::string fontFullPath(realpath(".", NULL));
//    fontFullPath.append("/hnpro-medium-condensed.ttf");

    FT_Face face, faceItalic, faceBold;
    if (FT_New_Face(ft, "hnpro-medium-condensed.otf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return 1;
    }
    if (FT_New_Face(ft, "hnpro-medium-condensed-oblique.otf", 0, &faceItalic)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return 1;
    }
    if (FT_New_Face(ft, "hnpro-extra-black-condensed.otf", 0, &faceBold)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return 1;
    }
    
    Font hnproMedium27(face, 26);
    Font hnproHuge(face, 240);
    Font hnproMediumOblique(faceItalic, 36);
    Font hnproHugeOblique(faceItalic, 250);
    Font hnproExtraHeavy36(faceBold, 36);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    GLuint modelProgramID = r->modelProgram->getId();
    GLuint textProgramID = r->textProgram->getId();
    
    GLuint MatrixID = glGetUniformLocation(modelProgramID, "MVP");
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(modelProgramID, "vertexPosition_modelspace");
    GLuint vertexUVID = glGetAttribLocation(modelProgramID, "vertexUV");
    GLuint TextureID = glGetUniformLocation(modelProgramID, "myTextureSampler");
    
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

    float speed = 0;
    float temp = 20;

    int running = 1;
    while (running)
    {
        speed += 0.2;
        temp += 0.1;
        
        if (speed > 299) {
            speed = 0;
        }
        
        if (temp > 100) {
            temp = 30;
        }
        
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
//
//        // render 3d plane
//        glUseProgram(r->modelProgram->getId());
//
//        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
//        glm::mat4 rotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
//        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);
//
//
//        Model = translationMatrix * rotationMatrix * scalingMatrix;
//
//        glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
//
//        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, Texture);
//        glUniform1i(TextureID, 0);
//
//        glEnableVertexAttribArray(vertexPosition_modelspaceID);
//        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//        glVertexAttribPointer(
//                              vertexPosition_modelspaceID, // The attribute we want to configure
//                              3, // size
//                              GL_FLOAT, // type
//                              GL_FALSE, // normalized?
//                              0, // stride
//                              (void*)0 // array buffer offset
//                              );
//
//        glEnableVertexAttribArray(vertexUVID);
//        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//        glVertexAttribPointer(
//                              vertexUVID, // The attribute we want to configure
//                              2, // size : U+V => 2
//                              GL_FLOAT, // type
//                              GL_FALSE, // normalized?
//                              0, // stride
//                              (void*)0 // array buffer offset
//                              );
//
//        glDrawArrays(GL_TRIANGLES, 0, (int) vertices.size() );
//
//        glDisableVertexAttribArray(vertexPosition_modelspaceID);
//        glDisableVertexAttribArray(vertexUVID);

        
        // text
        glUseProgram(r->textProgram->getId());
        
        float endX;
        std::string tempStr(1, '\xb0');
        tempStr.append("C");
        
//        std::stringstream ss;
//        ss << std::fixed << std::setprecision(0) << speed;
//        std::string speedStr = ss.str();
        
        std::stringstream tempSs;
        tempSs << std::fixed << std::setprecision(1) << temp;
        std::string coolantTempStr = tempSs.str();
        
        endX = r->renderText(hnproMedium27, "Coolant Temp", 27.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, coolantTempStr, endX + 5.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMedium27, tempStr, endX + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "Air Intake Temp", 27.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "100.0", endX + 5.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMedium27, tempStr, endX + 3.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "Manifold Pressure", 27.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "12.5", endX + 5.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "kPA", endX + 3.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "TPS", 564.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "100", endX + 3.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "%", endX + 3.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "Battery Voltage", 140.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "12.5", endX + 5.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "V", endX + 3.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "Max Power @", 512.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "67", endX + 5.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMedium27, "kW", endX + 3.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproMedium27, "Max Torque @", 509.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "40", endX + 5.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMedium27, "Nm", endX + 3.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        endX = r->renderText(hnproExtraHeavy36, "10000", 553.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMedium27, "RPM", endX + 5.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        r->renderText(hnproHugeOblique, "-", 530.0f, 284.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        std::stringstream ss;
        ss << std::setw(3) << std::setfill(' ') << std::fixed << std::setprecision(0) << speed;
        std::string speedStr = ss.str();
        
        r->renderText(hnproHuge, speedStr, 69.0f, 323.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        r->renderText(hnproMediumOblique, "km/h", 330.0f, 363.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        
        SDL_Delay(1000.0f / 60.0f);
        
        r->updateScreen();
    }

    SDL_Quit();
    
    return 0;
}
