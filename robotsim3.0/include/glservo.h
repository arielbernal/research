#ifndef GLSERVO_H
#define GLSERVO_H

#include "glprimitives.h"


void setMaterialBlackPlastic() {
  static const float Amb[4] = { 0, 0, 0, 1};
  static const float Dif[4] = { 0.01, 0.01, 0.01, 1};
  static const float Spec[4] = { 0.5, 0.5, 0.5, 1};
  static const float shine = 0.25f;
  glMaterialfv(GL_FRONT, GL_AMBIENT, Amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
  glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void setMaterialWhitePlastic() {
  static const float Amb[4] = { 0, 0, 0, 1};
  static const float Dif[4] = { 0.55, 0.55, 0.55, 1};
  static const float Spec[4] = { 0.70, 0.70, 0.70, 1};
  static const float shine = 0.25f;
  glMaterialfv(GL_FRONT, GL_AMBIENT, Amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
  glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void setMaterialBronze() {     
  static const float Amb[4] = { 0.24725, 0.1995, 0.0745, 1};
  static const float Dif[4] = { 0.75164, 0.60648, 0.22648, 1};
  static const float Spec[4] = { 0.628281, 0.555802, 0.366065, 1};
  static const float shine = 0.4f;
  glMaterialfv(GL_FRONT, GL_AMBIENT, Amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
  glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void setMaterialGold() {
  static const float Amb[4] = { 0.215, 0.1275, 0.054, 1};
  static const float Dif[4] = { 0.714, 0.4284, 0.18144, 1};
  static const float Spec[4] = { 0.3935, 0.2719, 0.1667, 1};
  static const float shine = 0.2f;
  glMaterialfv(GL_FRONT, GL_AMBIENT, Amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, Dif);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Spec);
  glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}



class GLServoMotor {
public:
  GLServoMotor() {
    setDimensions(2, 4, 3.5);
    Angle = 0;
    DrawRot = true;
    AMax = 0;
    AMin = 0;
    TMax = 0;
    TMin = 0;
    DTau = 0;
    DAlpha = 0;
    TauCoef = 0;
  }

  void setPos(float x, float y, float z, float angle = 0) {
    X = x;
    Y = y;
    Z = z;
    Angle = angle;    
  }

  void setDimensions(float width, float length, float height) {
    Width = width;
    Length = length;
    Height = height;    
  }

  void setAngle(float angle) { Angle = angle; }

  void incAngle(float da) { 
    Angle += da; 
    float am = AMax > AMin ? AMax : AMin;
    if (Angle >= am) Angle = am;
  }

  void decAngle(float da) { 
    Angle -= da; 
    float am = AMax > AMin ? AMin : AMax;
    if (Angle <= am) Angle = am;
  }


  float getAngle() { return Angle; }

  void rotate() {
    glRotatef(Angle, 0, 0, 1);
  }

  void setDrawRot(bool draw) {
    DrawRot = draw;
  }

  void draw() {
    glPushMatrix();
    // body
    if (!NoColor) {
      setMaterialBlackPlastic();
      glColor3f(0.1, 0.1, 0.1);
    }
    else glColor3f(0, 0, 0);

    drawCube(Width, Length, Height);
    // small bisel
    glTranslatef(0, 0.15, Height/2 +0.15);
    drawCube(Width - 0.3, Length - 0.3, 0.3);
    // gear
    glTranslatef(0, -0.15 + 1, 0.15);
    if (!NoColor) {
      setMaterialBronze();
      glColor3f(0.4, 0.4, 0.2);
    }
    else glColor3f(0, 0, 0);

    drawCilinder(0.61, 0.3);
    // Wheel
    glColor3f(0, 0, 0);
    if (DrawRot) {
      if (!NoColor)
        glColor3f(0, 0, 1);
      drawArrow(0, 0, -7, 0, 0, 2, 0.05);
      if (!NoColor)      
        glColor3f(0, 1, 0);
      drawArrow(0, -2, 0, 0, 2, 0, 0.05);
      if (!NoColor)      
        glColor3f(1, 0, 0);
      drawArrow(-2, 0, 0, 2, 0, 0, 0.05);
    }
    glRotatef(Angle, 0, 0, 1);

    glTranslatef(0, 0.0 , 0.35);
    if (!NoColor) {
      setMaterialWhitePlastic();
      glColor3f(1, 1, 1);
    }
    else
      glColor3f(0, 0, 0);

    drawCilinder(0.25, 1.25);
    glTranslatef(1, 0, 0.27);
    glColor3f(0.0, 0.0, 1);
    drawCilinder(0.02, 0.1);

    glPopMatrix();
  }

  void setBoundaries(float aMax, float aMin, float tMax, float tMin) {
    AMax = aMax;
    AMin = aMin;
    TMax = tMax;
    TMin = tMin;
    DAlpha = AMax - AMin;
    DTau = TMax - TMin;
    if (DTau == 0) 
      TauCoef = 0;
    else
      TauCoef = DAlpha / DTau;
  }

  void setAngleFromTau(float Tau) {
    Angle = TauCoef * (Tau - TMin) + AMin;
//    std::cout << Tau << " -> " << Angle << std::endl;
  }

  float getTau() {
    if(TauCoef != 0)
      return (Angle - AMin) / TauCoef + TMin;
    else
      return 0;
  }

private:
  float Angle;
  float X, Y, Z;
  float Width, Length, Height;
  bool DrawRot;
  float AMax, AMin, DAlpha;
  float TMax, TMin, DTau, TauCoef;
};


#endif  // GLSERVO_H