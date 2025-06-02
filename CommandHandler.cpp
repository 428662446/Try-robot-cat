// CommandHandler.cpp
#include "CommandHandler.h"
#include "Display.h"
#include "FaceExpressions.h"
#include "ServoControl.h"
#include <Arduino.h>

String inputBuffer = "";
// 实现串口指令处理
void handleSerialInput() {

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      processCommand(inputBuffer); // 处理完整命令
      inputBuffer = "";           // 清空缓冲区
      Serial.flush();             // 强制清空硬件缓冲区
    } else if (c != '\r') {       // 忽略回车符
      inputBuffer += c;
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();
  if (cmd.length() == 0) return;
  Serial.println("Received: " + cmd);

if (cmd == "SMILE") {
  isInputBuffer = true; 
  isEar = true;
  currentExpression = Expression::SMILE;
  exprParams = {5000, 500, 2, 30, eye_open_smile, eye_closed_smile, mouth_smile};
   showMouth(exprParams.mouth);

} 
else if (cmd == "ALERT") {
  isInputBuffer = true; 
  isEar = true;
  isBlinking = true;
  currentExpression = Expression::ALERT;
  exprParams = {3000, 3000, 6, 50, eye_open_alert, eye_closed_alert, mouth_alert};
} 
else if (cmd == "SHOCK") {
  isInputBuffer = true; 
  isEar = true;
  isBlinking = true;
  currentExpression = Expression::SHOCK;
  exprParams = {3000, 1000, 8, 20, eye_open_shock, eye_closed_shock, mouth_shock};
} 
else if (cmd == "SLEEP") {
  isInputBuffer = true; 
  isEar = true;
  isBlinking = true;
  currentExpression = Expression::SLEEP;
  exprParams = {0, 0, 0, 0, eye_closed, eye_closed, mouth_neutral};
} 
else if (cmd == "RESET") {
  isInputBuffer = false; 
  isEar = false;
  isBlinking = false;
  currentExpression = Expression::NEUTRAL;
  clearScreen();
  resetEars();
} 
else {
  Serial.println("Error: Unknown command '" + cmd + "'");
}
while (Serial.available()) Serial.read();
}

 //实现显示超时控制
void handleDisplayTimeout() {
  if(isShowing && (millis() - actionStart >= 10000)) {
    clearScreen();
    isShowing = false;
    drawDefaultFace(); 
  }
}