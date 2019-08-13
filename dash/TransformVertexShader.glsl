// input
attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;

// output
varying highp vec2 UV;

// uniforms
uniform highp mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    UV = vertexUV;
}
