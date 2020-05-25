precision highp float;
precision highp int;
// input
attribute vec4 vertex;
uniform highp mat4 projection;

varying vec2 vs_TEXCOORD0;
varying vec4 vs_TEXCOORD2;
varying vec4 vs_TEXCOORD3;
varying vec4 vs_TEXCOORD4;
varying vec4 vs_TEXCOORD5;
varying vec4 vs_COLOR0;

uniform float time;

uniform float FX1PulseAmount;
uniform float FX1PulseRate;
uniform float FX1PulseIntensity;
uniform float FX1PulseClip;
uniform float FX1ScrollRotateFlow;
uniform float FX1ScrollAngle;
uniform float FX1ScrollXSpeed;
uniform float FX1ScrollYSpeed;
uniform float FX1RotationSpeed;
uniform float FX1RotationCenterX;
uniform float FX1RotationCenterY;
uniform float FX1FlowAngle;
uniform float FX1FlowMapXOffset;
uniform float FX1FlowMapYOffset;
uniform float FX1FlowMapScaleXSpeed;
uniform float FX1FlowMapScaleYSpeed;
uniform float FX1FlowMapScrollXSpeed;
uniform float FX1FlowMapScrollYSpeed;
uniform float FX1OscillationSpeed;
uniform vec4 FX1Oscillation;
uniform float FX1ScaleX;
uniform float FX1ScaleY;

uniform float FX2PulseAmount;
uniform float FX2PulseRate;
uniform float FX2PulseIntensity;
uniform float FX2PulseClip;
uniform float FX2ScrollRotate;
uniform float FX2ScrollAngle;
uniform float FX2ScrollXSpeed;
uniform float FX2ScrollYSpeed;
uniform float FX2RotationSpeed;
uniform float FX2RotationCenterX;
uniform float FX2RotationCenterY;
uniform float FX2OscillationSpeed;
uniform vec4 FX2Oscillation;
uniform float FX2ScaleX;
uniform float FX2ScaleY;

uniform float FX3PulseAmount;
uniform float FX3PulseRate;
uniform float FX3PulseIntensity;
uniform float FX3PulseClip;
uniform float FX3RotationSpeed;
uniform float FX3RotationCenterX;
uniform float FX3RotationCenterY;
uniform float FX3OscillationSpeed;
uniform vec4 FX3Oscillation;
uniform float FX3ScrollRotate;
uniform float FX3ScrollXSpeed;
uniform float FX3ScrollYSpeed;
uniform float FX3ScrollAngle;
uniform float FX3ScaleX;
uniform float FX3ScaleY;

uniform float FX4PulseAmount;
uniform float FX4PulseRate;
uniform float FX4PulseIntensity;
uniform float FX4PulseClip;
uniform float FX4ScrollXSpeed;
uniform float FX4ScrollYSpeed;
uniform float FX4ScrollAngle;
uniform float FX4OscillationSpeed;
uniform vec4 FX4Oscillation;
uniform float FX4ScaleX;
uniform float FX4ScaleY;

uniform float LightingBlend;
uniform float Seed;
uniform float timeScale;

vec4 u_xlat0;
vec4 u_xlat1;
bvec2 u_xlatb1;
vec4 u_xlat2;
bool u_xlatb2;
vec4 u_xlat3;
vec4 u_xlat4;
vec3 u_xlat5;
vec3 u_xlat6;
vec3 u_xlat7;
float u_xlat8;
vec3 u_xlat9;
float u_xlat10;
vec2 u_xlat11;
vec2 u_xlat12;
float u_xlat16;
bool u_xlatb16;
vec2 u_xlat18;
vec2 u_xlat20;
vec2 u_xlat21;
float u_xlat24;
bool u_xlatb24;
float u_xlat25;
vec4 _Time;

vec4 _MainTex_ST;
float ShaderTime;

