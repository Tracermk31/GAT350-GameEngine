cbuffer Uniforms : register(b0, space3)
{
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
    output.color = mask;
    
	return output;
}
