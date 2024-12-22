byte RS = 10;
byte RD1 = 8;
byte RD2 = 9;
byte LS = 5;
byte LD3 = 6;
byte LD4 = 7;
void setup() {
  pinMode(RS,OUTPUT);
  pinMode(RD1,OUTPUT);
  pinMode(RD2,OUTPUT);
  pinMode(LS,OUTPUT);
  pinMode(LD3,OUTPUT);
  pinMode(LD4,OUTPUT);
}

void forward(){
  digitalWrite(RD1,0);
  digitalWrite(RD2,1);
  analogWrite(RS,150);
  digitalWrite(LD3,1);
  digitalWrite(LD4,0);
  analogWrite(LS,150);
}

void stop(){
  analogWrite(RS,0);
  analogWrite(LS,0);
}
void loop() {
  forward();
  delay(1000);
  stop();
}
