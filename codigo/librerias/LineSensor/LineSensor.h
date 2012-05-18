#ifndef LineSensor_h
#define LineSensor_h

#include "Arduino.h"
#include <Motor298.h>
#include <Driver298.h>

#define LN_SENSORS 6

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
    Serial.print(F("ErrorP: "));
    Serial.println(weight);
    return weight;
}

void LineSensor::follow(){
    Serial.println(F("Modo siguelineas activado"));
    while(1){
        read();
        correct(errorP());
        
        if(Serial.available()){
            Serial.read();
            return;
        }
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

#endif //LineSensor_h