#include "Lighting.hlsli"
#include "Uniforms.hlsli"

Texture2D<float4> base_texture_zero : register(t0, FRAGMENT_TEXTURE_SPACE);
SamplerState base_sampler_zero : register(s0, FRAGMENT_TEXTURE_SPACE);

Texture2D<float4> base_texture_one : register(t1, FRAGMENT_TEXTURE_SPACE);
SamplerState base_sampler_one : register(s1, FRAGMENT_TEXTURE_SPACE);

//Texture2D<float4> base_texture_two : register(t2, FRAGMENT_TEXTURE_SPACE);
//SamplerState base_sampler_two : register(s2, FRAGMENT_TEXTURE_SPACE);

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
    
    //float mask = base_texture_two.Sample(base_sampler_two, input.uv).r;
    float4 albedo_zero = base_texture_zero.Sample(base_sampler_zero, input.uv) * material.baseMap;
    float4 albedo_one = base_texture_one.Sample(base_sampler_one, input.uv) * material.baseMap;
    float4 albedo = lerp(albedo_zero, albedo_one, 0.5f);
    
    float3 viewDirection = normalize(frame.cameraPosition - input.worldPosition);
   
    float3 diffuseLighting = lights.ambient;
    float3 specularLighting = 0;
    
    for (uint index = 0; index < lights.numLights; index++) {
        calculateLighting(lights.lights[index], material, input.worldPosition, normalize(input.normal), viewDirection, diffuseLighting, specularLighting);
    }
    
    output.color = float4(albedo.rgb * diffuseLighting + specularLighting, albedo.a);
  
	return output;
}
