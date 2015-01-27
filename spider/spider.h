#ifndef SPIDER_H
#define SPIDER_H

#define _USE_MATH_DEFINES
#include <math.h>

struct Servo {
  float angleNew;
  float angle;
  float dangle;
  float dir;
  float vmod;
  float v;
  bool moving;

  Servo() {
    angle = 0;
    angleNew = 0;
    vmod = 60 / 0.17f;
    dangle = v * 0.0001f;
    moving = false;
  }
  void move(float val) {
    angleNew = val;
    v = angle < angleNew ? vmod : -vmod;
    moving = true;
  }
  void moveToAngle(float val) {
    moving = false;
    angle = val;
  }
  void update(float dt) {
    if (moving && (fabs(angle - angleNew) > dangle)) {
      angle += v * dt;
    } else if (moving) {
      angle = angleNew;
      moving = false;
    }
  }
};

struct Adafruit_PWMServoDriver {
  Servo servos[16];
  void begin() {}
  void setPWMFreq(size_t freq) {}
  void setPWM(size_t idServo, size_t offTime, float onTime) {
    servos[idServo].moveToAngle(onTime);
  }
  void update(float dt) {
    for (int i = 0; i < 16; ++i) servos[i].update(dt);
  }
  float getAngle(size_t idServo) { return servos[idServo].angle; }
};


struct vec4 {
  float x, y, z, w;
  void set(float vx, float vy, float vz, float vw = 0) {
    x = vx;
    y = vy;
    z = vz;
    w = vw;
  }

  void set(const vec4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
  }

  void add(float dx, float dy, float dz, float dw = 0) {
    x += dx;
    y += dy;
    z += dz;
    w += dw;
  }

  void add(const vec4& v, float dx, float dy, float dz, float dw = 0) {
    x = v.x + dx;
    y = v.y + dy;
    z = v.z + dz;
    w = v.w + dw;
  }  
};


class Spider {
 public:
  vec4 coxa[4];      // coxas initial position and angle
  vec4 legs[4];       // legs position
  vec4 angles[4];    // servo angles
  vec4 legsTemp[4];   // temporary legs position
  vec4 anglesTemp[4]; // temporary servo angles
  
  float lcoxa, lfemur, ltibia, width, height;

  float x0, y0, z0;
  Adafruit_PWMServoDriver *pwm;

  Spider() {
    width = 11;
    height = 14;
    lcoxa = 3.5;
    lfemur = 11;
    ltibia = 18;
    x0 = lcoxa + lfemur / 2 - 2;
    y0 = lcoxa + lfemur / 2 - 2;
    z0 = -8;
    pwm = new Adafruit_PWMServoDriver();
    pwm->begin();
    pwm->setPWMFreq(60);
    initPos();
  }

  ~Spider() { delete pwm; }

  bool computeAngles(size_t i, vec4 pos, vec4 angles) {
    bool ret = true;
    float dx = pos.x - coxa[i].x;
    float dy = pos.y - coxa[i].y;
    float coxaa = -coxa[i].w / 180.0f * M_PI;
    float cosc = cos(coxaa);
    float sinc = sin(coxaa);
    float dxp = cosc * dx - sinc * dy;
    float dyp = sinc * dx + cosc * dy;
    float u = sqrt(dxp * dxp + dyp * dyp);
    float f2 = lfemur * lfemur;
    float t2 = ltibia * ltibia;
    float du = u - lcoxa;
    float h2 = pos.z * pos.z + du * du;
    float h = sqrt(h2);
    float alpha = 0;
    float beta = 0;
    float gamma = 0;
    if ((h == 0) || (du == 0) ||
        (fabs((f2 + h2 - t2) / (2 * lfemur * h)) > 1) ||
        (fabs((f2 + t2 - h2) / (2 * lfemur * ltibia)) > 1)) {
      ret = false;
    } else {
      float a1 = acos((f2 + h2 - t2) / (2 * lfemur * h));
      float b1 = acos((f2 + t2 - h2) / (2 * lfemur * ltibia));
      float a2 = atan(pos.z / du);
      float alpha = (a1 + a2) / M_PI * 180;
      float beta =  b1 / M_PI * 180 - 180;
      float gamma = atan2(dyp, dxp) / M_PI * 180.0f;
      if (beta < 16 - 180 || beta > 20 || alpha < -90 ||
          alpha > 150 || gamma < -90 || gamma > 90)
        ret = false;
    }
    angles.x = alpha;
    angles.y = beta;
    angles.z = gamma;
    return ret;
  }


