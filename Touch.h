//Touch.h
#ifndef TOUCH_H
#define TOUCH_H
#include <Arduino.h>

extern unsigned long systemStartTime;
extern const int MOTION_PIN;
extern bool isTouched;
extern bool isInputBuffer; 
extern unsigned long touchStart;
extern const uint32_t INITIAL_DELAY;
void handleTouch();

#endif