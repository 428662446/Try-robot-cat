// Display.cpp
#include "Display.h"
#include "CommandHandler.h"
#include "FaceExpressions.h"
#include "Touch.h"
#include <Arduino.h>
#include <SPI.h> 

int CS_PIN = 10;
int DC_PIN = 9;
int RESET_PIN = 8;

void sendCommand(uint8_t cmd) {
  digitalWrite(DC_PIN, LOW);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(cmd);
  digitalWrite(CS_PIN, HIGH);
}

void sendData(uint8_t data) {
  digitalWrite(DC_PIN, HIGH);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(data);
  digitalWrite(CS_PIN, HIGH);
}

void clearScreen() {
  for(uint8_t page=0xB0; page<=0xB7; page++) { // 8页
    sendCommand(page);
    sendCommand(0x10); // 列地址高位
    sendCommand(0x00); // 列地址低位
    for(uint16_t col=0; col<128; col++) sendData(0x00);
  }
}

void initDisplay() {
  pinMode(CS_PIN, OUTPUT);
  pinMode(DC_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  sendCommand(0xE2);
  sendCommand(0x2F);
  sendCommand(0xA0);
  sendCommand(0xC8);
  sendCommand(0xA2);
  sendCommand(0x24);
  sendCommand(0x81);
  sendCommand(0x20);
  sendCommand(0xAF);

  delay(100);
  clearScreen();
  delay(100);
}


int EYE_RIGHT_X =92;
int EYE_LEFT_X =28;
int EYE_PAGE =4;

void drawEyes(const uint8_t* data) {

 setPosition(28, 4);
  for(uint8_t i=0; i<16; i++) sendData(data[i]);
  setPosition(84, 4);
  for(uint8_t i=0; i<16; i++) sendData(data[i]);
   sendCommand(0xAF);
}

void showMouth(const uint8_t* data) {
  setPosition(58, 3); // 嘴巴位置
  for(uint8_t i=0; i<16; i++) sendData(data[i]);
  startDisplayTimer(3000);
}


void drawDefaultFace() {
  // 绘制默认眼睛
  setPosition(28, 4);
  for(uint8_t i=0; i<16; i++) sendData(eye_open[i]);
  setPosition(84, 4);
  for(uint8_t i=0; i<16; i++) sendData(eye_open[i]);
  // 绘制默认嘴巴
  setPosition(58, 3);
  for(uint8_t i=0; i<16; i++) sendData(mouth_neutral[i]);
}


// 辅助函数
void setPosition(uint8_t x, uint8_t page) {
  sendCommand(0xB0 | (page & 0x07)); // 设置页地址
  sendCommand(0x10 | ((x >> 4) & 0x0F)); // 列地址高位
  sendCommand(x & 0x0F); // 列地址低位
}

void startDisplayTimer(unsigned long duration) {
  actionStart = millis();
  isShowing = true;
}

//眨眼控制
void handleBlink() {
  switch (currentExpression) {
    case Expression::SLEEP:
      drawEyes(exprParams.eyesClosed); // 使用当前表情的闭眼图案
      break;
    default:
      if (millis() >= nextBlinkTime) {
        if (blinkState == BlinkState::EYE_OPEN) {
          drawEyes(exprParams.eyesClosed);
          blinkState = BlinkState::EYE_CLOSED;
          nextBlinkTime = millis() + exprParams.closeDuration;
        } else {
          drawEyes(exprParams.eyesOpen);
          blinkState = BlinkState::EYE_OPEN;
          nextBlinkTime = millis() + exprParams.openDuration;
        }
      }
      break;
  }
}