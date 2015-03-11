#version 130

// Interpolated values from the vertex shaders
in vec3 vertexPosition_world;
in vec3 N;

// Ouput data
out vec4 color;

struct GLMaterial {
  vec3 Kd;
  vec3 Ka;
  vec3 Ks;
};

// Values that stay constant for the whole mesh.
uniform vec3 LightPosition_worldspace;
uniform GLMaterial Material;
uniform vec3 EyePos;
uniform mat4 V;

void main() {
  vec3 Ld = vec3(0.5, 0.5, 0.5);
  vec3 La = vec3(0.1, 0.1, 0.1);
  vec3 Ls = 4*vec3(0.2, 0.2, 0.2);

  vec3 ColorA = La + Material.Ka;  // Ambient Color
  vec3 ColorD = vec3(0);           // Diffuse Color
  vec3 ColorS = vec3(0);           // Specular Color

  vec3 L = normalize((V * vec4(LightPosition_worldspace,1)).xyz - vertexPosition_world);
  vec3 NN = normalize(N);
  vec3 EyePos1 = vec3(0);
  float fd = dot(NN, L);
  if (fd > 0) {
    ColorD = fd * Ld * Material.Kd;
    vec3 VertexToEye = normalize(EyePos1 - vertexPosition_world);
    vec3 LightReflect = normalize(reflect(-L, NN));
    float Ps = 25;
    float fs = dot(VertexToEye, LightReflect);
    if (fs > 0) {
      fs = pow(fs, Ps);
      ColorS = fs * Ls * Material.Ks;
    }
  }
  color = vec4(ColorA + ColorD + ColorS, 0.5);
}
