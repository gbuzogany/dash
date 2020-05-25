#ifndef SpriteMap_hpp
#define SpriteMap_hpp

#include "Renderer.hpp"
#include "Icon.hpp"
#include "Definitions.h"
#include <map>
#include "rapidjson/reader.h"
#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

class SpriteMap;

class SpriteMap {
    
    SpriteMap();
    GLuint iconsTexture;
    GLfloat texWidth, texHeight;
    
    std::map<std::string, Icon*> iconMap;
    
    static SpriteMap *instance;
    void parseIcons(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj);
    void parseTexture(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj);
public:
    ~SpriteMap();
    static SpriteMap* getInstance();
    void loadIcons(std::string jsonPath);
    void renderIcon(Renderer *r, std::string name, int x, int y, float scale, glm::vec3 color);
};

#endif /* SpriteMap_hpp */
