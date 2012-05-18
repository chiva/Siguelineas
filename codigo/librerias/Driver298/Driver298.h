#ifndef Driver298_h
#define Driver298_h

#include "Arduino.h"
#include <Motor298.h>

#define D298_FW         true
#define D298_BW         false
#define D298_LEFT       true
#define D298_RIGHT      false
#define D298_REC_SPEED  170     //PWM para hacer 3V de media con 5V
#define D298_MAX_SPEED  255     //PWM para sacar 5V al motor en continua
#define D298_FULL_SPEED D298_REC_SPEED

class Driver298
{
  public:
    Driver298() {};
    Driver298(byte, byte, byte, byte, byte, byte);
    Motor298 *left, *right;
    void stop();
    void brake();
    void forward(byte);
    void reverse(byte);
    void setSpeed(boolean, byte, boolean, byte);
    void setSpeed(byte, byte);
    void turn(boolean, byte, byte);
};

Driver298::Driver298(byte pinLF, byte pinLB, byte pinLS, byte pinRF, byte pinRB, byte pinRS){
    left = new Motor298(pinLF, pinLB, pinLS);
    right = new Motor298(pinRF, pinRB, pinRS);
}

inline void Driver298::forward(byte speed){
    setSpeed(D298_FW, speed, D298_FW, speed);
}

inline void Driver298::reverse(byte speed){
    setSpeed(D298_BW, speed, D298_BW, speed);
}

void Driver298::setSpeed(boolean spinLeft, byte speedLeft, boolean spinRight, byte speedRight){
    left->setSpeed(spinLeft, speedLeft);
    right->setSpeed(spinRight, speedRight);
}

inline void Driver298::setSpeed(byte speedLeft, byte speedRight){
    setSpeed(D298_FW, speedLeft, D298_FW, speedRight);
}

void Driver298::turn(boolean direction, byte speedL, byte speedR){
    Serial.println(F("Motor: giro"));
    if (direction) {
        setSpeed(D298_BW, speedL, D298_FW, speedR);
    } else {
        setSpeed(D298_FW, speedL, D298_BW, speedR);
    }
}

void Driver298::stop(){
    Serial.println(F("Motor: stop"));
    left->stop();
    right->stop();
}

void Driver298::brake(){
    Serial.println(F("Motor: parado"));
    left->brake();
    right->brake();
}

#endif