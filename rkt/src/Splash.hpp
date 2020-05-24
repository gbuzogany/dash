#ifndef Splash_hpp
#define Splash_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "Definitions.h"
#include "Scene.hpp"
#include "Animation.hpp"
#include "ShaderProgram.hpp"

class Splash : Scene {
    GLuint dissolveRampTextureId;
    GLuint dissolveNoiseTextureId;
    GLuint splashLogo;
    
    GLuint baseTex;
    GLuint maskTex;
    GLuint FX1Tex;
    GLuint FX1FlowTex;
    
    ShaderProgram *splashFire;

    float dissolve = 0;
    
    RawShaderProgram *dissolveProgram;

    std::queue<Animation*> animationQueue;
    
    void setupDissolve(GLuint textureId);
    
    ~Splash();
public:
    Splash(Renderer *r, RocketteServiceImpl *service);
    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* Splash_hpp */
