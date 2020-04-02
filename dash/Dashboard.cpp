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

    vehicle = new CB650F();
    
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
    
    hnproMedium27 = new FontWrapper(face, 26, usedChars);
    hnproHuge = new FontWrapper(face, 240, largeChars);
    hnproMediumOblique = new FontWrapper(faceItalic, 36, usedChars);
    hnproHugeOblique = new FontWrapper(faceItalic, 250, largeChars);
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
    
    vehicle->guessGear();

    std::string degStr(1, '\xb0');
    std::string tempStr(1, '\xb0');
    tempStr.append("C");
    
    if (vehicle->getNeutral() == KICKSTAND_NEUTRAL) {
        r->renderTexture(squareTextureId, 22, 363, 94, 94);
        
        glUseProgram(r->textProgram->getId());
        
        r->renderText(*hnproMedium27, "SIDE", 46.0f, 400.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        r->renderText(*hnproMedium27, "STAND", 36.0f, 436.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    }
    else {
        glUseProgram(r->textProgram->getId());
    }
    
    float endX = 0;
    r->renderText(*hnproMedium27, playStatus_, 30.0, 20.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, nowPlaying_.title, 30.0, 40.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getCoolantTempString(), attrX["coolantTemp"] + 5.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getAirIntakeTempString(), attrX["airIntakeTemp"] + 5.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getManifoldPressureString(), attrX["manifoldPressure"] + 5.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "kPA", endX + 3.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getTPSString(), attrX["tps"] + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "%", endX + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getInjectorString(), attrX["injectorDuration"] + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "ms", endX + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getIgnitionAdvanceString(), attrX["ignitionAdvance"] + 3.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, degStr, endX + 3.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getBattVoltageString(), attrX["battVoltage"] + 5.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "V", endX + 3.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getMaxPowerString(), attrX["maxPower"] + 5.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "HP", endX + 3.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getMaxTorqueString(), attrX["maxTorque"] + 5.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "Nm", endX + 3.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getRPMString(), 553.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "RPM", endX + 5.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproHugeOblique, vehicle->getGearString(), 530.0f, 284.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproHuge, vehicle->getSpeedString(), 69.0f, 323.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << r->getFrameRate();
    r->renderText(*hnproMedium27, sfps.str(), 0.0f, 480.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Dashboard::renderFixed() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(r->textProgram->getId());
    
    attrX["coolantTemp"] = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["airIntakeTemp"] = r->renderText(*hnproMedium27, "Air Intake Temp", 27.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["manifoldPressure"] = r->renderText(*hnproMedium27, "Manifold Pressure", 27.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["tps"] = r->renderText(*hnproMedium27, "TPS", 600.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["injectorDuration"] = r->renderText(*hnproMedium27, "Injector Duration", 300.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["ignitionAdvance"] = r->renderText(*hnproMedium27, "Ignition Advance", 300.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["battVoltage"] = r->renderText(*hnproMedium27, "Battery Voltage", 140.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["maxPower"] = r->renderText(*hnproMedium27, "Max Power @", 512.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    attrX["maxTorque"] = r->renderText(*hnproMedium27, "Max Torque @", 509.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    r->renderText(*hnproMediumOblique, "km/h", 330.0f, 363.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Vehicle* Dashboard::getVehicle() {
    return vehicle;
}
