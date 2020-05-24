#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include <iostream>
#include <ft2build.h>
#include <map>
#include <thread>
#include <queue>
#include FT_FREETYPE_H
#include "Scene.hpp"
#include "Definitions.h"
#include "Animation.hpp"
#include "Utils.hpp"
#include "DashIcons.hpp"

class MainScene : Scene {
    GLuint screenTexture;
    GLuint frameBuffer;
    
    GLuint dashMask;
    GLuint daskFX1FlowTex;
    GLuint dashFX1Tex;
    
    std::queue<Animation*> animationQueue;
    
    DashIcons *dashIcons;
    
    FontWrapper *roboto, *robotoSmall;
    
    void createFramebuffer();
    void drawCounter(FontWrapper &font, GLfloat x, GLfloat y, GLfloat radius, GLfloat longTickLength, GLfloat shortTickLength, GLfloat startAngle, GLfloat endAngle, GLfloat maxValue, GLfloat beginCritical, GLint ticksBetweenInts);
    void drawNeedle(float value, float maxValue, GLint x, GLint y, GLfloat tipRadius, GLfloat bottomRadius, GLfloat startAngle, GLfloat endAngle);
public:
    MainScene(Renderer *r, RocketteServiceImpl *service);
    ~MainScene();

    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* MainScene_hpp */
