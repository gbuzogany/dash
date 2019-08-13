//
//  ShaderProgram.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 13/08/2019.
//  Copyright © 2019 gbuzogany.com. All rights reserved.
//

#include "ShaderProgram.hpp"

bool ShaderProgram::create(Shader *vertex_shader, Shader *fragment_shader)
{
    VertexShader = vertex_shader;
    FragmentShader = fragment_shader;
    Id = glCreateProgram();
    glAttachShader(Id, VertexShader->getId());
    glAttachShader(Id, FragmentShader->getId());
    glLinkProgram(Id);
    //        check();
    
    return true;
}
