#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

byte RS = 10;
byte RD1 = 8;
byte RD2 = 9;
byte LS = 5;
byte LD3 = 6;
byte LD4 = 7;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0) { }
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");

  // Initialize motor pins
  pinMode(RS, OUTPUT);
  pinMode(RD1, OUTPUT);
  pinMode(RD2, OUTPUT);
  pinMode(LS, OUTPUT);
  pinMode(LD3, OUTPUT);
  pinMode(LD4, OUTPUT);
}

void forward(int rightSpeed, int leftSpeed) {
  digitalWrite(RD1, 0);
  digitalWrite(RD2, 1);
  analogWrite(RS, rightSpeed);
  digitalWrite(LD3, 1);
  digitalWrite(LD4, 0);
  analogWrite(LS, leftSpeed);
}

void stop() {
  analogWrite(RS, 0);
  analogWrite(LS, 0);
}

void loop() {
  mpu.update();

  static float targetYaw = mpu.getAngleZ(); 
  
  float currentYaw = mpu.getAngleZ();
  float yawError = targetYaw - currentYaw;

  int baseSpeed = 150;
  int correction = yawError * 7; 

  int rightMotorSpeed = baseSpeed + correction;
  int leftMotorSpeed = baseSpeed - correction;

  rightMotorSpeed = constrain(rightMotorSpeed, 0, 200);
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 200);

  
  forward(rightMotorSpeed, leftMotorSpeed);
  if((millis() - timer) > 100) {
    Serial.print("Yaw (X) : ");
    Serial.print(currentYaw);
    Serial.print("\tCorrection : ");
    Serial.print(correction);
    Serial.print("\tRight Speed : ");
    Serial.print(rightMotorSpeed);
    Serial.print("\tLeft Speed : ");
    Serial.println(leftMotorSpeed);
    timer = millis();
  }
  
  delay(10);
}
