#ifndef WheelEnc_h
#define WheelEnc_h

#include "Arduino.h"

class WheelEnc
{
  private:
    boolean lastLeft, lastRight;
    byte stepLeft, stepRight;
    byte pinLeft, pinRight;
    byte goalPulses;
    void detectLeft();
    void detectRight();
  public:
    WheelEnc(byte, byte);
    boolean checkLeft();
    boolean checkRight();
    void waitSteps(byte);
};

WheelEnc::WheelEnc(byte pinLeft, byte pinRight){
    this->pinLeft = pinLeft;
    this->pinRight = pinRight;
    pinMode(pinLeft, INPUT);
    pinMode(pinRight, INPUT);
}

void WheelEnc::detectLeft(){
    boolean left = digitalRead(pinLeft);
    if (left != lastLeft){
        lastLeft = left;
        stepLeft++;
    }
}

void WheelEnc::detectRight(){
    boolean right = digitalRead(pinRight);
    if (right != lastRight){
        lastRight = right;
        stepRight++;
    }
}

boolean WheelEnc::checkLeft(){
    detectLeft();
    if (stepLeft >= goalPulses){
        return true;
    } else{
        return false;
    }
}

boolean WheelEnc::checkRight(){
    detectRight();
    if (stepRight >= goalPulses){
        return true;
    } else{
        return false;
    }
}

void WheelEnc::waitSteps(byte goal){
    stepLeft = 0;
    stepRight = 0;
    lastLeft = digitalRead(pinLeft);
    lastRight = digitalRead(pinRight);
    goalPulses = goal;
    while(!checkLeft() || !checkRight());
}

#endif