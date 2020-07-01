#include "Splash.hpp"
#include <functional>
#include <memory>

Splash::Splash(Renderer *renderer, RocketteServiceImpl *service) : Scene(renderer, service) {
    
    dissolveRampTextureId = Texture::loadTGA("rkt/etc/textures/dissolve-ramp.tga");
    dissolveNoiseTextureId = Texture::loadTGA("rkt/etc/textures/noise.tga");
    splashLogo = Texture::loadTGA("rkt/etc/textures/logo.tga");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 0.5));
    animationQueue.push(new Animation("delay", 0, 1.0, 0.5));
    animationQueue.push(new Animation("dissolve", 0, 1.0, 2.0));
    animationQueue.push(new Animation("fadeOut", 1.0, 0.0, 0.5));
    
    baseTex = Texture::loadTGA("rkt/etc/textures/blank.tga");
    maskTex = Texture::loadTGA("rkt/etc/textures/splash_mask.tga");
    FX1FlowTex = Texture::loadTGA("rkt/etc/textures/flow_tunnel.tga");
    FX1Tex = Texture::loadTGA("rkt/etc/textures/splash.tga");
    
    splashFire = new ShaderProgram("rkt/etc/shaders/vfxVertex.glsl", "rkt/etc/shaders/vfxFragment.glsl", "rkt/etc/shaders/splashUniforms.json");
    dissolveProgram = new ShaderProgram("rkt/etc/shaders/DissolveVertex.glsl", "rkt/etc/shaders/DissolveFragment.glsl", "rkt/etc/shaders/dissolveUniforms.json");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    splashFire->setMat4Uniform("projection", projection);
    splashFire->setTextureUniform("baseTexture", baseTex);
    splashFire->setTextureUniform("maskTex", maskTex);
    splashFire->setTextureUniform("FX1Texture", FX1Tex);
    splashFire->setTextureUniform("FX1FlowTexture", FX1FlowTex);
    splashFire->setVec4Uniform("FX1Color", glm::vec4(1.0, 0.407, 0.0, 1.0));
    
    dissolveProgram->setMat4Uniform("projection", projection);
    dissolveProgram->setTextureUniform("baseTexture", splashLogo);
    dissolveProgram->setTextureUniform("noiseTexture", dissolveNoiseTextureId);
    dissolveProgram->setTextureUniform("rampTexture", dissolveRampTextureId);
}

Splash::~Splash() {
    Texture::destroyTexture(splashLogo);
    Texture::destroyTexture(dissolveRampTextureId);
    Texture::destroyTexture(dissolveNoiseTextureId);
    
    Texture::destroyTexture(baseTex);
    Texture::destroyTexture(maskTex);
    Texture::destroyTexture(FX1FlowTex);
    Texture::destroyTexture(FX1Tex);
    
    delete dissolveProgram;
}

bool Splash::update(float delta) {
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
        if (current->getId() == "dissolve") {
            dissolve = value;
        }
        if (current->getId() == "fadeOut") {
            _r->setGlobalAlpha(value);
        }
        if (current->complete()) {
            animationQueue.pop();
            delete current;
        }
    }
    else {
        return false;
    }
    
    return true;
}

void Splash::render() {
    _r->clear();
    
    splashFire->setFloatUniform("time", _r->getTotalTime() / 20.0f);
    splashFire->use(_r);
    _r->setGlobalAlpha();
    _r->renderRect(0, 0, WIDTH, HEIGHT, true);
    
    dissolveProgram->setFloatUniform("dissolve", dissolve);
    dissolveProgram->use(_r);
    _r->setGlobalAlpha();
    
    float width = 600;
    float height = 600;
    
    _r->renderRect(WIDTH/2.0f - width/2.0f, HEIGHT/2.0f - height/2.0f, width, height, true);
}

void Splash::renderFixed() {
    
}
