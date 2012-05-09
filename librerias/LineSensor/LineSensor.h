#ifndef LineSensor_h
#define LineSensor_h

#include "Arduino.h"
#include <Motor298.h>
#include <Driver298.h>

#define LN_SENSORS 6
#define LN_CONTROLLER_P

#ifdef LN_CONTROLLER_P
    #define LN_KP 1
#endif
#ifdef LN_CONTROLLER_PD
    #define LN_MAX_ERROR 99
    #define LN_KP 50
    #define LN_KD 0
#endif

class LineSensor
{
  private:
    Driver298 *motor;
    byte pinSensor[LN_SENSORS];    // {IZQ_3, IZQ_2, IZQ_1, DCHA_1, DCHA_2, DCHA_3}
    byte lastRead[LN_SENSORS];
    static const int8_t sensorWeight[LN_SENSORS];
    void correct(int);
    void read();
    int errorP();
#ifdef LN_CONTROLLER_PD
    int errorD();
#endif
  public:
    LineSensor(Driver298*, byte[]);
    void follow();
};

LineSensor::LineSensor(Driver298 *motor, byte pinSensor[]){
    this->motor = motor;
    
    for (byte i=0; i<LN_SENSORS; i++){
        this->pinSensor[i] = pinSensor[i];
        pinMode(pinSensor[i], INPUT);
    }
}

const int8_t LineSensor::sensorWeight[LN_SENSORS] = {-5, -3, -1, 1, 3, 5};

inline void LineSensor::read(){
    for (byte i=0; i<LN_SENSORS; i++){
        lastRead[i] = digitalRead(pinSensor[i]);
    }
}

inline int LineSensor::errorP(){
    int8_t weight = 0;
    static int8_t lastWeight = 0;
    byte sensorsOn = 0;
    
    for (byte i=0; i<LN_SENSORS; i++){
        if (!lastRead[i]){
            weight += sensorWeight[i];
            sensorsOn++;
        }
    }
    if (!sensorsOn){
        motor->setSpeed(D298_FW, D298_FULL_SPEED, D298_BW, D298_FULL_SPEED);
        weight = 5;
    } else {
        weight /= sensorsOn;
        lastWeight = weight;
    }
    weight *= LN_KP;
    Serial.print(F("ErrorP: "));
    Serial.println(weight);
    return weight;
}

#ifdef LN_CONTROLLER_P

void LineSensor::follow(){
    Serial.println(F("Modo siguelineas activado"));
    while(1){
        read();
        correct(errorP());
    }
}

void LineSensor::correct(int weight){
    if (weight > 0){
        motor->setSpeed(D298_FW, D298_FULL_SPEED, D298_FW, map(abs(weight),0,5,D298_FULL_SPEED,0));
    }
    else if (weight < 0){
        motor->setSpeed(D298_FW, map(abs(weight),0,5,D298_FULL_SPEED,0), D298_FW, D298_FULL_SPEED);
    } else{
        motor->forward(D298_FULL_SPEED);
    }
}

#endif //LN_CONTROLLER_P

#ifdef LN_CONTROLLER_PD

void LineSensor::follow(){
    int error;
    unsigned int lastTime = millis();
    
    Serial.println(F("Modo siguelineas activado"));
    while(1){
        while(millis() - lastTime < 10);
        lastTime = millis();
        read();
        error = errorP() + errorD();
        correct(error);
    }
}

void LineSensor::correct(int error){
    if(error > D298_FULL_SPEED)
        error = D298_FULL_SPEED;
    else if(error < -D298_FULL_SPEED)
        error = -D298_FULL_SPEED;
    
    if (error > 0){
        motor->setSpeed(D298_FW, D298_FULL_SPEED, D298_FW, D298_FULL_SPEED-error);
    }
    else if (error < 0){
        motor->setSpeed(D298_FW, D298_FULL_SPEED-error, D298_FW, D298_FULL_SPEED);
    } else{
        motor->forward(D298_FULL_SPEED);
    }
}

int LineSensor::errorD(){
    int error = LN_MAX_ERROR;
    static int lastError = 0;
    static int errorD=0;
    static int lastErrorD = 0;
    static int tic = 1;
    static int lastTic = 1;
    
    int diferencia = 0;
    
    for (byte i=LN_SENSORS-1; i>=0; i--){
        if (!lastRead[i] && abs(sensorWeight[i]) < error) error = sensorWeight[i];
    }
    if (error == LN_MAX_ERROR){
        if (lastError < 0) error = -sensorWeight[LN_SENSORS]-2;
        else if(lastError > 0) error = sensorWeight[LN_SENSORS]+2;
    }
    
    if (error == lastError){
        tic++;
        if(tic > 30000) tic = 30000;
        if(tic > lastTic) errorD = lastErrorD/tic;
    } else {
        diferencia = error - lastError;
        errorD = LN_KD*(diferencia)/tic; //error medio
        lastErrorD = errorD;
        lastTic=tic;
        tic=1;
    }
    
    lastError = error;
    Serial.print(F("errorD: "));
    Serial.println(errorD);
    return(errorD);
}

#endif //LN_CONTROLLER_PD

#endif //LineSensor_h