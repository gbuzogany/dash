//
//  Dashboard.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 15/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Dashboard.hpp"

Dashboard::Dashboard(Renderer &renderer) {
    this->r = &renderer;
    
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
    
    hnproMedium27 = new FontWrapper(face, 26);
    hnproHuge = new FontWrapper(face, 240);
    hnproMediumOblique = new FontWrapper(faceItalic, 36);
    hnproHugeOblique = new FontWrapper(faceItalic, 250);
    hnproExtraHeavy36 = new FontWrapper(faceBold, 36);
}

void Dashboard::render() {
    std::string tempStr(1, '\xb0');
    tempStr.append("C");
    
    glUseProgram(r->textProgram->getId());
    
    float endX = 0;
    endX = r->renderText(*hnproMedium27, "Coolant Temp", 27.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getCoolantTempString(), endX + 5.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 39.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "Air Intake Temp", 27.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getAirIntakeTempString(), endX + 5.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, tempStr, endX + 3.0f, 83.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "Manifold Pressure", 27.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getManifoldPressureString(), endX + 5.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "kPA", endX + 3.0f, 123.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "TPS", 564.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getTPSString(), endX + 3.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "%", endX + 3.0f, 47.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "Battery Voltage", 140.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getBattVoltageString(), endX + 5.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "V", endX + 3.0f, 451.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "Max Power @", 512.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getMaxPowerString(), endX + 5.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "HP", endX + 3.0f, 410.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproMedium27, "Max Torque @", 509.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getMaxTorqueString(), endX + 5.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "Nm", endX + 3.0f, 448.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    endX = r->renderText(*hnproExtraHeavy36, vehicle->getRPMString(), 553.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMedium27, "RPM", endX + 5.0f, 364.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproHugeOblique, vehicle->getGearString(), 530.0f, 284.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproHuge, vehicle->getSpeedString(), 69.0f, 323.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    r->renderText(*hnproMediumOblique, "km/h", 330.0f, 363.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << r->getFrameRate();
    r->renderText(*hnproMedium27, sfps.str(), 0.0f, 480.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
