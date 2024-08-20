#version 330 core
#extension GL_ARB_shading_language_include : require

struct PointLight {
  mat3 ads;
  vec3 atten;

  vec3 position;
};

struct DirectionalLight {
  mat3 ads;
  vec3 atten;

  vec3 direction;
};

struct SpotLight {
  mat3 ads;
  vec3 atten;

  vec3 position;
  vec3 direction;

  vec2 cutoff;
};

// 16 PointLights
uniform int PointLightCount;

#include "/PointLight_0"
#include "/PointLight_1"
#include "/PointLight_2"
#include "/PointLight_3"
#include "/PointLight_4"
#include "/PointLight_5"
#include "/PointLight_6"
#include "/PointLight_7"
#include "/PointLight_8"
#include "/PointLight_9"
#include "/PointLight_10"
#include "/PointLight_11"
#include "/PointLight_12"
#include "/PointLight_13"
#include "/PointLight_14"
#include "/PointLight_15"

// 16 DirectionalLight
uniform int DirectionalLightCount;

#include "/DirectionalLight_0"
#include "/DirectionalLight_1"
#include "/DirectionalLight_2"
#include "/DirectionalLight_3"
#include "/DirectionalLight_4"
#include "/DirectionalLight_5"
#include "/DirectionalLight_6"
#include "/DirectionalLight_7"
#include "/DirectionalLight_8"
#include "/DirectionalLight_9"
#include "/DirectionalLight_10"
#include "/DirectionalLight_11"
#include "/DirectionalLight_12"
#include "/DirectionalLight_13"
#include "/DirectionalLight_14"
#include "/DirectionalLight_15"

// 4 SpotLight
uniform int SpotLightCount;

#include "/SpotLight_0"
#include "/SpotLight_1"
#include "/SpotLight_2"
#include "/SpotLight_3"

uniform sampler2D diffuseMap;
// uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform float shininess;

in BlinnPhong {
  vec3 pos_frag;
  vec3 norm_frag;
  vec2 uv;
} fs_in;

vec3 CalcAmbient(vec3 color) {
  return color;
}

vec3 CalcDiffuse(vec3 color, vec3 normal, vec3 lightDir) {
  return color * max(dot(normal, lightDir), 0.0);
}

vec3 CalcSpecular(vec3 color, vec3 normal, vec3 lightDir, vec3 viewDir, float shininess) {
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
  return color * spec;
}

float CalcAttenuation(float dist, vec3 atten) {
  return 1.0 / (atten.x + atten.y * dist + atten.z * dist * dist);
}

vec3 CalcPointLight(PointLight light, vec2 uv, vec3 normal, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fs_in.pos_frag);
  vec3 color = CalcAmbient(texture2D(diffuseMap, uv).rgb) +
    CalcDiffuse(texture2D(diffuseMap, uv).rgb, normal, lightDir) +
    CalcSpecular(texture2D(specularMap, uv).rgb, normal, lightDir, viewDir, shininess);
  return color * CalcAttenuation(distance(fs_in.pos_frag, light.position), light.atten);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec2 uv, vec3 normal, vec3 viewDir) {
  vec3 lightDir = normalize(-light.direction);
  vec3 color = CalcAmbient(texture2D(diffuseMap, uv).rgb) +
    CalcDiffuse(texture2D(diffuseMap, uv).rgb, normal, lightDir) +
    CalcSpecular(texture2D(specularMap, uv).rgb, normal, lightDir, viewDir, shininess);
  return color;
}

vec3 CalcSpotLight(SpotLight light, vec2 uv, vec3 normal, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fs_in.pos_frag);
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutoff.y - light.cutoff.x;
  float intensity = clamp((theta - light.cutoff.x) / epsilon, 0.0, 1.0);
  if(intensity > 0.0) {
    vec3 color = CalcAmbient(texture2D(diffuseMap, uv).rgb) +
      CalcDiffuse(texture2D(diffuseMap, uv).rgb, normal, lightDir) +
      CalcSpecular(texture2D(specularMap, uv).rgb, normal, lightDir, viewDir, shininess);
    return color * intensity * CalcAttenuation(distance(fs_in.pos_frag, light.position), light.atten);
  } else {
    return CalcAmbient(texture2D(diffuseMap, uv).rgb);
  }
}

