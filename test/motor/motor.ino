#include <Motor298.h>
#include <Driver298.h>

Driver298 motor(A0,A1,10,A2,A3,9), *test;

void setup(){
  test = &motor;
  for(int i=D298_FULL_SPEED/2; i<=D298_FULL_SPEED; ++i){
    test->forward(i);
    delay(25);
  }
}

void loop(){
    test->forward(D298_FULL_SPEED);
    delay(2000);
    test->reverse(D298_FULL_SPEED);
    delay(2000);
    test->turn(D298_LEFT,D298_FULL_SPEED,D298_FULL_SPEED);
    delay(2000);
    test->turn(D298_RIGHT,D298_FULL_SPEED,D298_FULL_SPEED);
    delay(2000);
}
