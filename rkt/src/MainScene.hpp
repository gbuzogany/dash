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
#include "SpriteMap.hpp"
#include "ShaderProgram.hpp"

class MainScene : Scene {
    GLuint screenTexture;
    GLuint frameBuffer;
    
    GLuint baseTex;
    GLuint maskTex;
    GLuint FX1Tex;
    GLuint FX1FlowTex;
    
    std::queue<Animation*> animationQueue;
    
    SpriteMap *dashIcons;
    ShaderProgram *vfxProgram;
    
    FontWrapper *roboto;
    FontWrapper *robotoThin;
    FontWrapper *robotoSmall;
    FontWrapper *robotoMedium;
    FontWrapper *robotoLarge;
    
    void createFramebuffer();

public:
    MainScene(Renderer *r, RocketteServiceImpl *service);
    ~MainScene();

    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* MainScene_hpp */
