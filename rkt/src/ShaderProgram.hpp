#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>
#include <glad/glad.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifdef Status
#undef Status
#endif

class ShaderProgram {
    GLuint Id, vs, fs;
    std::map<std::string, GLuint> uniformLocations;
    
public:
    
    ShaderProgram(const std::string vertex_shader, const std::string fragment_shader);
    ~ShaderProgram();
    
    GLuint compileShader(std::string filename, GLuint shader_type);
    GLuint getUniformLocation(std::string name);
    GLuint getId() { return Id; }
};

#endif /* ShaderProgram_hpp */
