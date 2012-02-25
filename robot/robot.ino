#include <Motor298.h>
#include <Driver298.h>
#include <Bluetooth.h>

/**********************/
/* Definiciones Motor */
/**********************/
// PWM 5 y 6, no llegan a 0
#define MT_IZQ_AVANCE   3
#define MT_IZQ_RETRO    4
#define MT_IZQ_CONTROL  5
#define MT_DCHA_AVANCE  6
#define MT_DCHA_RETRO   7
#define MT_DCHA_CONTROL 6

#if !digitalPinHasPWM(MT_IZQ_CONTROL) || !digitalPinHasPWM(MT_DCHA_CONTROL)
  #error "Los pines de control deben ser PWM"
#endif

Driver298 move(MT_IZQ_AVANCE, MT_IZQ_RETRO, MT_IZQ_CONTROL,
               MT_DCHA_AVANCE, MT_DCHA_RETRO, MT_DCHA_CONTROL);

/**************************/
/* Definiciones Bluetooth */
/**************************/
#define BT_RESET 10
#define BT_NAME "ROBOTO"
#define BT_PINCODE "1234"

Bluetooth bt(BT_RESET);

/*****************************/
/* Definiciones Sensor Línea */
/*****************************/


void setup(){
  Serial.begin(9600);
  
  #if defined(BT_NAME) || defined(BT_PINCODE)
    bt.turnOn();
    #ifdef BT_NAME
      bt.setName(BT_NAME);
    #endif
    #ifdef BT_PINCODE
      bt.setPinCode(BT_PINCODE);
    #endif
    bt.turnOff();
  #endif
}

void loop(){}
