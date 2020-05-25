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
    
    dissolveProgram = new RawShaderProgram("rkt/etc/shaders/DissolveVertex.glsl", "rkt/etc/shaders/DissolveFragment.glsl");
    
    splashFire = new ShaderProgram("rkt/etc/shaders/dashVertex.glsl", "rkt/etc/shaders/dashFragment.glsl", "rkt/etc/shaders/splashUniforms.json");
    
    baseTex = Texture::loadTGA("rkt/etc/textures/dash.tga");
    maskTex = Texture::loadTGA("rkt/etc/textures/splash_mask.tga");
    FX1FlowTex = Texture::loadTGA("rkt/etc/textures/flow_tunnel.tga");
    FX1Tex = Texture::loadTGA("rkt/etc/textures/splash.tga");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    splashFire->setMat4Uniform("projection", projection);
    splashFire->setTextureUniform("baseTexture", baseTex);
    splashFire->setTextureUniform("maskTex", maskTex);
    splashFire->setTextureUniform("FX1Texture", FX1Tex);
    splashFire->setTextureUniform("FX1FlowTexture", FX1FlowTex);
    
    splashFire->setVec4Uniform("FX1Color", glm::vec4(1.0, 0.407, 0.0, 1.0));
}

Splash::~Splash() {
    Texture::destroyTexture(splashLogo);
    Texture::destroyTexture(dissolveRampTextureId);
    Texture::destroyTexture(dissolveNoiseTextureId);
    
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

void Splash::setupDissolve(GLuint textureId) {
    _r->useProgram(*dissolveProgram);
    _r->setProgramGlobalAlpha(*dissolveProgram);
    
    GLuint u_baseTexture = dissolveProgram->getUniformLocation("baseTexture");
    GLuint u_noiseTexture = dissolveProgram->getUniformLocation("noiseTexture");
    GLuint u_rampTexture = dissolveProgram->getUniformLocation("rampTexture");
    GLuint u_projection = dissolveProgram->getUniformLocation("projection");
    GLuint u_dissolve = dissolveProgram->getUniformLocation("dissolve");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_baseTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    _r->bindTexture(textureId);
    
    glUniform1i(u_noiseTexture, 1);
    glActiveTexture(GL_TEXTURE1);
    _r->bindTexture(dissolveNoiseTextureId);
    
    glUniform1i(u_rampTexture, 2);
    glActiveTexture(GL_TEXTURE2);
    _r->bindTexture(dissolveRampTextureId);
    
    glUniform1f(u_dissolve, dissolve);
}

void Splash::render() {
    _r->clear();
    
    splashFire->setFloatUniform("time", _r->getTotalTime() / 20.0f);
    splashFire->use(_r);
    _r->setGlobalAlpha();
    _r->renderRect(0, 0, WIDTH, HEIGHT, true);
    
    setupDissolve(splashLogo);
    
    float width = 500;
    float height = 500;
    
    _r->renderRect(WIDTH/2.0f - width/2.0f, HEIGHT/2.0f - height/2.0f, width, height, true);
}

void Splash::renderFixed() {
    
}
