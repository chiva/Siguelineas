#ifndef PathFollow_h
#define PathFollow_h

#include "Arduino.h"
#include <Motor298.h>
#include <Driver298.h>
#include <WheelEnc.h>

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PTH_MAX_STEP 10
#define PTH_STEPS    10
#define PTH_FW       'i'
#define PTH_BW       'k'
#define PTH_LFT      'j'
#define PTH_RGT      'l'
#define PTH_STP      ' '
#define PTH_END      '\n'
#define PTH_DLY      1000

class PathFollow
{
  private:
    Driver298 *motor;
    WheelEnc *encoder;
    void read();
    char steps[PTH_MAX_STEP];
  public:
    PathFollow(Driver298*, WheelEnc*);
    void follow();
};

PathFollow::PathFollow(Driver298 *motor, WheelEnc *encoder){
    this->motor = motor;
    this->encoder = encoder;
}

void PathFollow::read(){
    byte i=0;
    char c;
    while(Serial.available() > 0) Serial.read();
    Serial.println(F("^:" STR(PTH_FW) " v:" STR(PTH_BW) " <:" STR(PTH_LFT) " >:" STR(PTH_RGT) " Stop: space"));
    Serial.println(F("Introduce el camino: "));
    while(i<PTH_MAX_STEP){
        if(Serial.available() > 0){
            c = Serial.read();
            if(c == '\n'){
                steps[i] = 0;
                break;
            }
            steps[i++] = c;
            if(i == PTH_MAX_STEP-1){
                steps[i] = 0;
                break;
            }
        }
    }
}

void PathFollow::follow(){
    byte i;
    while(1){
        read();
        for(i=0; steps[i]!=0; ++i){
            switch(steps[i]){
                case PTH_FW:
                    motor->forward(D298_MAX_SPEED);
                    encoder->waitSteps(PTH_STEPS);
                    break;
                case PTH_BW:
                    motor->reverse(D298_MAX_SPEED);
                    encoder->waitSteps(PTH_STEPS);
                    break;
                case PTH_LFT:
                    motor->turn(D298_LEFT, D298_MAX_SPEED, D298_MAX_SPEED);
                    encoder->waitSteps(PTH_STEPS);
                    break;
                case PTH_RGT:
                    motor->turn(D298_RIGHT, D298_MAX_SPEED, D298_MAX_SPEED);
                    encoder->waitSteps(PTH_STEPS);
                    break;
                case PTH_STP:
                    motor->stop();
                    delay(PTH_DLY);
                    break;
            }
        }
    }
}

#endif