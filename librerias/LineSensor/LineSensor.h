#ifndef LineSensor_h
#define LineSensor_h

#include "Arduino.h"

#define LN_SENSORS 6
#define LN_CONTROLLER_K true

class LineSensor
{
  private:
    byte pinSensor[LN_SENSORS];    // {IZQ_3, IZQ_2, IZQ_1, DCHA_1, DCHA_2, DCHA_3}
    byte lastRead[LN_SENSORS];
    static const int8_t sensorWeight[LN_SENSORS];
    byte weight;
    byte sensorsOn;
  public:
    LineSensor(byte[]);
    void read();
    byte follow();
};

LineSensor::LineSensor(byte pinSensor[]){
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

#ifdef LN_CONTROLLER_K

byte LineSensor::follow(){
    read();
    weight = 0;
    sensorsOn = 0;
    for (byte i=0; i<LN_SENSORS; i++){
        if (lastRead[i]){
            weight += sensorWeight[i];
            sensorsOn++;
        }
    }
    return weight/sensorsOn;
}

#endif

#endif