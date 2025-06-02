// ServoControl.h
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H
#include <Arduino.h>
#include <Servo.h>

// 舵机引脚定义
extern const int servo1_pin;
extern const int servo2_pin;

// 函数声明
void initServos();
void handleEars();
void resetEars();

#endif