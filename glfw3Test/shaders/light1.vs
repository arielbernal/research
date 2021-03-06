#version 130

// Input vertex data, different for all executions of this shader.
in vec3 Vertex;
in vec3 Normal;

// Output data ; will be interpolated for each fragment.
out vec3 VertexView;
out vec3 NormalView;

// Values that stay constant for the whole mesh.
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main() {
  // Need to use the transpose(inverse(M)) in case of scaling
  // otherwise transp(transp(M)) = M!!
  mat4 MV = V * M;
  NormalView = (MV * vec4(Normal, 0.0)).xyz;
  VertexView = (MV * vec4(Vertex, 1)).xyz;
  gl_Position = P * MV * vec4(Vertex, 1);
}