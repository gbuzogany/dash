//
//  Splash.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Splash_hpp
#define Splash_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "Definitions.h"
#include "Scene.hpp"
#include "Animation.hpp"

class Splash : Scene {
    GLuint dissolveRampTextureId;
    GLuint dissolveNoiseTextureId;
    GLuint splashLogo;

    float totalTime = 0;
    float dissolve = 0;
    
    ShaderProgram *dissolveProgram;

    std::queue<Animation*> animationQueue;
    
    void setupDissolve(GLuint textureId);

public:
    Splash(Renderer *r, RocketteServiceImpl *service);
    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* Splash_hpp */
