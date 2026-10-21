Texture2D<float4> u_texture : register(t0, space2);
SamplerState u_sampler : register(s0, space2);

cbuffer Uniforms : register(b0, space3) {
    float4 mask;
};

struct Input {
    float2 uv : TEXCOORD0;
};

struct Output {
	float4 color : SV_Target0;
};

Output main(Input input) {
	Output output;
    output.color = u_texture.Sample(u_sampler, input.uv) * mask;
  
	return output;
}
