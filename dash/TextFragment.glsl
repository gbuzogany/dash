varying highp vec2 UV;

uniform sampler2D text;
uniform highp vec3 textColor;

void main()
{
    highp vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, UV).r);
    gl_FragColor = vec4(textColor, 1.0) * sampled;
}
