#include <Motor298.h>
#include <Driver298.h>

Driver298 motor(A0,A1,10,A2,A3,9);

void setup(){
  motor.forward(D298_MAX_SPEED);
}

void loop(){
}
