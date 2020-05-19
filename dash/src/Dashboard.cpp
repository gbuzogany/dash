//
//  Dashboard.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Dashboard.hpp"
#include <thread>
#include <functional>
#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

Dashboard::Dashboard(Renderer *renderer, DashServiceImpl *service) : Scene(renderer, service) {
    arcTextureId = Texture::loadBMP("dash/etc/textures/radial.bmp");
    fasterTexture = Texture::loadTGA("dash/etc/textures/faster.tga");
    
    vehicle = new Vehicle();
    
    Font::loadFontFace(_r, "hnpro", "dash/etc/fonts/hnpro-medium-condensed.otf");
    Font::loadFontFace(_r, "hnpro-italic", "dash/etc/fonts/hnpro-medium-condensed-oblique.otf");
    Font::loadFontFace(_r, "hnpro-bold", "dash/etc/fonts/hnpro-extra-black-condensed.otf");
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/'
    };
    
    std::vector<FT_ULong> largeChars = {
        'N','0','1','2','3','4','5','6','7','8','9','-','.'
    };

    hnproSmall = new Font("hnpro", 16, usedChars);
    hnproMedium27 = new Font("hnpro", 26, usedChars);
    hnproHuge = new Font("hnpro", 150, largeChars);
    hnproMediumOblique = new Font("hnpro-italic", 36, usedChars);
    hnproHugeOblique = new Font("hnpro-italic", 100, largeChars);
    hnproExtraHeavy36 = new Font("hnpro-bold", 36, usedChars);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 2.0));
    
    _r->createFramebuffer(frameBuffer, screenTexture, WIDTH, HEIGHT);
}

bool Dashboard::render(float delta) {
    _r->clear();
    
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
    
    _r->renderTexture(screenTexture, 0, 0, WIDTH, HEIGHT);
    
    float value = vehicle->getRPM()/1000.0f;
    float max = 12;
    
//    r->renderTexture(fasterTexture, 400, 130, 350, 350, true);
    
    std::string degStr(1, '\xb0');
    std::string tempStr(1, '\xb0');
    tempStr.append("C");
    
    if (vehicle->getKickstand() == true) {
        _r->renderTexture(squareTextureId, 22, 363, 94, 94);
        _r->renderText(*hnproMedium27, "SIDE", 46.0f, 80.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        _r->renderText(*hnproMedium27, "STAND", 36.0f, 44.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    }
//
//    float endX = 0;
//    r->renderText(*hnproMedium27, playStatus_, 30.0, 460.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    r->renderText(*hnproMedium27, nowPlaying_.title, 30.0, 440.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getCoolantTempString(), attrX["coolantTemp"] + 5.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getAirIntakeTempString(), attrX["airIntakeTemp"] + 5.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getManifoldPressureString(), attrX["manifoldPressure"] + 5.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, "kPA", endX + 3.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getTPSString(), attrX["tps"] + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, "%", endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getInjectorString(), attrX["injectorDuration"] + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, "ms", endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getIgnitionAdvanceString(), attrX["ignitionAdvance"] + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, degStr, endX + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getBattVoltageString(), attrX["battVoltage"] + 5.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproMedium27, "V", endX + 3.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getRPMString(), 553.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    _r->renderText(*hnproHugeOblique, vehicle->getGearString(), 50.0f, 420.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER, CENTER);

//    std::string speed = vehicle->getSpeedString();
    std::string speed = "";
    _service->getFloatValueAsString("speed", speed);
    
    _r->renderText(*hnproHuge, speed, 270.0f, 200.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);
    _r->renderText(*hnproMediumOblique, "km/h", 200.0f, 160.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    //    r->renderText(*hnproSmall, "RPM X 1000", 700.0f, 200.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    //    r->drawRingArc(value, // value
    //                   max,// max value
    //                   550, // x
    //                   230, // y
    //                   220, // outer radius
    //                   0.1, // arc thickness
    //                   0, // start angle
    //                   0.75, // endPercent
    //                   glm::vec3(0.76,0.76,0.76) //color
    //                   );
    
    //    r->drawRingArcTexture(value, // value
    //                   max,// max value
    //                   550, // x
    //                   230, // y
    //                   220, // outer radius
    //                   0.2, // arc thickness
    //                   0, // start angle
    //                   0.75, // endPercent
    //                   arcTextureId // texture id
    //                   );
    
//        r->drawCircle(550, 230, 125, 50);
    this->drawCounter(*hnproMediumOblique, // font
                      550, // x
                      230, // y
                      220, // radius
                      30, // long tick lenght
                      15, // short tick length
                      M_PI + M_PI_2, // start angle
                      0.0, // end angle
                      12, // max value
                      10.5, // begin critical
                      4 // intermediary ticks
                      );
    this->drawNeedle(value, // value
                     max,  // max value
                     550, // x
                     230, // y
                     220, // tip radius,
                     70, // bottom radius,
                     M_PI + M_PI_2, // start angle
                     0 // end angle
                     );
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << _r->getFrameRate();
    _r->renderText(*hnproMedium27, sfps.str(), 0.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    return true;
}

void Dashboard::renderFixed() {
    _r->bindFramebuffer(frameBuffer);
    _r->clear();

//    r->useProgram(*r->textProgram);
    
//    attrX["coolantTemp"] = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["coolantTemp"] = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["airIntakeTemp"] = r->renderText(*hnproMedium27, "Air Intake Temp", 27.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["manifoldPressure"] = r->renderText(*hnproMedium27, "Manifold Pressure", 27.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["tps"] = r->renderText(*hnproMedium27, "TPS", 600.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["injectorDuration"] = r->renderText(*hnproMedium27, "Injector Duration", 300.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["ignitionAdvance"] = r->renderText(*hnproMedium27, "Ignition Advance", 300.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    attrX["battVoltage"] = r->renderText(*hnproMedium27, "Battery Voltage", 140.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//
    _r->bindFramebuffer(0);
    _r->setGlobalAlpha(0.0);
}

void Dashboard::drawCounter(Font &font, GLfloat x, GLfloat y, GLfloat radius, GLfloat longTickLength, GLfloat shortTickLength, GLfloat startAngle, GLfloat endAngle, GLfloat maxValue, GLfloat beginCritical, GLint ticksBetweenInts) {
    
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

void Dashboard::drawNeedle(float value, float maxValue, GLint x, GLint y, GLfloat tipRadius, GLfloat bottomRadius, GLfloat startAngle, GLfloat endAngle) {
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
