//
//  Splash.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Splash.hpp"
#include "MediaPlayer.hpp"
#include "DashControl.hpp"
#include <thread>
#include <functional>
#include <memory>

Splash::Splash(Renderer &renderer) : Scene(renderer) {
    dissolveRampTextureId = Texture::loadTGA("dash/etc/textures/dissolve-ramp.tga");
    dissolveNoiseTextureId = Texture::loadTGA("dash/etc/textures/noise.tga");
    splashLogo = Texture::loadTGA("dash/etc/textures/logo.tga");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 1.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 0.5));
    animationQueue.push(new Animation("dissolve", 0, 1.0, 2.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 1.0));
}

bool Splash::render(float delta) {
    totalTime += delta;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (!animationQueue.empty()) {
        Animation *current = animationQueue.front();
        float value = current->animate(delta);
        
        if (current->getId() == "fadeIn") {
            r->setGlobalAlpha(value);
        }
        if (current->getId() == "dissolve") {
            dissolve = value;
        }
        
        if (current->complete()) {
            animationQueue.pop();
            delete current;
        }
    }
    else {
        return false;
    }
    
    r->useProgram(*r->dissolveProgram);
    r->setProgramGlobalAlpha(*r->dissolveProgram);

    GLuint u_baseTexture = r->dissolveProgram->getUniformLocation("baseTexture");
    GLuint u_noiseTexture = r->dissolveProgram->getUniformLocation("noiseTexture");
    GLuint u_rampTexture = r->dissolveProgram->getUniformLocation("rampTexture");
    GLuint u_projection = r->dissolveProgram->getUniformLocation("projection");
    GLuint u_dissolve = r->dissolveProgram->getUniformLocation("dissolve");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_baseTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    r->bindTexture(splashLogo);
    
    glUniform1i(u_noiseTexture, 1);
    glActiveTexture(GL_TEXTURE1);
    r->bindTexture(dissolveNoiseTextureId);
    
    glUniform1i(u_rampTexture, 2);
    glActiveTexture(GL_TEXTURE2);
    r->bindTexture(dissolveRampTextureId);
    
    glUniform1f(u_dissolve, dissolve);

//    r->useProgram(r->fractalBackgroundProgram->getId());
//    GLuint u_color = r->fractalBackgroundProgram->getUniformLocation("color");
//
//    glUniform3f(u_color, 0.06, 0.06, 0.06);
    r->renderRect(10, -170, 800, 800, true);
    
    return true;
}

void Splash::renderFixed() {
}
