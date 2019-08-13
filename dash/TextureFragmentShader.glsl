varying highp vec2 UV;

uniform sampler2D myTextureSampler;

void main(){
    gl_FragColor.a = 1.0;
    gl_FragColor.rgb = texture2D( myTextureSampler, UV ).rgb;
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