  void initPos() {
    coxa[0].set(width / 2, height / 2, 0, 45);
    coxa[1].set(-width / 2, height / 2, 0, 135);
    coxa[2].set(width / 2, -height / 2, 0, -45);
    coxa[3].set(-width / 2, -height / 2, 0, -135);
    legs[0].add(coxa[0], x0, y0, z0);
    legs[1].add(coxa[1], -x0, y0, z0);
    legs[2].add(coxa[2], x0, -y0, z0);
    legs[3].add(coxa[3], -x0, -y0, z0);
    for (size_t i = 0; i < 4; ++i)
      computeAngles(i, legs[i], angles[i]);
    moveServos();
  }

  void rotate(float roll, float pitch, float yaw) {
    float g = roll / 180 * M_PI;
    float b = pitch / 180 * M_PI;
    float a = yaw / 180 * M_PI;
    float a11 = cos(b) * cos(a);
    float a12 = cos(b) * sin(a);
    float a13 = sin(b);
    float a21 = -sin(g) * sin(b) * cos(a) - cos(g) * sin(a);
    float a22 = -sin(g) * sin(b) * sin(a) + cos(g) * cos(a);
    float a23 = sin(g) * cos(b);
    float a31 = -cos(g) * sin(b) * cos(a) + sin(g) * sin(a);
    float a32 = -cos(g) * sin(b) * sin(a) - sin(g) * cos(a);
    float a33 = cos(g) * cos(b);
    for (int i = 0; i < 4; ++i) {
      float xx = legs[i].x, yy = legs[i].y, zz = legs[i].z;
      legsTemp[i].x = a11 * xx + a12 * yy + a13 * zz;
      legsTemp[i].y = a21 * xx + a22 * yy + a23 * zz;
      legsTemp[i].z = a31 * xx + a32 * yy + a33 * zz;
      if (computeAngles(i, legsTemp[i], anglesTemp[i])) {
        angles[i].set(anglesTemp[i]);
        legs[i].set(legsTemp[i]);
      }
    }
    moveServos();
  }

  void translate(float dx, float dy, float dz) {
    for (int i = 0; i < 4; ++i) {
      legsTemp[i].add(legs[i], -dx, -dy, -dz);
      if (computeAngles(i, legsTemp[i], anglesTemp[i])) {
        angles[i].set(anglesTemp[i]);
        legs[i].set(legsTemp[i]);
      }
    }
    moveServos();
  }

  void moveLeg(int i, float dx, float dy, float dz) {
    legsTemp[i].add(legs[i], -dx, -dy, -dz);
    legsTemp[i].add(legs[i], -dx, -dy, -dz);
    if (computeAngles(i, legsTemp[i], anglesTemp[i])) {
      angles[i].set(anglesTemp[i]);
      legs[i].set(legsTemp[i]);
    }
    moveServos();
  }

  void moveLegTo(int i, float vx, float vy, float vz) {
    legsTemp[i].set(vx, vy, vz);
    if (computeAngles(i, legsTemp[i], anglesTemp[i])) {
      angles[i].set(anglesTemp[i]);
      legs[i].set(legsTemp[i]);
    }
    moveServos();
  }

  void printAngles(int i) {
    std::cout << "Alpha = " << angles[i].x << " Beta = " << angles[i].y
              << " Gamma = " << angles[i].z << std::endl;
  }


  bool checkCoxa(float gamma) {
    return (gamma >= -90 && gamma <= 90);
  }
  bool checkFemur(float alpha) {
    return (alpha >= -90 && alpha <= 150);
  }
  bool checkTibia(float beta) {
    return (beta >= 16 - 180 && beta <= 20);
  }

  void moveFemur(int i, float angle) { 
    if (checkFemur(angle)) {
      angles[i].x = angle;
      pwm->setPWM(3 * i + 1, 0, angle); 
    }
  }
  void moveTibia(int i, float angle) { 
    if (checkTibia(angle)) {
      angles[i].y = angle;
      pwm->setPWM(3 * i + 2, 0, angle); 
    }
  }
  void moveCoxa(int i, float angle) {
    if (checkCoxa(angle)) {
      angles[i].z = angle;
      pwm->setPWM(3 * i, 0, angle); 
    }
  }
  void moveServos() {
    for (size_t i = 0; i <4; ++i) {
      moveFemur(i, angles[i].x);
      moveTibia(i, angles[i].y);
      moveCoxa(i, angles[i].z);
    }
  }

};

#endif  // SPIDER_H