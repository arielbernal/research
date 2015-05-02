#include <glprimitivies.h>

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


}  // namespace glp
