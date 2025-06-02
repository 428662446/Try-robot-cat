// ServoControl.cpp
#include "ServoControl.h"
#include "CommandHandler.h"
#include "Touch.h"
#include <Servo.h>
#include <Arduino.h> 

const int servo1_pin = 3;
const int servo2_pin = 7;

Servo servo1;
Servo servo2;

Expression previousExpression = Expression::NEUTRAL;

// 运动控制变量
unsigned long prevMillis = 0;
const long interval = 20;//运动间隔
int angle1 = 90, angle2 = 90;
int dir1 = 1, dir2 = -1;
int maxMovements = 3;
int movementCount = 0;

extern Expression currentExpression;
extern ExpressionParams exprParams;

void initServos() {
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo1.write(90);
  servo2.write(90);
}

void updateServo(Servo &servo, int &angle, int &dir, int center, int range) {
  angle += dir;
  angle = constrain(angle, center - range, center + range);
  if (angle == center + range || angle == center - range) {
    dir *= -1;
  }
  servo.write(angle);
}

//耳朵运动控制
// ServoControl.cpp
void handleEars() {
  if (currentExpression != previousExpression) {
    movementCount = 0;
    previousExpression = currentExpression;
    isEar = true;
    Serial.println("[Servo] Expression changed");
  }

  if (!isEar) return;

  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;

    // 跳过睡眠和中性状态
    if (currentExpression == Expression::SLEEP) {
      servo1.write(150);
      servo2.write(30);
      return;
    }
    if (currentExpression == Expression::NEUTRAL) return;

    // 更新舵机角度
    updateServo(servo1, angle1, dir1, 90, exprParams.earAngleRange);
    updateServo(servo2, angle2, dir2, 90, exprParams.earAngleRange);

    // 完成一次往返计数
    if (angle1 == 90) movementCount++;

    // 达到指定次数后停止
    if (movementCount >= exprParams.earMoveCount) {
      isEar = false;
      movementCount = 0;
      Serial.println("[Servo] Movement completed");
    }
  }
}

// ServoControl.cpp
void resetEars() {
  angle1 = 90;
  angle2 = 90;
  dir1 = 1;
  dir2 = -1;
  movementCount = 0;
  isEar = false;
  servo1.write(90);
  servo2.write(90);
}