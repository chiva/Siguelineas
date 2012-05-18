#ifndef PathFollow_h
#define PathFollow_h

#include "Arduino.h"
#include <Motor298.h>
#include <Driver298.h>
#include <WheelEnc.h>

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PTH_MAX_STEP     10
#define PTH_ENC_STEPS    25
#define PTH_FW           'i'
#define PTH_BW           'k'
#define PTH_LFT          'j'
#define PTH_RGT          'l'
#define PTH_STP          ' '
#define PTH_END          '\n'
#define PTH_DLY          1000

class PathFollow
{
  private:
    Driver298 *motor;
    WheelEnc *encoder;
    void read();
    void waitSteps();
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
    while(Serial.available()) Serial.read();
    Serial.println(F("^:" STR(PTH_FW) " v:" STR(PTH_BW) " <:" STR(PTH_LFT) " >:" STR(PTH_RGT) " Stop: espacio Vacio: menu"));
    Serial.println(F("Introduce el camino: "));
    while(i<PTH_MAX_STEP){
        if(Serial.available() > 0){
            c = Serial.read();
            Serial.print(c);
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
    Serial.println();
}

void PathFollow::waitSteps(){
    while(1){
        if(encoder->checkLeft()) motor->left->stop();
        if(encoder->checkRight()) motor->right->stop();
        if(encoder->checkLeft() && encoder->checkRight()){
            motor->left->stop();
            motor->right->stop();
            return;
        }
    }
}

void PathFollow::follow(){
    Serial.println(F("Modo sigue caminos activado"));
    byte i;
    while(1){
        read();
        if(steps[0]=0) return;
        Serial.println(F("Ejecutando..."));
        for(i=0; steps[i]!=0; i++){
            switch(steps[i]){
                case PTH_FW:
                    Serial.print(F("Recto........ "));
                    motor->forward(D298_FULL_SPEED);
                    encoder->setGoal(PTH_ENC_STEPS);
                    waitSteps();
                    break;
                case PTH_BW:
                    Serial.print(F("Atras........ "));
                    motor->reverse(D298_FULL_SPEED);
                    encoder->setGoal(PTH_ENC_STEPS);
                    waitSteps();
                    break;
                case PTH_LFT:
                    Serial.print(F("Izquierda.... "));
                    motor->turn(D298_LEFT, D298_FULL_SPEED, D298_FULL_SPEED);
                    encoder->setGoal(PTH_ENC_STEPS);
                    waitSteps();
                    break;
                case PTH_RGT:
                    Serial.print(F("Derecha...... "));
                    motor->turn(D298_RIGHT, D298_FULL_SPEED, D298_FULL_SPEED);
                    encoder->setGoal(PTH_ENC_STEPS);
                    waitSteps();
                    break;
                case PTH_STP:
                    Serial.print(F("Parar........ "));
                    motor->stop();
                    delay(PTH_DLY);
                    break;
                default:
                    Serial.println(F("Desconocido.. "));
                    break;
            }
            Serial.println(F("OK"));
        }
    }
}

#endif