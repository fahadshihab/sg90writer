/* 
 *  shittyCode for the shittyWriter
 *  author: fahadshihab
 */

#define NSTEPS 40

#include <Servo.h>

Servo servo1, servo2, servo3;

class Vec2 {
  public:
  float x;
  float y;

  Vec2() {
    x = 0;
    y = 0;
  }
  
  Vec2(float x0, float y0) {
    x = x0;
    y = y0;
  }
  
  Vec2 operator + (Vec2 const &a){
    Vec2 ans;
    ans.x = x + a.x;
    ans.y = y + a.y;
    return ans;
  }

  Vec2 operator - (Vec2 const &a){
    Vec2 ans;
    ans.x = x - a.x;
    ans.y = y - a.y;
    return ans;
  }

  float dot(Vec2 a){
    return x*a.x + y*a.y;
  }

  Vec2 mult(float a){
    Vec2 ans;
    ans.x = x * a;
    ans.y = y * a;
    return ans;
  }
};

int pos = 90;    
float flag = 0.05;
float theta1 = 90;
float theta2 = 90;
int thetap = 135;
float x = 0.0;
float y = 14.0;

void setup() {
  servo1.attach(10);
  servo2.attach(11);
  servo3.attach(9);
}

void loop() {
  drawChar('S', Vec2(8.3, 1.75), 2);
  drawChar('H', Vec2(10.8, 1.75), 2);
  drawChar('I', Vec2(13.3, 1.75), 2);
  drawChar('T', Vec2(15.8, 1.75), 2);
}

void penUp() {
  servo3.write(100);
  delay(150);
}

void penDown() {
  servo3.write(140);
  delay(150);
}


void setPosition2(float x, float y){
  float r2 = x*x + y*y;
  float alpha3 = acos((128-r2)/128);
  float beta1 = acos(x/sqrt(r2));
  float radtheta1 = (PI-alpha3)/2 + beta1;
  float radtheta2 = 1.5*PI - alpha3;
  theta1 = radtheta1 * 180.0/PI;
  theta2 = radtheta2 * 180.0/PI;
  servo2.write(theta2);
  servo1.write(theta1);
  delay(100);
}


float rmin = 12.0;
float rmax = 15.5;
void setPosition(float x, float y){
  float r = rmin + y;
  float theta = radians(135 - (90.0*x/21.6));
  float xnew = r * cos(theta);
  float ynew = r * sin(theta);
  setPosition2(xnew, ynew);
}

void line(Vec2 P0, Vec2 P1, int steps){
  Vec2 dP = P1 - P0;
  Vec2 P;
  float dt = 1.0/steps;
  float t = 0;
  for(int i=0; i<=steps; ++i){
    P = P0 + dP.mult(i * dt);
    setPosition(P.x, P.y);
  }
}

void cubicBezier(Vec2 P0, Vec2 P1, Vec2 P2, Vec2 P3, int steps=NSTEPS){
  Vec2 B;
  float dt = 1.0/steps;
  float t = 0;
  float it = 1 - t;
  for(int i=0; i<=steps; ++i){
    t = i * dt;
    it = 1 - t;
    B = P0.mult(it * it * it);
    B = B + P1.mult(3 * it * it * t);
    B = B + P2.mult(3 * it * t * t);
    B = B + P3.mult(t * t * t);
    setPosition(B.x, B.y);
  }
}

void drawChar(char letter, Vec2 P0, float scale){
  switch(letter){
    case 'C':
      setPosition(P0.x + 0.5*scale, P0.y + 0.5*scale);
      penDown();
      cubicBezier(Vec2(0.5, 0.5).mult(scale) + P0,
                  Vec2(-0.75, 0.5).mult(scale) + P0,
                  Vec2(-0.75, -0.5).mult(scale) + P0,
                  Vec2(0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'E':
      setPosition(P0.x + 0.5*scale, P0.y + 0.5*scale);
      penDown();
      line(Vec2(0.5, 0.5).mult(scale) + P0, Vec2(-0.5, 0.5).mult(scale) + P0, NSTEPS);
      line(Vec2(-0.5, 0.5).mult(scale) + P0, Vec2(-0.5, -0.5).mult(scale) + P0, NSTEPS);
      line(Vec2(-0.5, -0.5).mult(scale) + P0, Vec2(0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      setPosition(P0.x - 0.5*scale, P0.y);
      penDown();
      line(Vec2(-0.5, 0.0).mult(scale) + P0, Vec2(0.5, 0.0).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'H':
      setPosition(P0.x - 0.5*scale, P0.y + 0.5*scale);
      penDown();
      line(Vec2(-0.5, 0.5).mult(scale) + P0, Vec2(-0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      setPosition(P0.x + 0.5*scale, P0.y + 0.5*scale);
      penDown();
      line(Vec2(0.5, 0.5).mult(scale) + P0, Vec2(0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      setPosition(P0.x - 0.5*scale, P0.y);
      penDown();
      line(Vec2(-0.5, 0.0).mult(scale) + P0, Vec2(0.5, 0.0).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'I':
      setPosition(P0.x, P0.y + 0.5*scale);
      penDown();
      line(Vec2(0.0, 0.5).mult(scale) + P0, Vec2(0.0, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'L':
      setPosition(P0.x - 0.5*scale, P0.y + 0.5*scale);
      penDown();
      line(Vec2(-0.5, 0.5).mult(scale) + P0, Vec2(-0.5, -0.5).mult(scale) + P0, NSTEPS);
      line(Vec2(-0.5, -0.5).mult(scale) + P0, Vec2(0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'S':
      setPosition(P0.x + 0.5*scale, P0.y + 0.5*scale);
      penDown();
      cubicBezier(Vec2(0.5, 0.5).mult(scale) + P0,
                  Vec2(-2, 0.5).mult(scale) + P0,
                  Vec2(2, -0.5).mult(scale) + P0,
                  Vec2(-0.5, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'T':
      setPosition(P0.x + 0.5*scale, P0.y + 0.5*scale);
      penDown();
      line(Vec2(0.5, 0.5).mult(scale) + P0, Vec2(-0.5, 0.5).mult(scale) + P0, NSTEPS);
      penUp();
      setPosition(P0.x, P0.y + 0.5*scale);
      penDown();
      line(Vec2(0.0, 0.5).mult(scale) + P0, Vec2(0.0, -0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
    case 'U':
      setPosition(P0.x - 0.5*scale, P0.y + 0.5*scale);
      penDown();
      cubicBezier(Vec2(-0.5, 0.5).mult(scale) + P0,
                  Vec2(-0.5, -0.75).mult(scale) + P0,
                  Vec2(0.5, -0.75).mult(scale) + P0,
                  Vec2(0.5, 0.5).mult(scale) + P0, NSTEPS);
      penUp();
      break;
  }
}
