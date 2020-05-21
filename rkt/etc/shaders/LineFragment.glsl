precision mediump float;

varying float v_alpha;

uniform vec4 u_color;

void main() {
    gl_FragColor = vec4(u_color.rgb, u_color.a * v_alpha);
}
