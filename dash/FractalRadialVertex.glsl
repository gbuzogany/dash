attribute vec4 vertex;

varying highp vec2 original_uv;
uniform highp mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    original_uv = vertex.zw;
}
