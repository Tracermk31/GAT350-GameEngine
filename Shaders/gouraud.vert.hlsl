#include "Lighting.hlsli"

cbuffer VertexUniforms : register(b0, space1) {
    float4x4 mvp;
    float4x4 worldMatrix;
    float3 cameraPosition;
    float padding1;
}

cbuffer LightUniforms : register(b1, space1) {
    Light light;
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
    float3 diffuseLighting : TEXCOORD001;
    float3 specular : TEXCOORD002;
};

Output main(Input input) {
    Output output;
    output.uv = (input.uv * material.uvTiling) + material.offset;
    output.position = mul(mvp, float4(input.position, 1.0f));
    
    float3 normals = normalize(mul((float3x3) worldMatrix, input.normal));
    float3 worldPosition = mul(worldMatrix, float4(input.position, 1.0f)).xyz;
    
    float attenuation;
    float3 lightWorldPosition = getLightVector(light, worldPosition, attenuation);
    float3 radiance = light.color * light.intensity;
    
    // DIFFUSE
    float normalizedLighting = saturate(dot(normals, lightWorldPosition));
    float3 diffuseLighting = radiance * normalizedLighting * attenuation;
    
    output.diffuseLighting = light.ambient + diffuseLighting;
    
    //SPECULAR
    if (normalizedLighting > 0) {
        float3 specularReflection = reflect(-lightWorldPosition, normals);
        float3 viewDirection = normalize(cameraPosition - worldPosition);
        
        //Blinn-Phong Specular
        //float3 halfwayVector = normalize(viewDirection + lightWorldPosition);
        
        float specularLighting = saturate(dot(specularReflection, viewDirection));

        output.specular = pow(specularLighting, material.shininess) * radiance * attenuation;
    } else {
        output.specular = float3(0.0f, 0.0f, 0.0f);
    }
    return output;
}