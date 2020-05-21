//
//  Dashboard.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include <thread>
#include <functional>
#include <memory>
#define _USE_MATH_DEFINES
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "MainScene.hpp"

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

MainScene::MainScene(Renderer *renderer, RocketteServiceImpl *service) : Scene(renderer, service) {
    arcTextureId = Texture::loadTGA("rkt/etc/textures/radial.tga");
    fasterTexture = Texture::loadTGA("rkt/etc/textures/faster.tga");
    
    FontWrapper::loadFontFace(_r, "hnpro", "rkt/etc/fonts/hnpro-medium-condensed.otf");
    FontWrapper::loadFontFace(_r, "hnpro-italic", "rkt/etc/fonts/hnpro-medium-condensed-oblique.otf");
    FontWrapper::loadFontFace(_r, "hnpro-bold", "rkt/etc/fonts/hnpro-extra-black-condensed.otf");
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/'
    };
    
    std::vector<FT_ULong> largeChars = {
        '0','1','2','3','4','5','6','7','8','9','-','.'
    };

    hnproSmall = new FontWrapper("hnpro", 16, usedChars);
    hnproMedium27 = new FontWrapper("hnpro", 26, usedChars);
    hnproHuge = new FontWrapper("hnpro", 150, largeChars);
    hnproMediumOblique = new FontWrapper("hnpro-italic", 36, usedChars);
    hnproHugeOblique = new FontWrapper("hnpro-italic", 100, largeChars);
    hnproExtraHeavy36 = new FontWrapper("hnpro-bold", 36, usedChars);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 2.0));
    
    _r->createFramebuffer(frameBuffer, screenTexture, WIDTH, HEIGHT);
}

bool MainScene::update(float delta) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        int key = ev.key.keysym.sym;
        if (ev.type == SDL_QUIT || (ev.type == SDL_KEYUP && key == 'q'))
        {
            exit(0);
            break;
        }
    }
    
    if (!animationQueue.empty()) {
        Animation *current = animationQueue.front();
        float value = current->animate(delta);
        
        if (current->getId() == "fadeIn") {
            _r->setGlobalAlpha(value);
        }
        
        if (current->complete()) {
            animationQueue.pop();
            delete current;
        }
    }
    
    return true;
}

void MainScene::render() {
    _r->clear();
    _r->renderTexture(screenTexture, 0, 0, WIDTH, HEIGHT);
  
    std::string speed = "";
    _service->getFloatValueAsString("speed", speed);
    
    _r->renderText(*hnproHuge, speed, 270.0f, 200.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << _r->getFrameRate();
    _r->renderText(*hnproMedium27, sfps.str(), 0.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void MainScene::renderFixed() {
    _r->bindFramebuffer(frameBuffer);
    _r->clear();

    _r->bindFramebuffer(0);
    _r->setGlobalAlpha(0.0);
}
