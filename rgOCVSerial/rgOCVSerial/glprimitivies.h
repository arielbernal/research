#ifndef GLPRIMITIVIES
#define GLPRIMITIVIES

#include <GL/glew.h>
#include <cmath>

namespace glp {

void circle(float radius, float segments = 0);

void draw_axes(float width, float height);

uint32_t newTextureId();

void setTexture(size_t texId,
                size_t width,
                size_t height,
                GLenum DataFormat,
                uint8_t* buffer);

void renderTexture(size_t texId, float x, float y, float width, float height);

}  // namespace glp

#endif  // GLPRIMITIVIES