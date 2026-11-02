#include "Lighting.hlsli"

cbuffer VertexUniforms : register(b0, space1) {
    float4x4 mvp;
    float4x4 worldMatrix;
    float3 cameraPosition;
    float padding1;
}

cbuffer LightUniforms : register(b1, space1) {
    Light lights[MAX_LIGHTS];
    uint numLights;
    float3 ambient;    
}

cbuffer MaterialUniforms : register(b2, space1) {
    Material material;
}

struct Input {
    float3 position : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float3 normal : TEXCOORD2;
    //float3 tanget : TEXCOORD3;
};

struct Output {
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD001;
    float3 worldPosition : TEXCOORD002;
};

Output main(Input input) {
    Output output;
    output.uv = (input.uv * material.uvTiling) + material.offset;
    output.position = mul(mvp, float4(input.position, 1.0f));
    
    output.normal = normalize(mul((float3x3) worldMatrix, input.normal));
    output.worldPosition = mul(worldMatrix, float4(input.position, 1.0f)).xyz;
    
    return output;
}