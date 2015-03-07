#version 130

// Interpolated values from the vertex shaders
//in vec3 color;
in vec3 vertexPosition_world;
in vec3 N;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec3 LightPosition_worldspace;
uniform vec3 Color;


void main() {
  vec3 Ld = vec3(0.8, 0.8, 0.8);
  vec3 Md = vec3(0.6, 0.6, 0.7);
  Md = Color;
  vec3 La = vec3(0.1, 0.1, 0.1);
  vec3 Ma = vec3(0.2, 0.1, 0.1);

  vec3 L = LightPosition_worldspace - vertexPosition_world; 
  L = normalize(L);
  vec3 NN = normalize(N);
  vec3 fd = max(dot(NN, L), 0) * Ld * Md;
  vec3 fa = La + Ma;
  color = vec4(fd+fa, 0.5);
}