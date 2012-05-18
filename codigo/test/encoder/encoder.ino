//Deteccion a 0
byte sensores[] = {3,2}; //I,D

void setup(){
  Serial.begin(9600);
  for (int i=0; i<sizeof(sensores)); ++i){
    pinMode(sensores[i], INPUT);
  }
  Serial.println("Lectura encoder: ");
}

void loop(){
  for (int i=0; i<(sizeof(sensores)); ++i){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.print('\r');
}
