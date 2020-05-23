//
//  DashIcons.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 23/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef DashIcons_hpp
#define DashIcons_hpp

#include "Renderer.hpp"
#include "Icon.hpp"
#include "Definitions.h"
#include <map>
#include "rapidjson/reader.h"
#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

class DashIcons;

class DashIcons {
    
    DashIcons();
    GLuint iconsTexture;
    GLfloat texWidth, texHeight;
    
    std::map<std::string, Icon*> iconMap;
    
    static DashIcons *instance;
    void parseIcons(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj);
    void parseTexture(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj);
public:
    static DashIcons* getInstance();
    void loadIcons(std::string jsonPath);
    void renderIcon(Renderer *r, std::string name, int x, int y, float scale, glm::vec3 color);
};

#endif /* DashIcons_hpp */
