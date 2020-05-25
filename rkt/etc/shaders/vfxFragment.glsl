precision highp float;
precision highp int;

varying vec2 vs_TEXCOORD0;
varying vec2 vs_TEXCOORD1;
varying vec4 vs_TEXCOORD2;
varying vec4 vs_TEXCOORD3;
varying vec4 vs_TEXCOORD4;
varying vec4 vs_TEXCOORD5;
varying vec4 vs_COLOR0;

uniform float time;

const float PI = 3.1415926535897932384626433832795;

uniform vec4 FX1Color;
uniform float FX1Intensity;
uniform float FX1Invert;
uniform float FX1DistortionAmount;
uniform float FX1PulseAmount;
uniform float FX1PulseRate;
uniform float FX1PulseIntensity;
uniform float FX1PulseClip;
uniform float FX1ScrollRotateFlow;
uniform float FX1ScrollXSpeed;
uniform float FX1ScrollYSpeed;
uniform float FX1RotationSpeed;
uniform float FX1FlowAngle;
uniform float FX1FlowMapXOffset;
uniform float FX1FlowMapYOffset;
uniform float FX1FlowMapScrollXSpeed;
uniform float FX1FlowMapScrollYSpeed;
uniform float FX1FlowMapScaleXSpeed;
uniform float FX1FlowMapScaleYSpeed;
uniform float FX1ScaleX;
uniform float FX1ScaleY;
uniform float FX1ScrollAngle;

uniform vec4 FX2Color;
uniform float FX2Intensity;
uniform float FX2Invert;
uniform float FX2Blend;
uniform float FX2DistortionAmount;
uniform float FX2RotationSpeed;
uniform float FX2RotationCenterX;
uniform float FX2RotationCenterY;
uniform float FX2ScaleX;
uniform float FX2ScaleY;

uniform vec4 FX3Color;
uniform float FX3Intensity;
uniform float FX3ColorIntensity;
uniform float FX3Invert;
uniform float FX3Blend;
uniform float FX3DistortionAmount;
uniform float FX3PulseAmount;
uniform float FX3PulseRate;
uniform float FX3PulseIntensity;
uniform float FX3PulseClip;
uniform float FX3RotationSpeed;
uniform float FX3RotationCenterX;
uniform float FX3RotationCenterY;
uniform float FX3ScaleX;
uniform float FX3ScaleY;

uniform vec4 FX4Color;
uniform float FX4Intensity;
uniform float FX4ColorIntensity;

uniform float FXBrightness;
uniform float FXIntensity;
uniform float FX4AddAlpha;
uniform vec3 DistortionVector;

uniform sampler2D baseTexture;
uniform sampler2D maskTex;
uniform sampler2D FX1Texture;
uniform sampler2D FX1FlowTexture;
uniform sampler2D FX2Texture;
uniform sampler2D FX3Texture;
uniform sampler2D FX4Texture;

uniform float globalAlpha;

vec2 constantBiasScale(vec2 uv, float bias, float scale) {
	return (uv - vec2(bias)) * scale;
}

vec4 u_xlat0;
vec4 u_xlat10_0;
vec3 u_xlat1;
vec4 u_xlat10_1;
vec4 u_xlat2;
vec4 u_xlat10_2;
vec4 u_xlat3;
vec4 u_xlat10_3;
vec3 u_xlat4;
vec3 u_xlat5;
vec3 u_xlat6;
float u_xlat12;
float u_xlat16_12;
bool u_xlatb12;

float maxAlpha = 0.0;

