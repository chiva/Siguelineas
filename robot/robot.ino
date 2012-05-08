#include <Motor298.h>
#include <Driver298.h>
#include <LineSensor.h>
#include <PathFollow.h>
#include <WheelEnc.h>

/**********************/
/* Definiciones Motor */
/**********************/
// PWM 5 y 6, no llegan a 0
#define MT_IZQ_AVANCE   A0
#define MT_IZQ_RETRO    A1
#define MT_IZQ_CONTROL  10
#define MT_DCHA_AVANCE  A2
#define MT_DCHA_RETRO   A3
#define MT_DCHA_CONTROL 9

#if !digitalPinHasPWM(MT_IZQ_CONTROL) || !digitalPinHasPWM(MT_DCHA_CONTROL)
  #error "Los pines de control del motor deben ser PWM"
#endif

Driver298 motor(MT_IZQ_AVANCE, MT_IZQ_RETRO, MT_IZQ_CONTROL,
                MT_DCHA_AVANCE, MT_DCHA_RETRO, MT_DCHA_CONTROL);

/*****************************/
/* Definiciones Sensor Línea */
/*****************************/
byte pinLine[LN_SENSORS] = {7,8,A4,4,5,6};
LineSensor line(&motor, pinLine);

/******************************/
/* Definiciones Encoder Rueda */
/******************************/
#define ENC_IZQ  3
#define ENC_DCHA 2
WheelEnc encoder(ENC_IZQ, ENC_DCHA);

/******************************/
/* Definiciones Sigue Caminos */
/******************************/
PathFollow path(&motor, &encoder);

void setup(){
  Serial.begin(9600);
  Serial.println(F("Selecciona un modo:"));
  Serial.println(F("1. Sigue lineas"));
  Serial.println(F("2. Sigue caminos"));
  Serial.print(F("Modo: "));
}

void loop(){
  while(!Serial.available());
    switch(Serial.read()){
      case '1':
        line.follow();
        break;
      case '2':
        path.follow();
        break;
    }
}
