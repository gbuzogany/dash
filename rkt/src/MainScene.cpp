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
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/', '!'
    };
    
    dashIcons = DashIcons::getInstance();
    dashIcons->loadIcons("rkt/etc/textures/icons.json");

    roboto = new FontWrapper("Roboto-Regular", 50, usedChars);
    robotoSmall = new FontWrapper("Roboto-Regular", 20, usedChars);
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 2.0));
    
    _r->createFramebuffer(frameBuffer, screenTexture, WIDTH, HEIGHT);
}

MainScene::~MainScene() {
    delete roboto;
    delete robotoSmall;
}

bool MainScene::update(float delta) {
    totalTime += delta;
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
    
    // render to texture
    _r->bindFramebuffer(frameBuffer);
    _r->clear();
  
    std::string message = "";
    _service->getStringValue("message", message);
    
    dashIcons->renderIcon(_r, "maintenance", 0, 0, 0.5, glm::vec3(1.0, 0.0, 0.0));
    dashIcons->renderIcon(_r, "indicator-left", 62, 0, 0.5, glm::vec3(0.0, 1.0, 0.0));
    dashIcons->renderIcon(_r, "indicator-right", 124, 0, 0.5, glm::vec3(0.0, 1.0, 0.0));

    // apply blur to screentexture, get id of texture blurred as return value
    GLuint tex = _r->blurTexture(screenTexture, 0.004);

    // render to screen
    _r->bindFramebuffer(0);
    // render blurred texture
    _r->renderTexture(tex, 0, 0, WIDTH, HEIGHT);

    // render again elements that were blurred
    dashIcons->renderIcon(_r, "maintenance", 0, 0, 0.5, glm::vec3(1.0, 0.0, 0.0));
    dashIcons->renderIcon(_r, "indicator-left", 62, 0, 0.5, glm::vec3(0.0, 1.0, 0.0));
    dashIcons->renderIcon(_r, "indicator-right", 124, 0, 0.5, glm::vec3(0.0, 1.0, 0.0));
    
    _r->renderText(*roboto, "Hello world!", WIDTH/2.0, HEIGHT/2.0, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER);
    _r->renderText(*robotoSmall, message, WIDTH/2.0, HEIGHT/2.0 + 30.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER);
    
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

void MainScene::drawNeedle(float value, float maxValue, GLint x, GLint y, GLfloat tipRadius, GLfloat bottomRadius, GLfloat startAngle, GLfloat endAngle) {
    GLfloat deltaAngle = 0;
    
    float valuePercent = (value - 1) / maxValue;
    
    if (startAngle > endAngle) {
        deltaAngle = endAngle - startAngle;
    }
    else {
        deltaAngle = (startAngle - endAngle) - startAngle;
    }
    
    GLfloat buffer[3 * 2]; // 3 vertices x y
    
    // tip of needle
    buffer[0] = tipRadius;
    buffer[1] = 0;
    
    // bottom upper
    buffer[2] = bottomRadius;
    buffer[3] = 5;
    
    // bottom lower
    buffer[4] = bottomRadius;
    buffer[5] = -5;
    
    float angle = startAngle + valuePercent * deltaAngle;
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    
    for (int i=0; i<6; i+=2) {
        // rotate all vertices around origin
        float px = buffer[i];
        float py = buffer[i+1];
        buffer[i]   = px * cosAngle - py * sinAngle;
        buffer[i+1] = px * sinAngle + py * cosAngle;
        
        buffer[i]   += x;
        buffer[i+1] += y;
    }
    
    GLuint uTextColor = _r->textProgram->getUniformLocation("textColor");
    glUniform3f(uTextColor, 1, 0, 0);
    
    GLuint vertexbuffer = _r->getVertexBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0, // The attribute we want to configure
                          2, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0, // stride
                          0 // array buffer offset
                          );
    
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

void MainScene::drawCounter(FontWrapper &font, GLfloat x, GLfloat y, GLfloat radius, GLfloat longTickLength, GLfloat shortTickLength, GLfloat startAngle, GLfloat endAngle, GLfloat maxValue, GLfloat beginCritical, GLint ticksBetweenInts) {
    
    GLuint vertexbuffer = _r->getVertexBuffer();
    
    GLint ticks = (maxValue - 1) * ticksBetweenInts + maxValue;
    GLint numberOfVertices = ticks * 2;
    std::vector<GLfloat> allCircleVertices(numberOfVertices * 2);
    GLfloat deltaAngle = 0;
    
    if (startAngle > endAngle) {
        deltaAngle = endAngle - startAngle;
    }
    else {
        deltaAngle = (startAngle - endAngle) - startAngle;
    }
    
    for ( int i = 0; i < ticks; i++)
    {
        GLfloat smallRadius = shortTickLength;
        if (i % (ticksBetweenInts + 1) == 0) {
            smallRadius = longTickLength;
            _r->renderText(font,
                           std::to_string(i/(ticksBetweenInts+1)+1),
                           x + ( (radius - smallRadius - 25) * cos(startAngle + i * (deltaAngle / ticks) ) ),
                           y + ( (radius - smallRadius - 25) * sin(startAngle + i * (deltaAngle / ticks) ) ),
                           1.0f,
                           glm::vec3(1.0f, 1.0f, 1.0f),
                           CENTER,
                           CENTER);
        }
        
        allCircleVertices.at(i * 4) = x + ( radius * cos(startAngle + i * (deltaAngle / ticks) ) );
        allCircleVertices.at(i * 4 + 1) = y + ( radius * sin(startAngle + i * (deltaAngle / ticks) ) );
        
        allCircleVertices.at(i * 4 + 2) = x + ( (radius - smallRadius) * cos(startAngle + i * (deltaAngle / ticks)) );
        allCircleVertices.at(i * 4 + 3) = y + ( (radius - smallRadius) * sin(startAngle + i * (deltaAngle / ticks)) );
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, allCircleVertices.size() * sizeof(GLfloat), &allCircleVertices.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0, // The attribute we want to configure
                          2, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0, // stride
                          0 // array buffer offset
                          );
    
    // Render quad
    glDrawArrays(GL_LINES, 0, numberOfVertices);
    
    glDisableVertexAttribArray(0);
}