void main(){
	u_xlat10_0 = texture2D(FX1FlowTexture, vs_TEXCOORD2.xy);
    u_xlatb12 = 1.0<FX1ScrollRotateFlow;
    u_xlat0.xyz = (bool(u_xlatb12)) ? u_xlat10_0.xyz : vec3(1.0, 1.0, 1.0);
    u_xlat1.x = u_xlat0.x * FX1ScaleX;
    u_xlat1.y = u_xlat0.y * FX1ScaleY;
    u_xlat0.xy = u_xlat1.xy + vs_TEXCOORD5.xy;
    u_xlat0.xy = (bool(u_xlatb12)) ? u_xlat0.xy : vs_TEXCOORD2.xy;
    u_xlat10_1 = texture2D(FX1Texture, u_xlat0.xy);
    float FX1Alpha = clamp(u_xlat10_1.w, 0.0, 1.0);
    u_xlat0.xyw = (-u_xlat10_1.xyz) + vec3(vec3(FX1Invert, FX1Invert, FX1Invert));
    u_xlat4.xyz = u_xlat0.zzz * abs(u_xlat0.xyw);
    u_xlat0.x = abs(u_xlat0.x) + -0.5;
    u_xlat4.xyz = u_xlat4.xyz * FX1Color.xyz;
    u_xlat4.xyz = u_xlat4.xyz * FX1Color.www;
    u_xlat0.yzw = u_xlat4.xyz * vec3(FX1Intensity);
    u_xlat10_1 = texture2D(maskTex, vs_TEXCOORD0.xy);
    vec4 maskPixel = u_xlat10_1;
    u_xlat0 = u_xlat0 * u_xlat10_1.xxxx;
    u_xlat10_2 = texture2D(FX2Texture, vs_TEXCOORD4.xy);
    float FX2Alpha = clamp(u_xlat10_2.w, 0.0, 1.0);
    u_xlat2.xyz = (-u_xlat10_2.xyz) + vec3(vec3(FX2Invert, FX2Invert, FX2Invert));
    u_xlat6.xyz = abs(u_xlat2.xyz) * FX2Color.xyz;
    u_xlat2.x = abs(u_xlat2.x) + -0.5;
    u_xlat2.x = u_xlat10_1.y * u_xlat2.x;
    u_xlat2.yzw = u_xlat6.xyz * FX2Color.www;
    u_xlat2 = u_xlat2 * vec4(FX2DistortionAmount, FX2Intensity, FX2Intensity, FX2Intensity);
    u_xlat6.xyz = u_xlat10_1.yyy * u_xlat2.yzw;
    u_xlat6.xyz = u_xlat6.xyz * vs_TEXCOORD3.yyy;
    u_xlat3.xyz = u_xlat0.yzw * vs_TEXCOORD3.xxx + u_xlat6.xyz;
    u_xlat4.xyz = u_xlat0.yzw * vs_TEXCOORD3.xxx;
    u_xlat3.xyz = u_xlat3.xyz * vec3(0.5, 0.5, 0.5);
    u_xlat4.xyz = u_xlat4.xyz * u_xlat6.xyz + (-u_xlat3.xyz);
    u_xlat4.xyz = vec3(vec3(FX2Blend, FX2Blend, FX2Blend)) * u_xlat4.xyz + u_xlat3.xyz;
    u_xlat10_3 = texture2D(FX3Texture, vs_TEXCOORD4.zw);
    float FX3Alpha = clamp(u_xlat10_3.w, 0.0, 1.0);
    u_xlat3 = (-u_xlat10_3) + vec4(vec4(FX3Invert, FX3Invert, FX3Invert, FX3Invert));
    u_xlat6.x = abs(u_xlat3.x) + -0.5;
    u_xlat3 = abs(u_xlat3) * FX3Color;
    u_xlat6.x = u_xlat10_1.z * u_xlat6.x;
    u_xlat2.x = u_xlat6.x * FX3DistortionAmount + u_xlat2.x;
    u_xlat0.x = u_xlat0.x * FX1DistortionAmount + u_xlat2.x;
    u_xlat2.xy = vec2(DistortionVector.x, DistortionVector.y) * u_xlat0.xx + vs_TEXCOORD0.xy;
    u_xlat10_2 = texture2D(baseTexture, u_xlat2.xy);
    float baseTexAlpha = clamp(u_xlat10_2.w, 0.0, 1.0);
    u_xlat0.xyz = u_xlat4.xyz + u_xlat10_2.xyz;
    u_xlat0.xyz = vec3(vec3(FXBrightness, FXBrightness, FXBrightness)) * vec3(FXIntensity) + u_xlat0.xyz;
    u_xlat0.xyz = (-u_xlat10_2.xyz) + u_xlat0.xyz;
    u_xlat16_12 = u_xlat10_1.y + u_xlat10_1.x;
    u_xlat16_12 = clamp(u_xlat16_12, 0.0, 1.0);
    u_xlat0.xyz = vec3(u_xlat16_12) * u_xlat0.xyz + u_xlat10_2.xyz;
    u_xlat2.xyz = u_xlat3.xyz * vec3(vec3(FX3ColorIntensity, FX3ColorIntensity, FX3ColorIntensity)) + (-u_xlat0.xyz);
    u_xlat12 = u_xlat10_1.z * u_xlat3.w;
    u_xlat1.x = u_xlat10_1.w * vs_TEXCOORD3.w;
    u_xlat1.x = u_xlat1.x * FX4Intensity;
    u_xlat12 = u_xlat12 * vs_TEXCOORD3.z;
    u_xlat12 = u_xlat12 * FX3Intensity;
    u_xlat0.xyz = vec3(u_xlat12) * u_xlat2.xyz + u_xlat0.xyz;
    u_xlat10_2 = texture2D(FX4Texture, vs_TEXCOORD2.zw);
    float FX4Alpha = clamp(u_xlat10_2.w, 0.0, 1.0);
    u_xlat2 = u_xlat10_2 * FX4Color;
    u_xlat5.xyz = u_xlat2.xyz * vec3(vec3(FX4ColorIntensity, FX4ColorIntensity, FX4ColorIntensity)) + (-u_xlat0.xyz);
    u_xlat5.xyz = u_xlat2.www * u_xlat5.xyz + u_xlat0.xyz;
    u_xlat5.xyz = clamp(u_xlat5.xyz, 0.0, 1.0);
    u_xlat2.xyz = u_xlat2.xyz * vec3(vec3(FX4ColorIntensity, FX4ColorIntensity, FX4ColorIntensity)) + u_xlat0.xyz;
    u_xlat0.xyz = u_xlat0.xyz;
    u_xlat0.xyz = clamp(u_xlat0.xyz, 0.0, 1.0);
    u_xlat5.xyz = u_xlat5.xyz + (-u_xlat2.xyz);
    u_xlat5.xyz = vec3(vec3(FX4AddAlpha, FX4AddAlpha, FX4AddAlpha)) * u_xlat5.xyz + u_xlat2.xyz;
    u_xlat5.xyz = (-u_xlat0.xyz) + u_xlat5.xyz;
    u_xlat0.xyz = u_xlat1.xxx * u_xlat5.xyz + u_xlat0.xyz;
    u_xlat1.xyz = u_xlat0.xyz + vec3(0.150000006, 0.150000006, 0.150000006);
    u_xlat1.xyz = u_xlat1.xyz * vs_COLOR0.xyz;
    u_xlat0.xyz = min(u_xlat0.xyz, u_xlat1.xyz);

    maxAlpha = baseTexAlpha;
    maxAlpha = max(FX1Alpha * maskPixel.x, maxAlpha);
    maxAlpha = max(FX2Alpha * maskPixel.y, maxAlpha);
    maxAlpha = max(FX3Alpha * maskPixel.z, maxAlpha);
    maxAlpha = max(FX4Alpha * maskPixel.w, maxAlpha);

	gl_FragColor.xyz = u_xlat0.xyz;
    gl_FragColor.w = min(maxAlpha, globalAlpha);
}
