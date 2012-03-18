#ifndef Bluetooth_h
#define Bluetooth_h

#include "Arduino.h"

class Bluetooth
{
  private:
    byte pinReset;
    unsigned long initial;
    boolean connected();
    void dumpResponse();
  public:
    Bluetooth(byte);
    void turnOn();
    void turnOff();
    void setPinCode(char[]);
    void setName(char[]);
    void reset();
};

Bluetooth::Bluetooth(byte pinReset){
    this->pinReset = pinReset;
    pinMode(pinReset, OUTPUT);
    turnOff();
}

boolean Bluetooth::connected(){
    return millis() - initial > 1000;
}

void Bluetooth::dumpResponse(){
    unsigned long inicial = millis();
    
    while (Serial.available()){
        Serial.read();
    }
}

void Bluetooth::setPinCode(char pin[]){
    if (!connected()){
        Serial.print("AT+PIN");
        Serial.print(pin);
        delay(1000);
        dumpResponse();
    }
}

void Bluetooth::setName(char name[]){
    if (!connected()){
        Serial.print("AT+NAME");
        Serial.print(name);
        delay(1000);
        dumpResponse();
    }
}

inline void Bluetooth::turnOn(){
    digitalWrite(pinReset, HIGH);
    initial = millis();
}

inline void Bluetooth::turnOff(){
    digitalWrite(pinReset, LOW);
    initial = 0;
}

void Bluetooth::reset(){
    if (digitalRead(pinReset)){
        turnOff();
        turnOn();
    }
}

#endif