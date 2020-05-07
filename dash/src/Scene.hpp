//
//  Scene.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 02/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Renderer.hpp"

class Scene {
protected:
    Renderer *r;
    
public:
    Scene(Renderer &renderer);
    virtual bool render(float delta) = 0;
    virtual void renderFixed() = 0;
};

#endif /* Scene_hpp */
