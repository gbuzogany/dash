#define PI 3.1415926538
#define R vec2(400.0, 400.0)


precision highp float;
precision highp int;

varying vec2 original_uv;

uniform vec3 color;

uniform float time;

float circle(vec2 st, vec2 p, float r){
    float d = length(st-p)*r;
    return 1.0/dot(d,d);
    return smoothstep(r, r-2./10.0, length(st-p));//length(st-p)<r?1.0:0.0;
}

float line(vec2 p1, vec2 p2, vec2 uv, float t) {
    float a = abs(distance(p1, uv));
    float b = abs(distance(p2, uv));
    float c = abs(distance(p1, p2));
    if ( a >= c || b >=  c ) return 0.0;
    float p = (a + b + c) * 0.5;
    float h = 2.0 / c * sqrt( p * ( p - a) * ( p - b) * ( p - c));
    return mix(1.0, 0.0, smoothstep(0.5 * t, 1.5 * t, h));
}

vec2 get_coord(float i, float r, float np){
    float th = PI+(i*2.*PI/np);
    return vec2(r*cos(th), r*sin(th));
}

void main()
{
    // just inner diameter
    vec2 uv = (2.0 * vec2(R.x/R.y, 1.0) * original_uv - vec2(1.0, 1.0)) / 1.0;
    // full diameter
//    vec2 uv = (2.0 * vec2(R.x/R.y, 1.0) * original_uv - vec2(2.29, 0.96)) / 1.0;
    vec3 col = vec3(uv, 0.0);
    float np = 180.;
    float fac = time;
    
    float shape = 0.0;
    for (float i=0.0; i<=180.0; i++){
        float r = 0.9;
        vec2 pos = get_coord(i, r, np);
        
        //line
        vec2 pos_line2 = get_coord(mod(i*fac, np), r, np);
        float lines = line(pos, pos_line2, uv, 0.004);
        
        shape += circle(uv, pos, 80.);
        shape += lines;
    }
    
    col = (shape) * color;// + vec3(.12) * (1.0 - clamp(shape, 0.0, 1.0));
    gl_FragColor = vec4(col, 1.0);
}
