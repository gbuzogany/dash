//
//  Scene.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(Renderer *renderer, DashServiceImpl *service) {
    this->_r = renderer;
    this->_service = service;
};
