byte reset = 7;
char c;

void setup(){
  pinMode(reset, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(reset, HIGH);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop(){
  c = Serial.read();
  switch(c){
    case '1':
      digitalWrite(13, HIGH);
      break;
    case '0':
      digitalWrite(13, LOW);
      break;
  }
}
