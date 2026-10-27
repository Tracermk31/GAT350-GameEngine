#include "Lighting.hlsli"

Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);

cbuffer MaterialUniforms : register(b0, space3) {
    Material material;
}

struct Input {
    float2 uv : TEXCOORD0;
    float3 diffuseLighting : TEXCOORD001;
    float3 specular : TEXCOORD002;
};

struct Output {
	float4 color : SV_Target0;
};

Output main(Input input) {
	Output output;
    float4 albedo = u_texture.Sample(u_sampler, input.uv) * material.colorMask;
    output.color = float4(albedo.rgb * input.diffuseLighting + input.specular, albedo.a);
  
	return output;
}
