// Touch.cpp
#include "Touch.h"
#include <Arduino.h>
#include "CommandHandler.h"
#include "Display.h"
#include "ServoControl.h"
#include "FaceExpressions.h"

const int MOTION_PIN =4;
bool isTouched = false;
unsigned long touchStart = 0;
const uint16_t TOUCH_DURATION = 3000;
extern int maxMovements;
extern bool isEar;
extern Expression currentExpression;
extern ExpressionParams exprParams;
extern bool isBlinking;

void handleTouch() {
  if(isInputBuffer)return;
  static unsigned long lastDebounceTime = 0;
  static bool lastSensorValue = LOW;
  const uint16_t NORMAL_DEBOUNCE = 200; // 正常防抖时间（200ms）
  uint16_t debounceDelay = NORMAL_DEBOUNCE;

  // 检查是否在初始屏蔽期内
  if (millis() - systemStartTime < INITIAL_DELAY) {
    return; // 前15秒直接退出，不处理任何信号
  }
  
  int currentSensorValue = digitalRead(MOTION_PIN);

  // 信号变化时重置防抖计时器
  if (currentSensorValue != lastSensorValue) {
    lastDebounceTime = millis();
    lastSensorValue = currentSensorValue;
  }
  // 防抖时间过后更新状态
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (isTouched != currentSensorValue) {
      isTouched = currentSensorValue;
      
      if (isTouched) {
        touchStart = millis();
        currentExpression = Expression::SMILE;
        exprParams = {5000, 500, 6, 30, eye_open_smile, eye_open, mouth_smile};
        showMouth(exprParams.mouth);
        isEar = true;
        maxMovements = 6;
        Serial.println("Touch detected!");
      } else {
        if (millis() - touchStart > TOUCH_DURATION) {
          currentExpression = Expression::NEUTRAL;
          isEar = false;
          resetEars();
          clearScreen();
          drawDefaultFace();
        }
      }
    }
  }
}