#pragma once

#define LIGHT_DIRECTIONAL	0
#define LIGHT_POINT			1
#define LIGHT_SPOT			2

#define MAX_LIGHTS          8

struct Material {
    float4 baseMap;
	float2 uvTiling;
	float2 offset;
    float shininess;
    float3 padding;
};

struct Light {
	float3 position;
	uint type;
    
	float3 direction;
	float range;
    
	float3 color;
	float intensity;
    
    float innerCutoff;
	float outerCutoff;
    float2 padding;
};

float calculatAttenuation(float distance, float range) {
    return pow(1 - saturate(distance / range), 2);
}

float3 getLightVector(Light light, float3 worldPosition, out float attenuation) {
    float3 lightWorldPosition = 0.0f;
    float3 toLight = 0.0f;
    float distance = 0.0f;
    attenuation = 1.0f;
    
    switch (light.type) {
        case 0:
            lightWorldPosition = normalize(-light.direction);
            break;
        case 1:
            toLight = light.position - worldPosition;
            distance = length(toLight);
            attenuation = calculatAttenuation(distance, light.range);
        
            lightWorldPosition = toLight/distance;
            break;
        case 2:
            toLight = light.position - worldPosition;
            distance = length(toLight);
            lightWorldPosition = toLight / distance;
        
            attenuation = calculatAttenuation(distance, light.range);
            attenuation *= smoothstep(light.outerCutoff, light.innerCutoff, dot(-lightWorldPosition, light.direction));
            break;
    }
    return lightWorldPosition;
}

float3 calculateDiffuseLighting(float3 normals, float3 lightWorldPosition, float3 radiance) {
    return radiance * saturate(dot(normals, lightWorldPosition));
}

float3 calculateSpecularLighting(float3 radiance, float3 viewDirection, float3 normals, float3 lightWorldPosition, Material material) {
    float3 specular = { 0.0f, 0.0f, 0.0f };
    float normalizedLighting = saturate(dot(normals, lightWorldPosition));
    if (normalizedLighting > 0) {
        //Blinn-Phong Specular
        float3 halfwayVector = normalize(viewDirection + lightWorldPosition);
        float specularLighting = saturate(dot(halfwayVector, normals));

        specular = pow(specularLighting, material.shininess) * radiance;
    }
    return specular;
}

void calculateLighting(Light light, Material material, float3 position, float3 normals, float3 viewDirection, out float3 diffuse, out float3 specular) {
    float attenuation;
    float3 lightWorldPosition = getLightVector(light, position, attenuation);

    // light arriving at the surface
    float3 radiance = light.color * light.intensity * attenuation;

    diffuse += calculateDiffuseLighting(normals, lightWorldPosition, radiance);
    specular += calculateSpecularLighting(radiance, viewDirection, normals, lightWorldPosition, material);
}
