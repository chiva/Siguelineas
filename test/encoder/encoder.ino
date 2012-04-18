//Deteccion a 0
byte sensores[] = {3,2}; //I,D

void setup(){
  Serial.begin(9600);
  for (int i=0; i<(sizeof(sensores)/sizeof(byte)); i++){
    pinMode(sensores[i], INPUT);
  }
}

void loop(){
  Serial.println("Lectura encoder: ");
  for (int i=0; i<(sizeof(sensores)/sizeof(byte)); i++){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(500);
}
