varying highp vec2 UV;

uniform sampler2D textureSampler;

void main(){
    gl_FragColor.a = 1.0;
    gl_FragColor.rgb = texture2D( textureSampler, UV ).bgr;
}
