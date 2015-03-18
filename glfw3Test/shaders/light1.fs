#version 130

#define MAX_LIGHTS 6

struct GLMaterial {
  vec3 Kd;
  vec3 Ka;
  vec3 Ks;
  float Ns;
  sampler2D tex;
};

struct GLLight {
  // 0 Directional, 1 Point, 2 Spot, 3 Area
  int type;

  // Color of the light emitted
  vec3 La;  // Ambient color
  vec3 Ld;  // Diffuse color
  vec3 Ls;  // Specular color

  // Spot and Point Lights
  vec3 Pos;
  // Spot and Directional Lights
  vec3 Direction;

  // Spot light only
  float SpotAngle;
  float SpotCosCutoff;
  float SpotExponent;

  // Point Light Only
  float Ac;  // Constant Attenuation
  float Ab;  // Linear Attenuation
  float Aa;  // Quadratic Attenuation
};

// Interpolated values from the vertex shaders
in vec3 VertexView;
in vec3 NormalView;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform int NLights;
uniform GLLight Lights[MAX_LIGHTS];
uniform GLMaterial Material;
uniform mat4 V;

void main() {
  color = vec4(0, 0, 0, 0);
  for (int i = 0; i < NLights; ++i) {
    GLLight Light = Lights[i];
    vec3 ColorA = Light.La + Material.Ka;  // Ambient Color
    vec3 ColorD = vec3(0);                 // Diffuse Color
    vec3 ColorS = vec3(0);                 // Specular Color

    vec3 LightDirection;
    vec3 LightDistance;
    if (Light.type == 0) {  // directional light
      LightDirection = -normalize((V * vec4(Light.Direction, 1)).xyz);
    }
    if (Light.type == 1) {  // point light
      LightDistance = (V * vec4(Light.Pos, 1)).xyz - VertexView;
      LightDirection = normalize(LightDistance);
    }

    vec3 NNormalView = normalize(NormalView);
    float fd = dot(NNormalView, LightDirection);
    if (fd > 0) {
      ColorD = fd * Light.Ld * Material.Kd;
      vec3 VertexToEye = -normalize(VertexView);
      vec3 LightReflect = normalize(reflect(-LightDirection, NNormalView));
      float fs = dot(VertexToEye, LightReflect);
      if (fs > 0) {
        ColorS = pow(fs, Material.Ns) * Light.Ls * Material.Ks;
      }
    }
    vec3 ColorT = ColorA + ColorD + ColorS;
    if (Light.type == 1) {  // point light
      float d = length(LightDistance);
      float coeff = (Light.Aa * d * d + Light.Ab * d + Light.Ac);
      if (coeff == 0) coeff = 1;
      ColorT = 1 / coeff * ColorT;
    }
    color += vec4(ColorT, 0.5f);
  }
}
