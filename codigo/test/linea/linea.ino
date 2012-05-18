//Deteccion a 0
byte sensores[] = {7,8,A4,4,5,6}; //D3,D2,D1,I1,I2,I3

void setup(){
  Serial.begin(9600);
  for (int i=0; i<(sizeof(sensores)); i++){
    pinMode(sensores[i], INPUT);
  }
  Serial.println("Lectura sensores: ");
}

void loop(){
  for (int i=0; i<(sizeof(sensores)); i++){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.print('\r');
}
