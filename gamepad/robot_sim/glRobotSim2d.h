#ifndef GLROBOTSIM2D_H
#define GLROBOTSIM2D_H

#include <svector.h>
#include "../include/glprimitives.h"
#include "../include/gl2dmodel.h"
#include "Robot2d.h"

class GLRobotSim2D : public GL2DModel {
public:
  GLRobotSim2D(Robot2D &robot, float ViewWidth = 100, int WinWidth = 1200,
               int WinHeight = 1000)
      : GL2DModel(ViewWidth, WinWidth, WinHeight), robot(robot) {}

  void render() {
    glScalef(1, -1, 1);

    float r = robot.L / 2;
    float rw = robot.rw;
    float arrowLength = r + 5;
    float dw2 = 0.4;

    glColor3f(1, 0, 0);
    drawCircle(robot.xTarget, robot.yTarget, 2, 30);

    glColor3f(0, 1, 0);
    drawCircle(robot.ICCx, robot.ICCy, robot.ICCR, 100);
    glBegin(GL_LINES);
    glVertex2f(robot.x, robot.y);
    glVertex2f(robot.ICCx, robot.ICCy);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(robot.x, robot.y);
    glVertex2f(robot.xTarget, robot.yTarget);
    glEnd();

    glPushMatrix();
    glTranslatef(robot.x, robot.y, 0);
    glRotatef(robot.theta / M_PI * 180 - 90, 0, 0, 1);

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

    glTranslatef(0, r, 0);
    glColor3f(0, 1, 0);
    drawDisk(0, 0, r / 10, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(robot.xEst, robot.yEst, 0);
    glRotatef(robot.thetaEst / M_PI * 180 - 90, 0, 0, 1);

    glColor3f(0.5, 0.5, 0.5);
    drawCircle(0, 0, r, 30);

    glColor3f(0.5, 0.5, 0);
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

    glTranslatef(0, r, 0);
    glColor3f(0, 0.5, 0);
    drawDisk(0, 0, r / 10, 30);
    glPopMatrix();
  }

  void mouse_button(int button, int status, int x, int y) {
    GL2DModel::mouse_button(button, status, x, y);
    if (button == GLUT_LEFT_BUTTON) {
      if (status == GLUT_DOWN) {
        glPushMatrix();
        set2DMode(ViewWidth, ViewHeight);
        glTranslatef(ViewX0, ViewY0, 0);
        glScalef(1, -1, 1);
        float wx, wy;
        convertScreenToWorldCoords(x, y, wx, wy);
        std::cout << x << " " << y << "  ->  " << wx << " " << wy << std::endl;
        glPopMatrix();
        robot.setTarget(wx, wy);
      }
    }
  }

private:
  Robot2D &robot;
};

#endif // GLROBOTSIM2D_H