/* Velocidades:
 * 4: 9600
 * 7: 57600
 * 8: 115200
 */
void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(1500);
  Serial.print("AT+NAMEJoshua");
  delay(1500);
  Serial.print("AT+PIN1234");
  delay(1500);
  Serial.print("AT+BAUD4");
}
