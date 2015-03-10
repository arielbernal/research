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

void main() {
  vec3 Ld = vec3(0.5, 0.5, 0.5);
  vec3 La = vec3(0.1, 0.1, 0.1);
  vec3 Ls = vec3(0.2, 0.2, 0.2);

  vec3 ColorA = La + Material.Ka;  // Ambient Color
  vec3 ColorD = vec3(0);           // Diffuse Color
  vec3 ColorS = vec3(0);           // Specular Color

  vec3 L = normalize(LightPosition_worldspace - vertexPosition_world);
  vec3 NN = normalize(N);

  float fd = dot(NN, L);
  if (fd > 0) {
    ColorD = fd * Ld * Material.Kd;
    vec3 VertexToEye = normalize(EyePos - vertexPosition_world);
    vec3 LightReflect = normalize(reflect(L, NN));
    float Ps = 32;
    float fs = dot(VertexToEye, LightReflect);
    if (fs > 0) {
      fs = pow(fs, Ps);
      ColorS = fs * Ls * Material.Ks;
    }
  }
  color = vec4(ColorA + ColorD + ColorS, 0.5);
}
