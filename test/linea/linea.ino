byte sensores[] = {4,5,6,16,2,3}; //I1, I2, I3, D3, D2, D1

void setup(){
  Serial.begin(9600);
  for (int i=0; i<6; i++){
    pinMode(sensores[i], INPUT);
  }
}

void loop(){
  Serial.println("Lectura sensores: ");
  for (int i=0; i<6; i++){
    Serial.print(digitalRead(sensores[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(500);
}
