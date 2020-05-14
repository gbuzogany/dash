//
//  Shader.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#if !defined (__APPLE_CC__)
#include <GLFW/glfw3.h>
#endif

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

class Shader {
    GLchar* Src;
    GLuint Id;
    GLuint GlShaderType;
    
public:
    
    Shader() : Src(NULL), Id(0), GlShaderType(0) {}
    ~Shader() { if(Src) delete[] Src; }
    
    bool loadVertexShader(const char* filename);
    bool loadFragmentShader(const char* filename);
    GLuint getId() { return Id; }
};

#endif /* Shader_hpp */
