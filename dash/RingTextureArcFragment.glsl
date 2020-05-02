#define PI 3.1415926538
#define TAU 2.0*PI

precision highp float;
precision highp int;

varying vec2 UV;

uniform vec3 color;

uniform float startAngle;
uniform float endPercent;

uniform float valuePos;
uniform float outerRadius;
uniform float innerRadius;

uniform sampler2D tex;

float map(float value, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec2 map(vec2 value, vec2 inMin, vec2 inMax, vec2 outMin, vec2 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec3 map(vec3 value, vec3 inMin, vec3 inMax, vec3 outMin, vec3 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

vec4 map(vec4 value, vec4 inMin, vec4 inMax, vec4 outMin, vec4 outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main() {
    mat2 rot = mat2(
        cos(startAngle), -sin(startAngle),
        sin(startAngle), cos(startAngle)
    );
    
    vec2 aux1 = map(UV, vec2(0.0, 0.0), vec2(1.0, 1.0), vec2(-1.0, -1.0), vec2(1.0, 1.0));
    float aux2 = length(aux1) + (1.0 - outerRadius);
    float aux5  = aux2 + innerRadius;
    aux5  = floor(aux5);
    float aux4 = 1.0 - floor(aux2);
    aux4 = aux4 * aux5;
    vec2 uv_rot = aux1 * rot;
    
    float angle = atan(uv_rot.y, uv_rot.x);
    angle = map(angle, -PI, PI, 0.0, 1.0);
    angle = 1.0 - angle;
    angle = angle - valuePos * endPercent;
    angle = 1.0 - ceil(angle);
    float aux7 = angle * aux4;
    vec3 sampled = texture2D(tex, UV).rgb;
    vec3 aux3 = aux7 * sampled;
    gl_FragColor = vec4(aux3, aux7);
}
