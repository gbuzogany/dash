//
//  Shader.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "Shader.hpp"
#include <assert.h>

bool Shader::loadFragmentShader(const char *filename)
{
    //cheeky bit of code to read the whole file into memory
    assert(!Src);
    FILE* f = fopen(filename, "rb");
    assert(f);
    fseek(f,0,SEEK_END);
    long sz = ftell(f);
    fseek(f,0,SEEK_SET);
    Src = new GLchar[sz+1];
    fread(Src,1,sz,f);
    Src[sz] = 0; //null terminate it!
    fclose(f);
    
    //now create and compile the shader
    //      GlShaderType = GL_FRAGMENT_SHADER;
    Id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Id, 1, (const GLchar**)&Src, 0);
    glCompileShader(Id);
    //        check();
    
    //compilation check
    //      GLint compiled;
    
    return true;
}

bool Shader::loadVertexShader(const char *filename)
{
    char *working_dir_path = realpath(".", NULL);
    printf("%s\n", working_dir_path);
    //cheeky bit of code to read the whole file into memory
    assert(!Src);
    FILE* f = fopen(filename, "rb");
    assert(f);
    fseek(f,0,SEEK_END);
    long sz = ftell(f);
    fseek(f,0,SEEK_SET);
    Src = new GLchar[sz+1];
    fread(Src,1,sz,f);
    Src[sz] = 0; //null terminate it!
    fclose(f);
    
    //now create and compile the shader
    GlShaderType = GL_VERTEX_SHADER;
    Id = glCreateShader(GlShaderType);
    glShaderSource(Id, 1, (const GLchar**)&Src, 0);
    glCompileShader(Id);
    //    check();
    
    return true;
}
