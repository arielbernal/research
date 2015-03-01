#version 130

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition_modelspace;
in vec3 vertexNormal_modelspace;
in vec4 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec4 color;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;

void main() {

  //outColor = vertexColor;
  color = vertexColor;

  // Output position of the vertex, in clip space : MVP * position
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

  // Position of the vertex, in worldspace : M * position
  Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

  // Vector that goes from the vertex to the camera, in camera space.
  // In camera space, the camera is at the origin (0,0,0).
  vec3 vertexPosition_cameraspace =
      (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
  EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;

  // Vector that goes from the vertex to the light, in camera space. M is
  // ommited because it's identity.
  vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
  LightDirection_cameraspace =
      LightPosition_cameraspace + EyeDirection_cameraspace;

  // Normal of the the vertex, in camera space
  // Only correct if ModelMatrix does not scale the model ! Use its inverse
  // transpose if not.
  Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz;

}