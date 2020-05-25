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
    FontWrapper::loadFontFace(_r, "Roboto-Regular", "rkt/etc/fonts/Roboto-Regular.ttf");
    FontWrapper::loadFontFace(_r, "Roboto-Thin", "rkt/etc/fonts/Roboto-Thin.ttf");
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/', '!'
    };
    
    std::vector<FT_ULong> basicChars = {
        '0','1','2','3','4','5','6','7','8','9','-'
    };

    roboto = new FontWrapper("Roboto-Regular", 50, usedChars);
    robotoThin = new FontWrapper("Roboto-Thin", 40, usedChars);
    robotoSmall = new FontWrapper("Roboto-Regular", 20, usedChars);
    robotoMedium = new FontWrapper("Roboto-Regular", 130, basicChars);
    robotoLarge = new FontWrapper("Roboto-Regular", 200, basicChars);
    
    dashIcons = new SpriteMap("rkt/etc/textures/icons.json");
    
    baseTex = Texture::loadTGA("rkt/etc/textures/dash.tga");
    maskTex = Texture::loadTGA("rkt/etc/textures/dash_mask.tga");
    FX1FlowTex = Texture::loadTGA("rkt/etc/textures/flow_tunnel.tga");
    FX1Tex = Texture::loadTGA("rkt/etc/textures/splash.tga");
    
    vfxProgram = new ShaderProgram("rkt/etc/shaders/dashVertex.glsl", "rkt/etc/shaders/dashFragment.glsl", "rkt/etc/shaders/dashUniforms.json");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    vfxProgram->setMat4Uniform("projection", projection);
    vfxProgram->setTextureUniform("baseTexture", baseTex);
    vfxProgram->setTextureUniform("maskTex", maskTex);
    vfxProgram->setTextureUniform("FX1Texture", FX1Tex);
    vfxProgram->setTextureUniform("FX1FlowTexture", FX1FlowTex);
    vfxProgram->setVec4Uniform("FX1Color", glm::vec4(1.0, 0.407, 0.0, 1.0));
    
    _r->createFramebuffer(frameBuffer, screenTexture, WIDTH, HEIGHT);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 2.0));
}

MainScene::~MainScene() {
    delete roboto;
    delete robotoSmall;
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
    // render to texture
//    _r->bindFramebuffer(frameBuffer);
    _r->clear();
    
    float tps = 0;
    float rpm = 0;
    std::string gearString = "6";
    std::string speedString = "0";
    std::string rpmString = "0";
    std::string tempString = "100";
    
    _service->getFloatValue("tps", tps);
    _service->getFloatValue("rpm", rpm);
    _service->getFloatValueAsString("rpm", rpmString);
    _service->getStringValue("gear", gearString);
    _service->getFloatValueAsString("speed", speedString);
    _service->getFloatValueAsString("temp", tempString);
    
    tempString.append("\xb0");
    tempString.append("C");
    
    vfxProgram->use(_r);
    vfxProgram->setFloatUniform("gaugeValue", rpm / 11000.0f);
    vfxProgram->setFloatUniform("time", _r->getTotalTime() / 20.0f);

    _r->setGlobalAlpha();
    _r->renderRect(0, 0, WIDTH, HEIGHT, true);
    
    _r->renderText(*robotoMedium, gearString, 695, 35, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    _r->renderText(*robotoLarge, speedString, 450, 230, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);
    float pos = _r->renderText(*roboto, rpmString, 710, 430, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);
    _r->renderText(*robotoThin, "RPM", pos, 435, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    dashIcons->renderIcon(_r, "coolant-temp", 610, 370, 0.5, glm::vec3(1.0, 1.0, 1.0));
    _r->renderText(*roboto, tempString, 795, 380, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);

    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << _r->getFrameRate();
    _r->renderText(*robotoSmall, sfps.str(), 0.0f, HEIGHT, 1.0f, glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainScene::renderFixed() {
    _r->bindFramebuffer(frameBuffer);
    _r->clear();

    _r->bindFramebuffer(0);
    _r->setGlobalAlpha(0.0);
}
