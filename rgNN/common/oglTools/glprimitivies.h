#ifndef GLPRIMITIVIES
#define GLPRIMITIVIES

//#include <GL/glew.h>
#include <QOpenGLWidget>
#include <cmath>
#include <stdint.h>
#include <glm/glm.hpp>

namespace glp {

void circle(float radius, float segments = 0);
void disk(float radius, float segments = 0);

void draw_axes(float width, float height);

void cross(float x, float y, float size);
void cross(float x, float y, float size, const glm::vec3 &color);

uint32_t newTextureId();

void setTexture(size_t texId, size_t width, size_t height, GLenum DataFormat,
                uint8_t *buffer);

void renderTexture(size_t texId, float x, float y, float width, float height);

} // namespace glp

#endif // GLPRIMITIVIES
