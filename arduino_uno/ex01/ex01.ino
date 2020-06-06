void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  if(digitalRead(0))
    digitalWrite(5);
  if(digitalRead(1))
    digitalWrite(6);
  if(digitalRead(3))
    digitalWrite(7);
  delay(10);
}
