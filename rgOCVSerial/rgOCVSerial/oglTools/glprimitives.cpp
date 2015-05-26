#include "glprimitivies.h"
#define M_PI 3.14159265358

namespace glp {

void circle(float radius, float segments) {
  if (segments == 0)
    segments = radius * 60;
  float da = 2 * M_PI / segments;
  glBegin(GL_LINES);
  for (int i = 0; i < segments; ++i) {
    float x0 = radius * cos(da * i);
    float y0 = radius * sin(da * i);
    float x1 = radius * cos(da * (i + 1));
    float y1 = radius * sin(da * (i + 1));
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
  }
  glEnd();
}


void disk(float radius, float segments) {
  if (segments == 0)
    segments = radius * 60;
  float da = 2 * M_PI / segments;
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0, 0);
  for (int i = 0; i < segments + 1; ++i) {
    float x0 = radius * cos(da * i);
    float y0 = radius * sin(da * i);
    float x1 = radius * cos(da * (i + 1));
    float y1 = radius * sin(da * (i + 1));
    glVertex2f(x0, y0);
  }
  glEnd();
}


void draw_axes(float width, float height) {
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  glVertex3f(-width / 2, 0, 0);
  glVertex3f(width / 2, 0, 0);
  glEnd();
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(0, -height / 2, 0);
  glVertex3f(0, height / 2, 0);
  glEnd();
}

void cross(float x, float y, float size) {
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  glVertex3f(x - size / 2, y, 0);
  glVertex3f(x + size / 2, y, 0);
  glEnd();
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(x, y - size / 2, 0);
  glVertex3f(x, y + size / 2, 0);
  glEnd();
}
void cross(float x, float y, float size, const glm::vec3 &color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_LINES);
  glVertex3f(x - size / 2, y, 0);
  glVertex3f(x + size / 2, y, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(x, y - size / 2, 0);
  glVertex3f(x, y + size / 2, 0);
  glEnd();
}

uint32_t newTextureId() {
  GLuint texId;
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glDisable(GL_TEXTURE_2D);
  return texId;
}

void setTexture(size_t texId, size_t width, size_t height, GLenum DataFormat,
                uint8_t *buffer) {
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, DataFormat,
               GL_UNSIGNED_BYTE, buffer);
}

void renderTexture(size_t texId, float x, float y, float width, float height) {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex2f(x, y);
  glTexCoord2f(1, 1);
  glVertex2f(x + width, y);
  glTexCoord2f(1, 0);
  glVertex2f(x + width, y + height);
  glTexCoord2f(0, 0);
  glVertex2f(x, y + height);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

} // namespace glp