vec3 CalcLight(vec2 uv, vec3 normal, vec3 viewDir) {
  vec3 result = vec3(0.0);
  switch(PointLightCount) {
    case 16:
      result += CalcPointLight(PointLight_15, uv, normal, viewDir);
    case 15:
      result += CalcPointLight(PointLight_14, uv, normal, viewDir);
    case 14:
      result += CalcPointLight(PointLight_13, uv, normal, viewDir);
    case 13:
      result += CalcPointLight(PointLight_12, uv, normal, viewDir);
    case 12:
      result += CalcPointLight(PointLight_11, uv, normal, viewDir);
    case 11:
      result += CalcPointLight(PointLight_10, uv, normal, viewDir);
    case 10:
      result += CalcPointLight(PointLight_9, uv, normal, viewDir);
    case 9:
      result += CalcPointLight(PointLight_8, uv, normal, viewDir);
    case 8:
      result += CalcPointLight(PointLight_7, uv, normal, viewDir);
    case 7:
      result += CalcPointLight(PointLight_6, uv, normal, viewDir);
    case 6:
      result += CalcPointLight(PointLight_5, uv, normal, viewDir);
    case 5:
      result += CalcPointLight(PointLight_4, uv, normal, viewDir);
    case 4:
      result += CalcPointLight(PointLight_3, uv, normal, viewDir);
    case 3:
      result += CalcPointLight(PointLight_2, uv, normal, viewDir);
    case 2:
      result += CalcPointLight(PointLight_1, uv, normal, viewDir);
    case 1:
      result += CalcPointLight(PointLight_0, uv, normal, viewDir);
    case 0:
      break;
  }

  switch(DirectionalLightCount) {
    case 16:
      result += CalcDirectionalLight(DirectionalLight_15, uv, normal, viewDir);

    case 15:
      result += CalcDirectionalLight(DirectionalLight_14, uv, normal, viewDir);
    case 14:
      result += CalcDirectionalLight(DirectionalLight_13, uv, normal, viewDir);
    case 13:
      result += CalcDirectionalLight(DirectionalLight_12, uv, normal, viewDir);
    case 12:
      result += CalcDirectionalLight(DirectionalLight_11, uv, normal, viewDir);
    case 11:
      result += CalcDirectionalLight(DirectionalLight_10, uv, normal, viewDir);
    case 10:
      result += CalcDirectionalLight(DirectionalLight_9, uv, normal, viewDir);
    case 9:
      result += CalcDirectionalLight(DirectionalLight_8, uv, normal, viewDir);
    case 8:
      result += CalcDirectionalLight(DirectionalLight_7, uv, normal, viewDir);
    case 7:
      result += CalcDirectionalLight(DirectionalLight_6, uv, normal, viewDir);
    case 6:
      result += CalcDirectionalLight(DirectionalLight_5, uv, normal, viewDir);
    case 5:
      result += CalcDirectionalLight(DirectionalLight_4, uv, normal, viewDir);
    case 4:
      result += CalcDirectionalLight(DirectionalLight_3, uv, normal, viewDir);
    case 3:
      result += CalcDirectionalLight(DirectionalLight_2, uv, normal, viewDir);
    case 2:
      result += CalcDirectionalLight(DirectionalLight_1, uv, normal, viewDir);
    case 1:
      result += CalcDirectionalLight(DirectionalLight_0, uv, normal, viewDir);
    case 0:
      break;
  }

  switch(SpotLightCount) {
    case 4:
      result += CalcSpotLight(SpotLight_3, uv, normal, viewDir);
    case 3:
      result += CalcSpotLight(SpotLight_2, uv, normal, viewDir);
    case 2:
      result += CalcSpotLight(SpotLight_1, uv, normal, viewDir);
    case 1:
      result += CalcSpotLight(SpotLight_0, uv, normal, viewDir);
    case 0:
      break;
  }

}

out vec4 FragColor;

uniform vec3 camPos;


void main() {
  FragColor = vec4(CalcLight(fs_in.uv, fs_in.norm_frag, normalize(camPos - fs_in.pos_frag)), 1.0);
}