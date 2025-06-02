// FaceExpressions.h
#ifndef FACE_EXPRESSIONS_H
#define FACE_EXPRESSIONS_H
#include <Arduino.h>
extern const uint8_t eye_open[16];     // 声明而非定义
extern const uint8_t eye_closed[16];
extern const uint8_t mouth_neutral[16];
extern const uint8_t mouth_smile[16];

extern const uint8_t eye_open_smile[16];
extern const uint8_t eye_closed_smile[16];
extern const uint8_t eye_open_alert[16];
extern const uint8_t eye_closed_alert[16];
extern const uint8_t eye_closed_shock[16];
extern const uint8_t eye_open_shock[16];     
extern const uint8_t mouth_alert[16];  // 警觉嘴巴
extern const uint8_t mouth_shock[16];  // 震惊嘴巴

#endif