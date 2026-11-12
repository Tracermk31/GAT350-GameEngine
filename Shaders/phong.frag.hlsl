#include "Lighting.hlsli"
#include "Uniforms.hlsli"

Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);

cbuffer FrameUniforms : register(FRAME_SLOT, FRAGMENT_UNIFORM_SPACE) {
    Frame frame;
}

cbuffer LightUniforms : register(LIGHT_SLOT, FRAGMENT_UNIFORM_SPACE) {
    Lighting lights;
}

cbuffer MaterialUniforms : register(MATERIAL_SLOT, FRAGMENT_UNIFORM_SPACE) {
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
    float3 viewDirection = normalize(frame.cameraPosition - input.worldPosition);
   
    float3 diffuseLighting = lights.ambient;
    float3 specularLighting = 0;
    
    for (uint index = 0; index < lights.numLights; index++) {
        calculateLighting(lights.lights[index], material, input.worldPosition, normalize(input.normal), viewDirection, diffuseLighting, specularLighting);
    }
    
    output.color = float4(1, 1, 1, 1);
    //float4(albedo.rgb * diffuseLighting + specularLighting, albedo.a);
  
	return output;
}
