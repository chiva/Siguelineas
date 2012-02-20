#ifndef Motor298_h
#define Motor298_h

#include "Arduino.h"

class Motor298
{
  private:
    byte pinForward, pinReverse, pinSpeed;
  public:
    Motor298(byte, byte, byte);
    void forward();
    void reverse();
    void setSpeed(boolean, byte);
    void stop();
    void brake();
};

Motor298::Motor298(byte pinForward, byte pinReverse, byte pinSpeed){
    this->pinForward = pinForward;
    this->pinReverse = pinReverse;
    this->pinSpeed = pinSpeed;
    pinMode(pinForward, OUTPUT);
    pinMode(pinReverse, OUTPUT);
    pinMode(pinSpeed, OUTPUT);
    stop();
}

void Motor298::stop(){
    digitalWrite(pinForward, LOW);
    digitalWrite(pinReverse, LOW);
    digitalWrite(pinSpeed, LOW);
}

void Motor298::brake(){
    digitalWrite(pinForward, LOW);
    digitalWrite(pinReverse, LOW);
    digitalWrite(pinSpeed, HIGH);
}

void Motor298::forward(){
    digitalWrite(pinForward, HIGH);
    digitalWrite(pinReverse, LOW);
}

void Motor298::reverse(){
    digitalWrite(pinReverse, HIGH);
    digitalWrite(pinForward, LOW);
}

void Motor298::setSpeed(boolean direction, byte speed){
    if (direction){
        forward();
    } else {
        reverse();
    }
    analogWrite(pinSpeed, speed);
}
#endif