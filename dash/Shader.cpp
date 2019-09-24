//
//  Shader.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Shader.hpp"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

bool Shader::loadFragmentShader(const char *filename)
{
    assert(!Src);
    FILE* f = fopen(filename, "rb");
    assert(f);
    fseek(f,0,SEEK_END);
    long sz = ftell(f);
    fseek(f,0,SEEK_SET);
    Src = new GLchar[sz+1];
    fread(Src,1,sz,f);
    Src[sz] = 0;
    fclose(f);

    Id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Id, 1, (const GLchar**)&Src, 0);
    glCompileShader(Id);
    assert(glGetError() == 0);
    return true;
}

bool Shader::loadVertexShader(const char *filename)
{
    assert(!Src);
    FILE* f = fopen(filename, "rb");
    assert(f);
    fseek(f,0,SEEK_END);
    long sz = ftell(f);
    fseek(f,0,SEEK_SET);
    Src = new GLchar[sz+1];
    fread(Src,1,sz,f);
    Src[sz] = 0;
    fclose(f);

    GlShaderType = GL_VERTEX_SHADER;
    Id = glCreateShader(GlShaderType);
    glShaderSource(Id, 1, (const GLchar**)&Src, 0);
    glCompileShader(Id);
    assert(glGetError() == 0);
    
    return true;
}
