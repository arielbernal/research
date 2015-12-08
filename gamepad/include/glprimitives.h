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

bool gluInvertMatrix(const double m[16], double invOut[16]) {
  double inv[16], det;
  int i;

  inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
           m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

  inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] -
           m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

  inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
           m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

  inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

  inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] -
           m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

  inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
           m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

  inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
           m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

  inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
            m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

  inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
           m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

  inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
           m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

  inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
            m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

  inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
            m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

  inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
           m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

  inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
           m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

  inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
            m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

  inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
            m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if (det == 0)
    return false;

  det = 1.0 / det;

  for (i = 0; i < 16; i++)
    invOut[i] = inv[i] * det;

  return true;
}

void gluTransform(const double m[16], const double v[4], double out[4]) {
  out[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3];
  out[1] = m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3];
  out[2] = m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3];
  out[3] = m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3];
}

void MultiplyMatrices4by4(float *result, float *matrix1, float *matrix2);
void MultiplyMatrixByVector4by4(float *resultvector, const float *matrix,
                                const float *pvector);
int glhInvertMatrixf2(float *m, float *out);

int glhProjectf(float objx, float objy, float objz, float *modelview,
                float *projection, int *viewport, float *windowCoordinate) {
  // Transformation vectors
  float fTempo[8];
  // Modelview transform
  fTempo[0] = modelview[0] * objx + modelview[4] * objy + modelview[8] * objz +
              modelview[12]; // w is always 1
  fTempo[1] = modelview[1] * objx + modelview[5] * objy + modelview[9] * objz +
              modelview[13];
  fTempo[2] = modelview[2] * objx + modelview[6] * objy + modelview[10] * objz +
              modelview[14];
  fTempo[3] = modelview[3] * objx + modelview[7] * objy + modelview[11] * objz +
              modelview[15];
  // Projection transform, the final row of projection matrix is always [0 0 -1
  // 0]
  // so we optimize for that.
  fTempo[4] = projection[0] * fTempo[0] + projection[4] * fTempo[1] +
              projection[8] * fTempo[2] + projection[12] * fTempo[3];
  fTempo[5] = projection[1] * fTempo[0] + projection[5] * fTempo[1] +
              projection[9] * fTempo[2] + projection[13] * fTempo[3];
  fTempo[6] = projection[2] * fTempo[0] + projection[6] * fTempo[1] +
              projection[10] * fTempo[2] + projection[14] * fTempo[3];
  fTempo[7] = -fTempo[2];
  // The result normalizes between -1 and 1
  if (fTempo[7] == 0.0) // The w value
    return 0;
  fTempo[7] = 1.0 / fTempo[7];
  // Perspective division
  fTempo[4] *= fTempo[7];
  fTempo[5] *= fTempo[7];
  fTempo[6] *= fTempo[7];
  // Window coordinates
  // Map x, y to range 0-1
  windowCoordinate[0] = (fTempo[4] * 0.5 + 0.5) * viewport[2] + viewport[0];
  windowCoordinate[1] = (fTempo[5] * 0.5 + 0.5) * viewport[3] + viewport[1];
  // This is only correct when glDepthRange(0.0, 1.0)
  windowCoordinate[2] = (1.0 + fTempo[6]) * 0.5; // Between 0 and 1
  return 1;
}

int glhUnProjectf(float winx, float winy, float winz, float *modelview,
                  float *projection, int *viewport, float *objectCoordinate) {
  // Transformation matrices
  float m[16], A[16];
  float in[4], out[4];
  // Calculation for inverting a matrix, compute projection x modelview
  // and store in A[16]
  MultiplyMatrices4by4(A, projection, modelview);
  // Now compute the inverse of matrix A
  if (glhInvertMatrixf2(A, m) == 0)
    return 0;
  // Transformation of normalized coordinates between -1 and 1
  in[0] = (winx - (float)viewport[0]) / (float)viewport[2] * 2.0 - 1.0;
  in[1] = (winy - (float)viewport[1]) / (float)viewport[3] * 2.0 - 1.0;
  in[2] = 2.0 * winz - 1.0;
  in[3] = 1.0;
  // Objects coordinates
  MultiplyMatrixByVector4by4(out, m, in);
  if (out[3] == 0.0)
    return 0;
  out[3] = 1.0 / out[3];
  objectCoordinate[0] = out[0] * out[3];
  objectCoordinate[1] = out[1] * out[3];
  objectCoordinate[2] = out[2] * out[3];
  return 1;
}

