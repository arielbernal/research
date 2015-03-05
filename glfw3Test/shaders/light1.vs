#version 130

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition_modelspace;
in vec3 vertexNormal_modelspace;
in vec4 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 N;
out vec3 vertexPosition_world;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

void main() {

  // Output position of the vertex, in clip space : MVP * position
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);


  N = vertexNormal_modelspace;
  vertexPosition_world = (M * vec4(vertexPosition_modelspace, 1)).xyz;
}