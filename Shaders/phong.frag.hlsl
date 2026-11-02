#include "Lighting.hlsli"

Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);


cbuffer VertexUniforms : register(b0, space3) {
    float4x4 mvp;
    float4x4 worldMatrix;
    float3 cameraPosition;
    float padding1;
}

cbuffer LightUniforms : register(b1, space3) {
    Light lights[MAX_LIGHTS];
    uint numLights;
    float3 ambient;
}

cbuffer MaterialUniforms : register(b2, space3) {
    Material material;
}

struct Input {
    float2 uv : TEXCOORD0;
    float3 normal : TEXCOORD001;
    float3 worldPosition : TEXCOORD002;
};

struct Output {
	float4 color : SV_Target0;
};

Output main(Input input) {
	Output output;
    float4 albedo = u_texture.Sample(u_sampler, input.uv) * material.baseMap;
    float3 viewDirection = normalize(cameraPosition - input.worldPosition);
   
    float3 diffuseLighting = ambient;
    float3 specularLighting = 0;
    
    for (uint index = 0; index < numLights; index++) {
        calculateLighting(lights[index], material, input.worldPosition, normalize(input.normal), viewDirection, diffuseLighting, specularLighting);
    }
    
    output.color = float4(albedo.rgb * diffuseLighting + specularLighting, albedo.a);
  
	return output;
}
