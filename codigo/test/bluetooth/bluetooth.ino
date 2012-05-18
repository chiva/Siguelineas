void setup(){
  Serial.begin(9600);
}

char c;

void loop(){
  c = Serial.read();
  while(Serial.available() > 0){
    Serial.print(Serial.read());
  }
}
