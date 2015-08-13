#include <iostream>
#include <glheaders.h>
#include <cmath>
#include <glprimitives.h>
#include <vector>

struct Point2d {
  Point2d(float x = 0, float y = 0) : x(x), y(y) {}
  void set(float xv, float yv) {
    x = xv;
    y = yv;
  }
  float x;
  float y;
};

float distance(const Point2d &p1, const Point2d &p2) {
  float dx = p2.x - p1.x;
  float dy = p2.y - p1.y;
  return sqrt(dx * dx + dy * dy);
}

class Robot {
 public:
  Robot() : x(0), y(0), alpha(0), t(0) {
    r = 10;
    rw = 3;
    dt = 0.1f;
    Motors[0] = 0;
    Motors[1] = 0;
    k0 = 55.0f / 60.0f;
    k1 = 55.0f / 60.0f;
  }

  void setPos(float posx, float posy, float angle) {
    x = posx;
    y = posy;
    alpha = angle;
  }

  void setMotors(float Left, float Right) {
    Motors[0] = Left;
    Motors[1] = Right;
  }

  void setMotorLeft(float Left) { Motors[0] = Left; }

  void setMotorRight(float Right) { Motors[1] = Right; }

  float getX() { return x; }
  float getY() { return y; }
  float getAlpha() { return alpha; }

  void update() {
    t += dt;
    float v0 = Motors[0] / 100.0f * k0 * 2 * M_PI * rw;  // speed motor left
    float v1 = Motors[1] / 100.0f * k1 * 2 * M_PI * rw;  // speed motor right
    float ar = alpha / 180.0f * M_PI;
    float lx0 = x - r * cos(ar);
    float ly0 = y - r * sin(ar);
    float rx0 = x + r * cos(ar);
    float ry0 = y + r * sin(ar);

    float da0 = -v0 / (2 * M_PI * r) * dt;
    ar += da0;
    float lx1 = rx0 - 2 * r * cos(ar);
    float ly1 = ry0 - 2 * r * sin(ar);

    float da1 = v1 / (2 * M_PI * r) * dt;
    ar += da1;
    float rx1 = lx1 + 2 * r * cos(ar);
    float ry1 = ly1 + 2 * r * sin(ar);

    x = (rx1 + lx1) / 2;
    y = (ry1 + ly1) / 2;
    alpha = atan2(ry1 - ly1, rx1 - lx1) * 180 / M_PI;
    std::cout << "========================================" << std::endl;
    std::cout << " T = " << t << " x = " << x << " y = " << y
              << " alpha = " << alpha << std::endl;
  }

  void stimate(float m0, float m1, float dt, float &xe, float &ye,
               float &alphae) {
    float v0 = m0 / 100.0f * k0 * 2 * M_PI * rw;  // speed motor left
    float v1 = m1 / 100.0f * k1 * 2 * M_PI * rw;  // speed motor right
    float ar = alpha / 180.0f * M_PI;
    float lx0 = x - r * cos(ar);
    float ly0 = y - r * sin(ar);
    float rx0 = x + r * cos(ar);
    float ry0 = y + r * sin(ar);

    float da0 = -v0 / (2 * M_PI * r) * dt;
    ar += da0;
    float lx1 = rx0 - 2 * r * cos(ar);
    float ly1 = ry0 - 2 * r * sin(ar);

    float da1 = v1 / (2 * M_PI * r) * dt;
    ar += da1;
    float rx1 = lx1 + 2 * r * cos(ar);
    float ry1 = ly1 + 2 * r * sin(ar);

    xe = (rx1 + lx1) / 2;
    ye = (ry1 + ly1) / 2;
    alphae = atan2(ry1 - ly1, rx1 - lx1) * 180 / M_PI;
  }

  void render() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(alpha, 0, 0, 1);

    float arrowLength = r + 5;
    float dw2 = 0.4;

    glColor3f(1, 1, 1);
    drawCircle(0, 0, r, 30);

    glColor3f(1, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-r - dw2, rw);
    glVertex2f(-r - dw2, -rw);
    glVertex2f(-r + dw2, -rw);
    glVertex2f(-r + dw2, rw);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(r - dw2, rw);
    glVertex2f(r - dw2, -rw);
    glVertex2f(r + dw2, -rw);
    glVertex2f(r + dw2, rw);
    glEnd();