void MultiplyMatrices4by4(float *result, float *matrix1, float *matrix2) {
  result[0] = matrix1[0] * matrix2[0] + matrix1[4] * matrix2[1] +
              matrix1[8] * matrix2[2] + matrix1[12] * matrix2[3];
  result[4] = matrix1[0] * matrix2[4] + matrix1[4] * matrix2[5] +
              matrix1[8] * matrix2[6] + matrix1[12] * matrix2[7];
  result[8] = matrix1[0] * matrix2[8] + matrix1[4] * matrix2[9] +
              matrix1[8] * matrix2[10] + matrix1[12] * matrix2[11];
  result[12] = matrix1[0] * matrix2[12] + matrix1[4] * matrix2[13] +
               matrix1[8] * matrix2[14] + matrix1[12] * matrix2[15];
  result[1] = matrix1[1] * matrix2[0] + matrix1[5] * matrix2[1] +
              matrix1[9] * matrix2[2] + matrix1[13] * matrix2[3];
  result[5] = matrix1[1] * matrix2[4] + matrix1[5] * matrix2[5] +
              matrix1[9] * matrix2[6] + matrix1[13] * matrix2[7];
  result[9] = matrix1[1] * matrix2[8] + matrix1[5] * matrix2[9] +
              matrix1[9] * matrix2[10] + matrix1[13] * matrix2[11];
  result[13] = matrix1[1] * matrix2[12] + matrix1[5] * matrix2[13] +
               matrix1[9] * matrix2[14] + matrix1[13] * matrix2[15];
  result[2] = matrix1[2] * matrix2[0] + matrix1[6] * matrix2[1] +
              matrix1[10] * matrix2[2] + matrix1[14] * matrix2[3];
  result[6] = matrix1[2] * matrix2[4] + matrix1[6] * matrix2[5] +
              matrix1[10] * matrix2[6] + matrix1[14] * matrix2[7];
  result[10] = matrix1[2] * matrix2[8] + matrix1[6] * matrix2[9] +
               matrix1[10] * matrix2[10] + matrix1[14] * matrix2[11];
  result[14] = matrix1[2] * matrix2[12] + matrix1[6] * matrix2[13] +
               matrix1[10] * matrix2[14] + matrix1[14] * matrix2[15];
  result[3] = matrix1[3] * matrix2[0] + matrix1[7] * matrix2[1] +
              matrix1[11] * matrix2[2] + matrix1[15] * matrix2[3];
  result[7] = matrix1[3] * matrix2[4] + matrix1[7] * matrix2[5] +
              matrix1[11] * matrix2[6] + matrix1[15] * matrix2[7];
  result[11] = matrix1[3] * matrix2[8] + matrix1[7] * matrix2[9] +
               matrix1[11] * matrix2[10] + matrix1[15] * matrix2[11];
  result[15] = matrix1[3] * matrix2[12] + matrix1[7] * matrix2[13] +
               matrix1[11] * matrix2[14] + matrix1[15] * matrix2[15];
}

void MultiplyMatrixByVector4by4(float *resultvector, const float *matrix,
                                const float *pvector) {
  resultvector[0] = matrix[0] * pvector[0] + matrix[4] * pvector[1] +
                    matrix[8] * pvector[2] + matrix[12] * pvector[3];
  resultvector[1] = matrix[1] * pvector[0] + matrix[5] * pvector[1] +
                    matrix[9] * pvector[2] + matrix[13] * pvector[3];
  resultvector[2] = matrix[2] * pvector[0] + matrix[6] * pvector[1] +
                    matrix[10] * pvector[2] + matrix[14] * pvector[3];
  resultvector[3] = matrix[3] * pvector[0] + matrix[7] * pvector[1] +
                    matrix[11] * pvector[2] + matrix[15] * pvector[3];
}

#define SWAP_ROWS_DOUBLE(a, b) { \
double *_tmp = a; \
(a) = (b);        \
(b) = _tmp;       \
}
#define SWAP_ROWS_FLOAT(a, b) { \
float *_tmp = a;  \
(a) = (b);        \
(b) = _tmp;       \
}
#define MAT(m, r, c) (m)[(c)*4 + (r)]

