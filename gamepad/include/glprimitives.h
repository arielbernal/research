#ifndef GLPRIMITIVES_H
#define GLPRIMITIVES_H

#include <glheaders.h>
#include <svector.h>

//#include "common.h"

#define RADPERDEG 0.0174533

int NoColor = false;

void drawArrow(float x1, float y1, float z1, float x2, float y2, float z2,
               float D) {
  float x = x2 - x1;
  float y = y2 - y1;
  float z = z2 - z1;
  float L = sqrt(x * x + y * y + z * z);

  GLUquadricObj *quadObj;

  glPushMatrix();

  glTranslated(x1, y1, z1);

  if ((x != 0.) || (y != 0.)) {
    glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
    glRotated(atan2(sqrt(x * x + y * y), z) / RADPERDEG, 0., 1., 0.);
  } else if (z < 0) {
    glRotated(180, 1., 0., 0.);
  }

  glTranslatef(0, 0, L - 4 * D);

  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluCylinder(quadObj, 3 * D, 0.0, 6 * D, 32, 4);
  gluDeleteQuadric(quadObj);

  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluDisk(quadObj, 0.0, 2 * D, 32, 4);
  gluDeleteQuadric(quadObj);

  glTranslatef(0, 0, -L + 4 * D);

  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluCylinder(quadObj, D, D, L - 4 * D, 32, 4);
  gluDeleteQuadric(quadObj);

  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluDisk(quadObj, 0.0, D, 32, 4);
  gluDeleteQuadric(quadObj);

  glPopMatrix();
}

void drawCilinder(float h, float r) {
  glPushMatrix();
  GLUquadricObj *quadObj;
  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluCylinder(quadObj, r, r, h, 32, 4);
  gluDeleteQuadric(quadObj);
  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluDisk(quadObj, 0.0, r, 32, 4);
  gluDeleteQuadric(quadObj);
  glTranslatef(0, 0, h);
  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  gluDisk(quadObj, 0.0, r, 32, 4);
  gluDeleteQuadric(quadObj);
  glPopMatrix();
}

void draw_axes_arrow(float width, float height, float depth, float r) {
  glColor3f(1, 0, 0);
  drawArrow(-width / 2, 0, 0, width / 2, 0, 0, r);
  glColor3f(0, 1, 0);
  drawArrow(0, -height / 2, 0, 0, height / 2, 0, r);
  glColor3f(0, 0, 1);
  drawArrow(0, 0, -depth / 2, 0, 0, depth / 2, r);
}

void draw_axes(float width, float height, float depth) {
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
  glColor3f(0, 1, 0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, -depth / 2);
  glVertex3f(0, 0, depth / 2);
  glEnd();
}

void drawCube(float dx, float dy, float dz, bool center = false) {
  glPushMatrix();
  if (center)
    glTranslatef(-dx / 2, -dy / 2, -dz / 2);

  glBegin(GL_QUADS);
  // back face
  glNormal3f(0, 0, -1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, dy, 0);
  glVertex3f(dx, dy, 0);
  glVertex3f(dx, 0, 0);

  // flront face
  glNormal3f(0, 0, 1);
  glVertex3f(0, 0, dz);
  glVertex3f(0, dy, dz);
  glVertex3f(dx, dy, dz);
  glVertex3f(dx, 0, dz);

  // bottom face  (z = 1.0f)
  glNormal3f(0, -1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, dz);
  glVertex3f(dx, 0, dz);
  glVertex3f(dx, 0, 0);

  // top face (z = -1.0f)
  glNormal3f(0, 1, 0);
  glVertex3f(0, dy, 0);
  glVertex3f(0, dy, dz);
  glVertex3f(dx, dy, dz);
  glVertex3f(dx, dy, 0);

  // Left face (x = -1.0f)
  glNormal3f(-1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, dz);
  glVertex3f(0, dy, dz);
  glVertex3f(0, dy, 0);

  // // Right face (x = 1.0f)
  glNormal3f(1, 0, 0);
  glVertex3f(dx, 0, 0);
  glVertex3f(dx, 0, dz);
  glVertex3f(dx, dy, dz);
  glVertex3f(dx, dy, 0);

  glEnd(); // End of drawing color-cube
  glPopMatrix();
}

void drawWireframeCube(float dx, float dy, float dz) {
  glBegin(GL_LINE_LOOP); 
  glVertex3f(0, 0, 0);
  glVertex3f(dx, 0, 0);
  glVertex3f(dx, dy, 0);
  glVertex3f(0, dy, 0);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex3f(0, 0, dz);
  glVertex3f(dx, 0, dz);
  glVertex3f(dx, dy, dz);
  glVertex3f(0, dy, dz);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, dz);
  glVertex3f(dx, 0, 0);
  glVertex3f(dx, 0, dz);
  glVertex3f(dx, dy, 0);
  glVertex3f(dx, dy, dz);
  glVertex3f(0, dy, 0);
  glVertex3f(0, dy, dz);
  glEnd();


}

void drawCircle(float cx, float cy, float r, int num_segments) {
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta); // precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = r; // we start at angle = 0
  float y = 0;

  glBegin(GL_LINE_LOOP);
  for (int ii = 0; ii < num_segments; ii++) {
    glVertex2f(x + cx, y + cy); // output vertex

    // apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
}

void drawDisk(float cx, float cy, float r, int num_segments) {
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta); // precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = r; // we start at angle = 0
  float y = 0;

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(cx, cy);
  for (int ii = 0; ii < num_segments; ii++) {
    glVertex2f(x + cx, y + cy); // output vertex

    // apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glVertex2f(cx + r, cy);
  glEnd();
}

void printText(float x, float y, const std::string &text) {
  glRasterPos2f(x, y);
  for (auto I = text.begin(), E = text.end(); I != E; ++I) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (*I));
  }
}

std::string format(const char *fmt, ...) {
  std::vector<char> buf(1024);

  for (;;) {
    va_list va;
    va_start(va, fmt);
    int bsize = static_cast<int>(buf.size());
    int len = vsnprintf(&buf[0], bsize, fmt, va);
    va_end(va);

    if (len < 0 || len >= bsize) {
      buf.resize(std::max(bsize << 1, len + 1));
      continue;
    }
    return std::string(&buf[0], len);
  }
}


void printFloat(float x, float y, const std::string &text, float v,
                int dig = 10, int dec = 2) {
  char s[100];
  char sformat[100];
  sprintf(sformat, "%s%%%d.%df", text.c_str(), dig, dec);
  sprintf(s, sformat, v);
  printText(x, y, s);
}

void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(0, 0, 40, 0, 0, 0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, Height, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setColor(const svector::float4 &c) { glColor4f(c.x, c.y, c.z, c.w); }

#endif // GLPRIMITIVES_H