    glColor3f(1, 0, 0);
    drawArrow(0, 0, 0, 0, arrowLength, 0, 0.5);

    glPopMatrix();
  }
  Point2d pos() { return Point2d(x, y); }

 private:
  float x, y, alpha;
  float r;   // wheel to center distance
  float rw;  // wheel radius
  float t;   // time
  float dt;
  float k0;  // max angular speed motor0 (Left)
  float k1;  // max angular speed motor1 (Right)
  float Motors[2];
};

class Path {
 public:
  Path() {
    path.push_back(Point2d(0, 10));
    path.push_back(Point2d(0, 40));
    path.push_back(Point2d(40, 40));
    path.push_back(Point2d(40, 80));
  }

  float distToSegment(const Point2d &p, const Point2d &a, const Point2d &b) {
    float l = distance(a, b);
    if (l == 0) return distance(p, a);
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (l * l);
    if (t < 0) return distance(p, a);
    if (t > 1) return distance(p, b);
    Point2d xp(a.x + t * dx, a.y + t * dy);
    return distance(p, xp);
  }

  Point2d pointToSegment(const Point2d &p, const Point2d &a, const Point2d &b) {
    float l = distance(a, b);
    if (l == 0) return a;
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / (l * l);
    if (t < 0) return a;
    if (t > 1) return b;
    Point2d xp(a.x + t * dx, a.y + t * dy);
    return xp;
  }

  Point2d minDistPoint(const Point2d &p) {
    float dmin = 10E20;
    Point2d pmin;
    for (size_t i = 0; i < path.size() - 1; ++i) {
      Point2d xp = pointToSegment(p, path[i], path[i + 1]);
      float d = distance(p, xp);
      if (d < dmin) {
        dmin = d;
        pmin = xp;
      }
    }
    return pmin;
  }

  void render() {
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    for (size_t i = 0; i < path.size() - 1; ++i) {
      Point2d p0 = path[i];
      Point2d p1 = path[i + 1];
      glVertex2f(p0.x, p0.y);
      glVertex2f(p1.x, p1.y);
    }
    glEnd();
    glColor3f(0, 0, 1);
    for (size_t i = 0; i < path.size(); ++i) {
      drawDisk(path[i].x, path[i].y, 2, 10);
    }
  }
  std::vector<Point2d> path;
};

namespace {
int m_window_width = 1000;
int m_window_height = 1000;
std::string m_window_title = "RobotSim";
Robot robot;
Path path;
}

void set2DMode(size_t Width, size_t Height) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, Width, 0, Height);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void set3DMode(size_t Width, size_t Height) {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, float(Width) / Height, 0.01f, 1000);
  gluLookAt(80, 0, 80, 0, 0, 0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  int width = viewport[2];
  int height = viewport[3];
  set2DMode(300, 300);
  glTranslatef(150, 150, 0);
  path.render();
  robot.render();
  Point2d p = path.minDistPoint(robot.pos());
  glColor3f(0, 1, 0);
  drawDisk(p.x, p.y, 1.5, 20);
  glutSwapBuffers();
}

void init_display() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  display();
}

void mouse_wheel(int wheel, int direction, int x, int y) {}

void mouse_button(int button, int state, int x, int y) {}

void mouse_active_motion(int x, int y) {}

void mouse_passive_motion(int x, int y) {}

void special_keys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_RIGHT:
      break;
    case GLUT_KEY_LEFT:
      break;
    default:
      break;
  }
}

void normal_keys(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      robot.setMotorLeft(50);
      break;
    case 's':
      robot.setMotorRight(50);
      break;
    case 32:
      robot.update();
      glutPostRedisplay();
      break;
    case 27:
      glutLeaveMainLoop();
      break;
    default:
      break;
  }
}

void setWorld() {}

void init_glut_window(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(2800, 100);
  glutInitWindowSize(m_window_width, m_window_height);
  glutCreateWindow(m_window_title.c_str());

  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse_button);
  glutMotionFunc(mouse_active_motion);
  glutPassiveMotionFunc(mouse_passive_motion);
  glutMouseWheelFunc(mouse_wheel);
  glutReshapeFunc(reshape);
  // glewInit();
  setWorld();
  glutMainLoop();
}

int main(int argc, char **argv) {
  init_glut_window(argc, argv);
  return 0;
}
