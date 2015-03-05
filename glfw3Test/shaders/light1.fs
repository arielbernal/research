#version 130

// Interpolated values from the vertex shaders
//in vec3 color;
in vec3 vertexPosition_world;
in vec3 N;

// Ouput data
out vec3 Color;

// Values that stay constant for the whole mesh.
uniform vec3 LightPosition_worldspace;

void main() {
  vec3 Ld = vec3(0.8, 0.8, 0.8);
  vec3 Md = vec3(0.6, 0.6, 0.7);
  vec3 La = vec3(0.3, 0.3, 0.3);
  vec3 Ma = vec3(0.05, 0.05, 0.07);

  vec3 L = LightPosition_worldspace - vertexPosition_world; 
  L = normalize(L);
  vec3 fd = clamp(dot(N, L), 0, 1) * Ld * Md;
  vec3 fa = La + Ma;

  Color = fd+fa;
}