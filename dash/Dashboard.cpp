//
//  Dashboard.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Dashboard.hpp"
#include "MediaPlayer.hpp"
#include "DashControl.hpp"
#include <thread>
#include <functional>
#include <memory>

Dashboard::Dashboard(Renderer &renderer) {
    this->r = &renderer;
    
    squareTextureId = Texture::loadBMP("square.bmp");

    vehicle = new Vehicle();
    
    FT_Face face, faceItalic, faceBold;
    if (FT_New_Face(r->ft, "hnpro-medium-condensed.otf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    if (FT_New_Face(r->ft, "hnpro-medium-condensed-oblique.otf", 0, &faceItalic)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    if (FT_New_Face(r->ft, "hnpro-extra-black-condensed.otf", 0, &faceBold)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/'
    };
    
    std::vector<FT_ULong> largeChars = {
        'N','0','1','2','3','4','5','6','7','8','9','-'
    };
    
    hnproSmall = new FontWrapper(face, 16, usedChars);
    hnproMedium27 = new FontWrapper(face, 26, usedChars);
    hnproHuge = new FontWrapper(face, 150, largeChars);
    hnproMediumOblique = new FontWrapper(faceItalic, 36, usedChars);
    hnproHugeOblique = new FontWrapper(faceItalic, 150, largeChars);
    hnproExtraHeavy36 = new FontWrapper(faceBold, 36, usedChars);
    
    createFramebuffer();
    
    mediaServiceThread = std::thread(&Dashboard::startMediaService, this);
    dashServiceThread = std::thread(&Dashboard::startDashService, this);
}

void Dashboard::startMediaService() {
    std::string server_address("0.0.0.0:50051");
    MediaPlayerImpl service(this);
    
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Media Server listening on " << server_address << std::endl;

    server->Wait();
}

void Dashboard::startDashService() {
    std::string server_address("0.0.0.0:50052");
    DashControlImpl service(this);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Dash Server listening on " << server_address << std::endl;

    server->Wait();
}

void Dashboard::setPlayStatus(std::string playStatus) {
    playStatus_ = playStatus;
}

void Dashboard::setNowPlaying(DashMediaItem mediaItem) {
    nowPlaying_ = mediaItem;
}

void Dashboard::createFramebuffer() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    
    glGenTextures(1, &screenTexture);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    r->bindTexture(screenTexture);
    
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, WIDTH, HEIGHT, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
    
    GLint maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
    printf("Max texture size: %dx%d\n", maxTextureSize, maxTextureSize);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Error creating framebuffer!\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Dashboard::render() {
    glUseProgram(r->textureProgram->getId());
    r->renderTexture(screenTexture, 0, 0, WIDTH, HEIGHT);

    std::string degStr(1, '\xb0');
    std::string tempStr(1, '\xb0');
    tempStr.append("C");
    
    if (vehicle->getKickstand() == true) {
        r->renderTexture(squareTextureId, 22, 363, 94, 94);
        
        glUseProgram(r->textProgram->getId());
        
        r->renderText(*hnproMedium27, "SIDE", 46.0f, 480-400.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        r->renderText(*hnproMedium27, "STAND", 36.0f, 480-436.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    }
    else {
        glUseProgram(r->textProgram->getId());
    }
    
    float endX = 0;
    r->renderText(*hnproMedium27, playStatus_, 30.0, 460.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, nowPlaying_.title, 30.0, 440.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getCoolantTempString(), attrX["coolantTemp"] + 5.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getAirIntakeTempString(), attrX["airIntakeTemp"] + 5.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getManifoldPressureString(), attrX["manifoldPressure"] + 5.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "kPA", endX + 3.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getTPSString(), attrX["tps"] + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "%", endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getInjectorString(), attrX["injectorDuration"] + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "ms", endX + 3.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getIgnitionAdvanceString(), attrX["ignitionAdvance"] + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, degStr, endX + 3.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getBattVoltageString(), attrX["battVoltage"] + 5.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "V", endX + 3.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    endX = r->renderText(*hnproExtraHeavy36, vehicle->getRPMString(), 553.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproHugeOblique, vehicle->getGearString(), 550.0f, 230.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER, CENTER);
    std::string speed = vehicle->getSpeedString();
    r->renderText(*hnproHuge, speed, 240.0f, 480-323.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), RIGHT);
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << r->getFrameRate();
    r->renderText(*hnproMedium27, sfps.str(), 0.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Dashboard::renderFixed() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(r->textProgram->getId());
    attrX["coolantTemp"] = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["coolantTemp"] = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["airIntakeTemp"] = r->renderText(*hnproMedium27, "Air Intake Temp", 27.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["manifoldPressure"] = r->renderText(*hnproMedium27, "Manifold Pressure", 27.0f, 357.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["tps"] = r->renderText(*hnproMedium27, "TPS", 600.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["injectorDuration"] = r->renderText(*hnproMedium27, "Injector Duration", 300.0f, 441.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["ignitionAdvance"] = r->renderText(*hnproMedium27, "Ignition Advance", 300.0f, 397.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["battVoltage"] = r->renderText(*hnproMedium27, "Battery Voltage", 140.0f, 29.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    r->renderText(*hnproMediumOblique, "km/h", 170.0f, 117.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproSmall, "RPM X 1000", 600.0f, 70.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    r->drawCircle(550, 230, 125, 50);
    this->drawCounter(*hnproMediumOblique, // font
                   550, // x
                   230, // y
                   220, // radius
                   30, // long tick lenght
                   15, // short tick length
                   M_PI + M_PI_2, // start angle
                   M_PI + M_PI_2 + M_PI_4, // end angle
                   17, // max value
                   4 // intermediary ticks
                   );
//    r->drawNeedle(550,
//                  230, 220, 30, 15, M_PI + M_PI_2, 0, 17, 4);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Vehicle* Dashboard::getVehicle() {
    return vehicle;
}

void Dashboard::drawCounter(FontWrapper &font, GLfloat x, GLfloat y, GLfloat radius, GLfloat longTickLength, GLfloat shortTickLength, GLfloat minAngle, GLfloat maxAngle, GLint maxValue, GLint ticksBetweenInts) {
    
    GLuint vertexbuffer = r->getVertexBuffer();
    
    GLint ticks = (maxValue - 1) * ticksBetweenInts + maxValue;
    GLint numberOfVertices = ticks * 2;
    GLfloat allCircleVertices[numberOfVertices * 2];
    GLfloat deltaAngle = 0;
    
    if (minAngle > maxAngle) {
        deltaAngle = maxAngle - minAngle;
    }
    else {
        deltaAngle = (minAngle - maxAngle) - minAngle;
    }
    
    for ( int i = 0; i < ticks; i++)
    {
        GLfloat smallRadius = shortTickLength;
        if (i % (ticksBetweenInts + 1) == 0) {
            smallRadius = longTickLength;
            r->renderText(font,
                             std::to_string(i/(ticksBetweenInts+1)+1),
                             x + ( (radius - smallRadius - 25) * cos(minAngle + i * (deltaAngle / ticks) ) ),
                             y + ( (radius - smallRadius - 25) * sin(minAngle + i * (deltaAngle / ticks) ) ),
                             1.0f,
                             glm::vec3(1.0f, 1.0f, 1.0f),
                             CENTER,
                             CENTER);
        }
        
        allCircleVertices[(i * 4)] = x + ( radius * cos(minAngle + i * (deltaAngle / ticks) ) );
        allCircleVertices[(i * 4) + 1] = y + ( radius * sin(minAngle + i * (deltaAngle / ticks) ) );
        
        allCircleVertices[(i * 4) + 2] = x + ( (radius - smallRadius) * cos(minAngle + i * (deltaAngle / ticks)) );
        allCircleVertices[(i * 4) + 3] = y + ( (radius - smallRadius) * sin(minAngle + i * (deltaAngle / ticks)) );
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allCircleVertices), allCircleVertices, GL_DYNAMIC_DRAW);
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

void Renderer::drawCircle( GLfloat x, GLfloat y, GLfloat radius, GLint numberOfSides )
{
    GLint numberOfVertices = numberOfSides + 1;
    
    GLfloat doublePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i * doublePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * doublePi / numberOfSides ) );
    }
    
    GLfloat allCircleVertices[numberOfVertices * 2];
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 2] = circleVerticesX[i];
        allCircleVertices[( i * 2 ) + 1] = circleVerticesY[i];
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(allCircleVertices), allCircleVertices, GL_DYNAMIC_DRAW);
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
    glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
    
    glDisableVertexAttribArray(0);
    
}
