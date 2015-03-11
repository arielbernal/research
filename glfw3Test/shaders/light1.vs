#version 130

// Input vertex data, different for all executions of this shader.
in vec3 Vertex;
in vec3 Normal;

// Output data ; will be interpolated for each fragment.
out vec3 N;
out vec3 vertexPosition_world;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

void main() {
  // Need to use the transpose(inverse(M)) in case of scaling
  // otherwise transp(transp(M)) = M!!
  N = (V * M * vec4(Normal, 0.0)).xyz;
  vertexPosition_world = (V * M * vec4(Vertex, 1)).xyz;
  gl_Position = MVP * vec4(Vertex, 1);
}