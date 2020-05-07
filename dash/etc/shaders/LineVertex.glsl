attribute vec2 aPos;
attribute vec2 aPrevPos;
attribute vec2 aNextPos;
attribute float aOffset;

uniform vec4 u_linewidth;
uniform mat4 u_mvmatrix;
uniform mat4 u_pmatrix;
uniform bool u_shift;

varying float v_alpha;

void main() {
    vec4 pos = u_mvmatrix * vec4(aPos.xy / 10.0, 0, 1);
    v_alpha = 1.0;
    
    if (u_shift) {
        vec2 deltaNext = aNextPos.xy - aPos.xy;
        vec2 deltaPrev = aPos.xy - aPrevPos.xy;
        float angleNext = atan(deltaNext.y, deltaNext.x);
        float anglePrev = atan(deltaPrev.y, deltaPrev.x);
        if (deltaPrev.xy == vec2(0, 0)) anglePrev = angleNext;
        if (deltaNext.xy == vec2(0, 0)) angleNext = anglePrev;
        
        float angle = (anglePrev + angleNext) / 2.0;
        float distance = aOffset * (aOffset > 0.0 ? u_linewidth.s : u_linewidth.p) / cos(anglePrev - angle);
        
        pos.x += distance * sin(angle);
        pos.y -= distance * cos(angle);
        
        if (aOffset > 0.0) {
            v_alpha = u_linewidth.t;
        } else {
            v_alpha = u_linewidth.q;
        }
    }
    
    gl_Position = u_pmatrix * pos;
    }
