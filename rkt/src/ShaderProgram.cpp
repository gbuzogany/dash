#include "ShaderProgram.hpp"

bool ShaderProgram::create(Shader *vertex_shader, Shader *fragment_shader)
{
    VertexShader = vertex_shader;
    FragmentShader = fragment_shader;
    Id = glCreateProgram();
    glAttachShader(Id, VertexShader->getId());
    glAttachShader(Id, FragmentShader->getId());
    glLinkProgram(Id);
    assert(glGetError() == 0);
    
    return true;
}

GLuint ShaderProgram::getUniformLocation(std::string name) {
    if (uniformLocations.find(name) == uniformLocations.end()) {
        GLuint uniform = glGetUniformLocation(Id, name.c_str());
        uniformLocations[name] = uniform;
        return uniform;
    }
    return uniformLocations[name];
}
