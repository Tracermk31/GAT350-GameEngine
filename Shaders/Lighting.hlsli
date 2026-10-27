#pragma once

#define LIGHT_DIRECTIONAL	0
#define LIGHT_POINT			1
#define LIGHT_SPOT			2

struct Material {
    float4 colorMask;
	float2 uvTiling;
	float2 offset;
    float shininess;
};

struct Light {
	float3 position;
	uint type;
	float3 direction;
	float innerCutoff;
	float3 color;
	float intensity;
	float3 ambient;
	float outerCutoff;
};

float3 getLightVector(Light light, float3 worldPosition, out float attenuation) {
    float3 lightWorldPosition;
    attenuation = 1.0f;
    
    switch (light.type) {
        case 0:
            lightWorldPosition = normalize(-light.direction);
            break;
        case 1:
            lightWorldPosition = normalize(light.position - worldPosition);
            break;
        case 2:
            lightWorldPosition = normalize(light.position - worldPosition);
            attenuation = smoothstep(light.outerCutoff, light.innerCutoff, dot(lightWorldPosition, light.direction));
            break;
    }
    return lightWorldPosition;
}