void main(){
    vec2 UV = vertex.zw;
    
	_MainTex_ST = vec4(1.0, 1.0, 0.0, 0.0);
	float t = time*20.0;
	_Time = vec4(time, t, t*t, t*t*t);
	ShaderTime = time;

    u_xlat0.xy = UV * _MainTex_ST.xy + _MainTex_ST.zw;
    vs_TEXCOORD0.xy = UV * _MainTex_ST.xy + _MainTex_ST.zw;
    u_xlatb16 = 0.0<FX1ScrollRotateFlow;
    u_xlatb1.xy = lessThan(vec4(FX1ScrollRotateFlow), vec4(2.0, 1.0, 0.0, 0.0)).xy;
    u_xlatb16 = u_xlatb16 && u_xlatb1.x;
    u_xlat2.x = float(0.0);
    u_xlat2.y = float(0.0);
    u_xlat3.x = float(0.0);
    u_xlat3.y = float(0.0);
    u_xlat1.x = sin(FX1FlowAngle);
    u_xlat4.x = cos(FX1FlowAngle);
    u_xlat5.z = u_xlat1.x;
    u_xlat5.y = u_xlat4.x;
    u_xlat5.x = (-u_xlat1.x);
    u_xlat1.xz = u_xlat0.xy + vec2(-0.5, -0.5);
    u_xlat20.x = dot(u_xlat1.xz, u_xlat5.yz);
    u_xlat20.y = dot(u_xlat1.xz, u_xlat5.xy);
    u_xlat4.xy = u_xlat20.xy + vec2(0.5, 0.5);
    u_xlat4.xy = u_xlat4.xy + vec2(FX1FlowMapXOffset, FX1FlowMapYOffset);
    u_xlat4.zw = u_xlat4.xy * vec2(FX1FlowMapScaleXSpeed, FX1FlowMapScaleYSpeed);
    u_xlat5.x = sin(FX1ScrollAngle);
    u_xlat6.x = cos(FX1ScrollAngle);
    u_xlat7.z = u_xlat5.x;
    u_xlat7.y = u_xlat6.x;
    u_xlat7.x = (-u_xlat5.x);
    u_xlat5.y = dot(u_xlat1.xz, u_xlat7.xy);
    u_xlat5.x = dot(u_xlat1.xz, u_xlat7.yz);
    u_xlat5.xy = u_xlat5.xy + vec2(0.5, 0.5);
    u_xlatb24 = 0.0<ShaderTime;
    u_xlat25 = ShaderTime + Seed;
    u_xlat21.x = _Time.x + Seed;
    u_xlat24 = (u_xlatb24) ? u_xlat25 : u_xlat21.x;
    u_xlat24 = u_xlat24 * timeScale;
    u_xlat25 = u_xlat24 * FX1OscillationSpeed;
    u_xlat25 = sin(u_xlat25);
    u_xlat21.xy = vec2(u_xlat25) * FX1Oscillation.xy + FX1Oscillation.zw;
    u_xlat6.xy = vec2(FX1ScrollXSpeed, FX1ScrollYSpeed) * vec2(u_xlat24) + u_xlat21.xy;
    u_xlat5.xy = u_xlat5.xy + u_xlat6.xy;
    u_xlat3.z = u_xlat5.x * FX1ScaleX;
    u_xlat3.w = u_xlat5.y * FX1ScaleY;
    u_xlat4.xy = vec2(FX1FlowMapScrollXSpeed, FX1FlowMapScrollYSpeed) * vec2(u_xlat24) + u_xlat21.xy;
    u_xlat25 = FX1RotationSpeed * u_xlat24 + u_xlat21.x;
    u_xlat5.x = sin(u_xlat25);
    u_xlat6.x = cos(u_xlat25);
    u_xlat3 = (u_xlatb1.y) ? u_xlat3 : u_xlat4;
    u_xlat9.xz = vec2(FX1RotationCenterX, FX1RotationCenterY) + vec2(0.5, 0.5);
    u_xlat9.xz = u_xlat0.xy + (-u_xlat9.xz);
    u_xlat4.x = u_xlat9.x * FX1ScaleX;
    u_xlat4.y = u_xlat9.z * FX1ScaleY;
    u_xlat7.z = u_xlat5.x;
    u_xlat7.y = u_xlat6.x;
    u_xlat7.x = (-u_xlat5.x);
    u_xlat20.y = dot(u_xlat4.xy, u_xlat7.xy);
    u_xlat20.x = dot(u_xlat4.xy, u_xlat7.yz);
    u_xlat2.zw = u_xlat20.xy + vec2(0.5, 0.5);
    u_xlat2 = (bool(u_xlatb16)) ? u_xlat2 : u_xlat3;
    vs_TEXCOORD2.xy = u_xlat2.zw;
    vs_TEXCOORD5.xy = u_xlat2.xy;
    u_xlat2.x = sin(FX4ScrollAngle);
    u_xlat3.x = cos(FX4ScrollAngle);
    u_xlat4.z = u_xlat2.x;
    u_xlat4.y = u_xlat3.x;
    u_xlat4.x = (-u_xlat2.x);
    u_xlat18.y = dot(u_xlat1.xz, u_xlat4.xy);
    u_xlat18.x = dot(u_xlat1.xz, u_xlat4.yz);
    u_xlat9.xz = u_xlat18.xy + vec2(0.5, 0.5);
    u_xlat16 = u_xlat24 * FX4OscillationSpeed;
    u_xlat16 = sin(u_xlat16);
    u_xlat2.xy = vec2(u_xlat16) * FX4Oscillation.xy + FX4Oscillation.zw;
    u_xlat2.xy = vec2(FX4ScrollXSpeed, FX4ScrollYSpeed) * vec2(u_xlat24) + u_xlat2.xy;
    u_xlat9.xz = u_xlat9.xz + u_xlat2.xy;
    vs_TEXCOORD2.zw = u_xlat9.xz * vec2(FX4ScaleX, FX4ScaleY);
    u_xlat9.xz = vec2(FX2RotationCenterX, FX2RotationCenterY) + vec2(0.5, 0.5);
    u_xlat9.xz = u_xlat0.xy + (-u_xlat9.xz);
    u_xlat9.xz = u_xlat9.xz * vec2(FX2ScaleX, FX2ScaleY);
    u_xlat16 = u_xlat24 * FX2OscillationSpeed;
    u_xlat16 = sin(u_xlat16);
    u_xlat2.xy = vec2(u_xlat16) * FX2Oscillation.xy + FX2Oscillation.zw;
    u_xlat16 = FX2RotationSpeed * u_xlat24 + u_xlat2.x;
    u_xlat2.xy = vec2(FX2ScrollXSpeed, FX2ScrollYSpeed) * vec2(u_xlat24) + u_xlat2.xy;
    u_xlat3.x = sin(u_xlat16);
    u_xlat4.x = cos(u_xlat16);
    u_xlat5.z = u_xlat3.x;
    u_xlat5.y = u_xlat4.x;
    u_xlat5.x = (-u_xlat3.x);
    u_xlat11.y = dot(u_xlat9.xz, u_xlat5.xy);
    u_xlat11.x = dot(u_xlat9.xz, u_xlat5.yz);
    u_xlat3.yz = u_xlat11.xy + vec2(0.5, 0.5);
    u_xlat4.x = sin(FX2ScrollAngle);
    u_xlat5.x = cos(FX2ScrollAngle);
    u_xlat6.z = u_xlat4.x;
    u_xlat6.y = u_xlat5.x;
    u_xlat6.x = (-u_xlat4.x);
    u_xlat12.y = dot(u_xlat1.xz, u_xlat6.xy);
    u_xlat12.x = dot(u_xlat1.xz, u_xlat6.yz);
    u_xlat9.xz = u_xlat12.xy + vec2(0.5, 0.5);
    u_xlat9.xz = u_xlat2.xy + u_xlat9.xz;
    u_xlat2.yz = u_xlat9.xz * vec2(FX2ScaleX, FX2ScaleY);
    u_xlatb16 = 0.0<FX2ScrollRotate;
    u_xlat9.x = u_xlat24 * FX2PulseRate;
    u_xlat9.x = sin(u_xlat9.x);
    u_xlat25 = u_xlat9.x + (-FX2PulseClip);
    u_xlat9.x = u_xlat9.x + FX2PulseClip;
    u_xlat9.x = u_xlat9.x * FX2PulseIntensity;
    u_xlat9.x = clamp(u_xlat9.x, 0.0, 1.0);
    u_xlat9.x = u_xlat9.x + -1.0;
    u_xlat2.x = FX2PulseAmount * u_xlat9.x + 1.0;
    u_xlat9.x = u_xlat25 * FX2PulseIntensity;
    u_xlat9.x = clamp(u_xlat9.x, 0.0, 1.0);
    u_xlat9.x = u_xlat9.x + -1.0;
    u_xlat3.x = FX2PulseAmount * u_xlat9.x + 1.0;
    u_xlat2.xyz = (bool(u_xlatb16)) ? u_xlat3.xyz : u_xlat2.xyz;
    vs_TEXCOORD3.y = u_xlat2.x;
    vs_TEXCOORD4.xy = u_xlat2.yz;
    u_xlat9.xz = vec2(FX3RotationCenterX, FX3RotationCenterY) + vec2(0.5, 0.5);
    u_xlat0.xy = u_xlat0.xy + (-u_xlat9.xz);
    u_xlat0.xy = u_xlat0.xy * vec2(FX3ScaleX, FX3ScaleY);
    u_xlat9.xz = vec2(u_xlat24) * vec2(FX3OscillationSpeed, FX3PulseRate);
    u_xlat9.xz = sin(u_xlat9.xz);
    u_xlat2.xy = u_xlat9.xx * FX3Oscillation.xy + FX3Oscillation.zw;
    u_xlat16 = FX3RotationSpeed * u_xlat24 + u_xlat2.x;
    u_xlat2.xy = vec2(FX3ScrollXSpeed, FX3ScrollYSpeed) * vec2(u_xlat24) + u_xlat2.xy;
    u_xlat3.x = sin(u_xlat16);
    u_xlat4.x = cos(u_xlat16);
    u_xlat5.z = u_xlat3.x;
    u_xlat5.y = u_xlat4.x;
    u_xlat5.x = (-u_xlat3.x);
    u_xlat11.y = dot(u_xlat0.xy, u_xlat5.xy);
    u_xlat11.x = dot(u_xlat0.xy, u_xlat5.yz);
    u_xlat0.yz = u_xlat11.xy + vec2(0.5, 0.5);
    u_xlat3.x = sin(FX3ScrollAngle);
    u_xlat4.x = cos(FX3ScrollAngle);
    u_xlat5.z = u_xlat3.x;
    u_xlat5.y = u_xlat4.x;
    u_xlat5.x = (-u_xlat3.x);
    u_xlat11.y = dot(u_xlat1.xz, u_xlat5.xy);
    u_xlat11.x = dot(u_xlat1.xz, u_xlat5.yz);
    u_xlat1.xy = u_xlat11.xy + vec2(0.5, 0.5);
    u_xlat1.xy = u_xlat2.xy + u_xlat1.xy;
    u_xlat1.yz = u_xlat1.xy * vec2(FX3ScaleX, FX3ScaleY);
    u_xlatb2 = 0.0<FX3ScrollRotate;
    u_xlat10 = u_xlat9.z + (-FX3PulseClip);
    u_xlat25 = u_xlat9.z + FX3PulseClip;
    u_xlat25 = u_xlat25 * FX3PulseIntensity;
    u_xlat25 = clamp(u_xlat25, 0.0, 1.0);
    u_xlat25 = u_xlat25 + -1.0;
    u_xlat1.x = FX3PulseAmount * u_xlat25 + 1.0;
    u_xlat25 = u_xlat10 * FX3PulseIntensity;
    u_xlat25 = clamp(u_xlat25, 0.0, 1.0);
    u_xlat25 = u_xlat25 + -1.0;
    u_xlat0.x = FX3PulseAmount * u_xlat25 + 1.0;
    u_xlat0.xyz = (bool(u_xlatb2)) ? u_xlat0.xyz : u_xlat1.xyz;
    vs_TEXCOORD3.z = u_xlat0.x;
    vs_TEXCOORD4.zw = u_xlat0.yz;
    u_xlat0.x = u_xlat24 * FX1PulseRate;
    u_xlat0.y = u_xlat24 * FX4PulseRate;
    u_xlat0.xy = sin(u_xlat0.xy);
    u_xlat8 = u_xlat0.y + FX4PulseClip;
    u_xlat8 = u_xlat8 * FX4PulseIntensity;
    u_xlat8 = clamp(u_xlat8, 0.0, 1.0);
    u_xlat8 = u_xlat8 + -1.0;
    vs_TEXCOORD3.w = FX4PulseAmount * u_xlat8 + 1.0;
    u_xlat0.x = u_xlat0.x + FX1PulseClip;
    u_xlat0.x = u_xlat0.x * FX1PulseIntensity;
    u_xlat0.x = clamp(u_xlat0.x, 0.0, 1.0);
    u_xlat0.x = u_xlat0.x + -1.0;
    vs_TEXCOORD3.x = FX1PulseAmount * u_xlat0.x + 1.0;
    vs_TEXCOORD5.zw = vec2(0.0, 0.0);
    u_xlat0 = 1.0 * vec4(2.0, 2.0, 2.0, 2.0) + vec4(0.0);
    u_xlat0 = u_xlat0 * vec4(1.10000002, 1.10000002, 1.10000002, 1.10000002) + vec4(-1.0, -1.0, -1.0, -1.0);
    vs_COLOR0 = vec4(vec4(LightingBlend, LightingBlend, LightingBlend, LightingBlend)) * u_xlat0 + vec4(1.0, 1.0, 1.0, 1.0);

	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
}



















