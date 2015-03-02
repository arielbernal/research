#ifndef INITWORLD_H
#define INITWORLD_H

#include <gl/rgGLCamera.h>
#include <gl/rgGLLight.h>
#include <gl/rgGLBasicCuboid.h>
#include <gl/rgGLShaderProgram.h>
#include <gl/rgGLWorldScene.h>


namespace rg {

void InitWorld(rg::GLWorldScene &World) {
  GLCamera* Cam = new GLCamera("FirstCamera");
  World.add(Cam);

  GLLight* L1 = new GLLight("FirstLight");
  World.add(L1);

  GLShaderProgram* Shader = new GLShaderProgram("Basic3d", "./shaders/basic3d.vs", "./shaders/basic3d.fs");

  GLBasicCuboid* cube = new GLBasicCuboid("Cube", 2, 2, 2, glm::vec4(1, 1, 1, 1));
  cube->attachShader(Shader);
  World.add(cube);

  World.update();
}

} // namespace rg


#endif // INITWORLD_H