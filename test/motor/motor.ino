#include <Motor298.h>
#include <Driver298.h>

Driver298 motor(A0,A1,10,A2,A3,9);

void setup(){
}

void loop(){
  for(int i=D298_FULL_SPEED/2; i<=D298_FULL_SPEED; ++i){
    motor.forward(i);
    delay(50);
    if(i == D298_FULL_SPEED){
      motor.forward(i);
      delay(2000);
    }
  }
}
