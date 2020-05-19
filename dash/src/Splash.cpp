//
//  Splash.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Splash.hpp"
#include <functional>
#include <memory>

Splash::Splash(Renderer *renderer, DashServiceImpl *service) : Scene(renderer, service) {
    splashLogo = Texture::loadTGA("dash/etc/textures/logo.tga");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 1.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 0.5));
    animationQueue.push(new Animation("dissolve", 0, 1.0, 1.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 1.0));
}

bool Splash::render(float delta) {
    totalTime += delta;

    _r->clear();
    
    if (!animationQueue.empty()) {
        Animation *current = animationQueue.front();
        float value = current->animate(delta);
        
        if (current->getId() == "fadeIn") {
            _r->setGlobalAlpha(value);
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
    
    _r->useProgram(*_r->dissolveProgram);
    _r->setProgramGlobalAlpha(*_r->dissolveProgram);

    GLuint u_baseTexture = _r->dissolveProgram->getUniformLocation("baseTexture");
    GLuint u_noiseTexture = _r->dissolveProgram->getUniformLocation("noiseTexture");
    GLuint u_rampTexture = _r->dissolveProgram->getUniformLocation("rampTexture");
    GLuint u_projection = _r->dissolveProgram->getUniformLocation("projection");
    GLuint u_dissolve = _r->dissolveProgram->getUniformLocation("dissolve");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_baseTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    _r->bindTexture(splashLogo);
    
    glUniform1i(u_noiseTexture, 1);
    glActiveTexture(GL_TEXTURE1);
    _r->bindTexture(dissolveNoiseTextureId);
    
    glUniform1i(u_rampTexture, 2);
    glActiveTexture(GL_TEXTURE2);
    _r->bindTexture(dissolveRampTextureId);
    
    glUniform1f(u_dissolve, dissolve);

    _r->renderRect(10, -170, 800, 800, true);
    
    return true;
}

void Splash::renderFixed() {
}
