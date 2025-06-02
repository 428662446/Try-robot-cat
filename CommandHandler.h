//CommandHandler.h
#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>

enum class BlinkState {
   EYE_OPEN, 
   EYE_CLOSED 
   };
//小猫表情枚举
enum class Expression { 
  NEUTRAL, 
  SMILE,    // 微笑
  ALERT,    // 警觉
  SHOCK,    // 震惊 
  SLEEP     // 睡觉
};
//小猫表情参数
struct ExpressionParams {
  int openDuration;   // 新增：睁眼持续时间
  int closeDuration;  // 新增：闭眼持续时间
  int earMoveCount;//耳朵运动周期
  int earAngleRange;//耳朵摆动幅度
  const uint8_t* eyesOpen;  // 新增：睁眼图案
  const uint8_t* eyesClosed; // 新增：闭眼图案
  const uint8_t* mouth;//嘴巴图案指针
};


// 全局变量声明（extern表示变量在其他文件定义）
// CommandHandler.h
extern bool isBlinking;
extern bool isShowing;
extern bool isEar;    
extern unsigned long actionStart;
extern uint32_t nextBlinkTime;

extern BlinkState blinkState;
extern Expression currentExpression;
extern ExpressionParams exprParams;

extern bool isInputLocked;
extern bool isInputBuffer; 
// 函数声明
void handleSerialInput();
void handleDisplayTimeout();
void processCommand(String cmd);
#endif