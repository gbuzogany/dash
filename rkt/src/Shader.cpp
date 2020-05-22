#include "Shader.hpp"

#if !defined (_WIN32)
#include <fcntl.h>
#include <unistd.h>
#endif

#include <assert.h>
#include <iostream>
#include <stdlib.h>

bool Shader::loadFragmentShader(const char *filename)
{
    printf("Loading %s...\n", filename);
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
    printf("Loading %s...\n", filename);
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
