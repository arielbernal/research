#ifndef INITWORLD_H
#define INITWORLD_H

#include <gl/rgCamera.h>
#include <gl/rgWorldScene.h>

namespace rg {

void InitWorld(rg::WorldScene &World) {

  Camera* Cam = new Camera();

  World.addCamera(Cam);


}

} // namespace rg


#endif // INITWORLD_H