// This code comes directly from GLU except that it is for float
int glhInvertMatrixf2(float *m, float *out) {
  float wtmp[4][8];
  float m0, m1, m2, m3, s;
  float *r0, *r1, *r2, *r3;
  r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
  r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1), r0[2] = MAT(m, 0, 2),
  r0[3] = MAT(m, 0, 3), r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
  r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1), r1[2] = MAT(m, 1, 2),
  r1[3] = MAT(m, 1, 3), r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
  r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1), r2[2] = MAT(m, 2, 2),
  r2[3] = MAT(m, 2, 3), r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
  r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1), r3[2] = MAT(m, 3, 2),
  r3[3] = MAT(m, 3, 3), r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
  /* choose pivot - or die */
  if (fabsf(r3[0]) > fabsf(r2[0]))
    SWAP_ROWS_FLOAT(r3, r2);
  if (fabsf(r2[0]) > fabsf(r1[0]))
    SWAP_ROWS_FLOAT(r2, r1);
  if (fabsf(r1[0]) > fabsf(r0[0]))
    SWAP_ROWS_FLOAT(r1, r0);
  if (0.0 == r0[0])
    return 0;
  /* eliminate first variable     */
  m1 = r1[0] / r0[0];
  m2 = r2[0] / r0[0];
  m3 = r3[0] / r0[0];
  s = r0[1];
  r1[1] -= m1 * s;
  r2[1] -= m2 * s;
  r3[1] -= m3 * s;
  s = r0[2];
  r1[2] -= m1 * s;
  r2[2] -= m2 * s;
  r3[2] -= m3 * s;
  s = r0[3];
  r1[3] -= m1 * s;
  r2[3] -= m2 * s;
  r3[3] -= m3 * s;
  s = r0[4];
  if (s != 0.0) {
    r1[4] -= m1 * s;
    r2[4] -= m2 * s;
    r3[4] -= m3 * s;
  }
  s = r0[5];
  if (s != 0.0) {
    r1[5] -= m1 * s;
    r2[5] -= m2 * s;
    r3[5] -= m3 * s;
  }
  s = r0[6];
  if (s != 0.0) {
    r1[6] -= m1 * s;
    r2[6] -= m2 * s;
    r3[6] -= m3 * s;
  }
  s = r0[7];
  if (s != 0.0) {
    r1[7] -= m1 * s;
    r2[7] -= m2 * s;
    r3[7] -= m3 * s;
  }
  /* choose pivot - or die */
  if (fabsf(r3[1]) > fabsf(r2[1]))
    SWAP_ROWS_FLOAT(r3, r2);
  if (fabsf(r2[1]) > fabsf(r1[1]))
    SWAP_ROWS_FLOAT(r2, r1);
  if (0.0 == r1[1])
    return 0;
  /* eliminate second variable */
  m2 = r2[1] / r1[1];
  m3 = r3[1] / r1[1];
  r2[2] -= m2 * r1[2];
  r3[2] -= m3 * r1[2];
  r2[3] -= m2 * r1[3];
  r3[3] -= m3 * r1[3];
  s = r1[4];
  if (0.0 != s) {
    r2[4] -= m2 * s;
    r3[4] -= m3 * s;
  }
  s = r1[5];
  if (0.0 != s) {
    r2[5] -= m2 * s;
    r3[5] -= m3 * s;
  }
  s = r1[6];
  if (0.0 != s) {
    r2[6] -= m2 * s;
    r3[6] -= m3 * s;
  }
  s = r1[7];
  if (0.0 != s) {
    r2[7] -= m2 * s;
    r3[7] -= m3 * s;
  }
  /* choose pivot - or die */
  if (fabsf(r3[2]) > fabsf(r2[2]))
    SWAP_ROWS_FLOAT(r3, r2);
  if (0.0 == r2[2])
    return 0;
  /* eliminate third variable */
  m3 = r3[2] / r2[2];
  r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4], r3[5] -= m3 * r2[5],
      r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];
  /* last check */
  if (0.0 == r3[3])
    return 0;
  s = 1.0 / r3[3]; /* now back substitute row 3 */
  r3[4] *= s;
  r3[5] *= s;
  r3[6] *= s;
  r3[7] *= s;
  m2 = r2[3]; /* now back substitute row 2 */
  s = 1.0 / r2[2];
  r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
  r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
  m1 = r1[3];
  r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1, r1[6] -= r3[6] * m1,
      r1[7] -= r3[7] * m1;
  m0 = r0[3];
  r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0, r0[6] -= r3[6] * m0,
      r0[7] -= r3[7] * m0;
  m1 = r1[2]; /* now back substitute row 1 */
  s = 1.0 / r1[1];
  r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
  r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
  m0 = r0[2];
  r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0, r0[6] -= r2[6] * m0,
      r0[7] -= r2[7] * m0;
  m0 = r0[1]; /* now back substitute row 0 */
  s = 1.0 / r0[0];
  r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
  r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
  MAT(out, 0, 0) = r0[4];
  MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
  MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
  MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
  MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
  MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
  MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
  MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
  MAT(out, 3, 3) = r3[7];
  return 1;
}

#endif // GLPRIMITIVES_H