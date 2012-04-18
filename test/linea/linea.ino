//Deteccion a 0
byte sensores[] = {6,5,4,A4,8,7}; //I1, I2, I3, D3, D2, D1

void setup(){
  Serial.begin(9600);
  for (int i=0; i<(sizeof(sensores)/sizeof(byte)); i++){
    pinMode(sensores[i], INPUT);
  }
}

void loop(){
  Serial.println("Lectura sensores: ");
  for (int i=0; i<(sizeof(sensores)/sizeof(byte)); i++){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(500);
}
