#ifndef Motor298_h
#define Motor298_h

#include "Arduino.h"

class Motor298
{
  private:
    byte _pinForward, _pinReverse, _pinSpeed;
  public:
    Motor298(byte, byte, byte);
    void stop(void);
    void forward(void);
    void reverse(void);
    void speed(byte);
};

Motor298::Motor298(pinForward, pinReverse, pinSpeed){
    _pinForward = pinForward;
    _pinReverse = pinReverse;
    _pinSpeed = pinSpeed;
    pinMode(_pinForward, OUTPUT);
    pinMode(_pinReverse, OUTPUT);
    pinMode(_pinSpeed, OUTPUT);
}

Motor298::stop(){
    digitalWrite(_pinForward, LOW);
    digitalWrite(_pinReverse, LOW);
}

Motor298::forward(){
    digitalWrite(_pinForward, HIGH);
    digitalWrite(_pinReverse, LOW);
}

Motor298::reverse(){
    digitalWrite(_pinReverse, HIGH);
    digitalWrite(_pinForward, LOW);
}

Motor298::speed(speed){
    analogWrite(_pinSpeed, map(speed, 0, 100, 0, 1024));
}
#endif