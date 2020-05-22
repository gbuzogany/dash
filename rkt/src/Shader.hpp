#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

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
