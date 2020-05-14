//
//  ShaderProgram.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#ifdef Status
#undef Status
#endif

#include "Shader.hpp"

class ShaderProgram {
    Shader *VertexShader;
    Shader *FragmentShader;
    GLuint Id;
    std::map<std::string, GLuint> uniformLocations;
    
public:
    
    ShaderProgram() {}
    ~ShaderProgram() {}
    
    bool create(Shader *vertex_shader, Shader *fragment_shader);
    GLuint getUniformLocation(std::string name);
    GLuint getId() { return Id; }
};

#endif /* ShaderProgram_hpp */
