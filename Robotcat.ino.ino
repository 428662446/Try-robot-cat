// RobotFace.ino
#include "CommandHandler.h"
#include "Display.h"
#include "ServoControl.h"
#include "FaceExpressions.h"
#include "Touch.h"
#include <Arduino.h>
#include <SPI.h>

// 全局变量定义（唯一位置）

bool isBlinking = false;
bool isShowing = false;
bool isEar = true;
bool isInputLocked = false;
bool isInputBuffer =false; 
unsigned long actionStart = 0;
uint32_t nextBlinkTime = 0;
BlinkState blinkState = BlinkState::EYE_OPEN;
Expression currentExpression = Expression::NEUTRAL;
ExpressionParams exprParams;

unsigned long systemStartTime = 0; // 记录系统启动时间
const uint32_t INITIAL_DELAY = 15000; // 初始屏蔽时长15秒（单位：毫秒）


void setup() {
  systemStartTime = millis();
  initDisplay();
  initServos();
  Serial.begin(9600);
  clearScreen();
  pinMode(MOTION_PIN, INPUT); 
  currentExpression = Expression::NEUTRAL;
  exprParams = {3000, 3000, 5, 30, eye_open_alert, eye_closed_alert, mouth_neutral};
  drawDefaultFace();
}

void loop() {
  handleSerialInput();
  handleEars();
  handleBlink();
  handleDisplayTimeout();
  handleTouch();

static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    Serial.println("----- Status -----");
    Serial.print("isBlinking: ");
    Serial.print("blinkState: ");
    Serial.println((blinkState == BlinkState::EYE_OPEN) ? "OPEN" : "CLOSED");
    Serial.print("Touch State: ");
  Serial.println(isTouched ? "ACTIVE" : "INACTIVE");
  Serial.print("Servo Control: ");
  Serial.println(isEar ? "ENABLED" : "DISABLED");
  }

}