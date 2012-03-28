#include <Motor298.h>
#include <Driver298.h>
#include <WheelEnc.h>

#define STEPS 12
#define EOC 'z'

char path[60] = "";
byte index = 0;
Motor298 motor;
WheelEnc enc;

void setup(){
  Serial.begin(9600);
  digitalRead();
  pinMode();
}

void loop(){
  read();
  execute();
}

void read(){
  Serial.println("Introduce camino:");
  index = 0;
  char c;
  while(true){
    if (Serial.available() > 0){
      c = Serial.read();
      if (c == EOC){
        path[index] = 0;
        return;
      }
      path[index++] = c;
    }
  }
}

void execute(){
  Serial.print("Executing... ");
  enc.setGoal(STEPS);
  index = 0;
  switch(path[index++]){
    case 0:
      Serial.println("Done");
      Serial.println();
      return;
    case 'a':
      straight(D298_FW);
      break;
    case 'b':
      straight(D298_BW);
      break;
    case 'c':
      turn(D298_LEFT);
      break;
    case 'd':
      turn(D298_RIGHT);
      break;
  }
}

void straight(byte direction){
  byte speedLeft = enc.checkLeft() ? 0:255;
  byte speedRight = enc.checkRight() ? 0:255;
  motor.setSpeed(direction, speedLeft, direction, speedRight);
}

void turn(byte direction){
  byte speedLeft = checkLeft() ? 0:255;
  byte speedRight = checkRight() ? 0:255;
  motor.setSpeed(direction, speedLeft, !direction, speedRight);
}
