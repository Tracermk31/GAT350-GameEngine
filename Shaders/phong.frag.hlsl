#include "Lighting.hlsli"
#include "Uniforms.hlsli"

Texture2D<float4> base_texture : register(t0, FRAGMENT_TEXTURE_SPACE);
SamplerState base_sampler : register(s0, FRAGMENT_TEXTURE_SPACE);

Texture2D<float4> specular_texture : register(t1, FRAGMENT_TEXTURE_SPACE);
SamplerState specular_sampler : register(s1, FRAGMENT_TEXTURE_SPACE);

Texture2D<float4> emissive_texture : register(t2, FRAGMENT_TEXTURE_SPACE);
SamplerState emissive_sampler : register(s2, FRAGMENT_TEXTURE_SPACE);

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
    
    float specularMask = specular_texture.Sample(specular_sampler, input.uv).r;
    
    float3 emissiveMask = (emissive_texture.Sample(emissive_sampler, input.uv).rgb * material.emissiveColor);
    
    float4 albedo = base_texture.Sample(base_sampler, input.uv) * material.baseColor;
    float3 viewDirection = normalize(frame.cameraPosition - input.worldPosition);
   
    float3 diffuseLighting = lights.ambient;
    float3 specularLighting = 0;
    
    for (uint index = 0; index < lights.numLights; index++) {
        calculateLighting(lights.lights[index], material, input.worldPosition, normalize(input.normal), viewDirection, diffuseLighting, specularLighting);
    }
    
    output.color = float4((albedo.rgb * diffuseLighting) + (specularLighting * material.specularColor * specularMask) + emissiveMask, albedo.a);
  
	return output;
}
