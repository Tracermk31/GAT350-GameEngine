#include "Lighting.hlsli"
#include "Uniforms.hlsli"

cbuffer ObjectUniforms : register(OBJECT_SLOT, VERTEX_UNIFORM_SPACE) {
    Object object;
}

cbuffer FrameUniforms : register(FRAME_SLOT, VERTEX_UNIFORM_SPACE) {
    Frame frame;
}

cbuffer LightUniforms : register(LIGHT_SLOT, VERTEX_UNIFORM_SPACE) {
    Lighting lights;    
}

cbuffer MaterialUniforms : register(MATERIAL_SLOT, VERTEX_UNIFORM_SPACE) {
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
    
    output.worldPosition = mul(object.model, float4(input.position, 1.0f)).xyz;
    output.position = mul(frame.viewProjection, float4(output.worldPosition, 1.0f));
    
    output.normal = normalize(mul((float3x3) object.model, input.normal));
    
    return output;
}