// Display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <SPI.h>

// 引脚定义
extern int CS_PIN;
extern int DC_PIN;
extern int RESET_PIN;

extern int EYE_RIGHT_X;
extern int EYE_LEFT_X;
extern int EYE_PAGE;

// 函数声明
void initDisplay();
void clearScreen();
void drawDefaultFace();
void drawEyes(const uint8_t* data);
void showMouth(const uint8_t* data);
void setPosition(uint8_t x, uint8_t page);
void startDisplayTimer(unsigned long duration);

void handleBlink();
#endif