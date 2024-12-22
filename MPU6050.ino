#include <Wire.h>
#include <math.h>

const int MPU6050_ADDR = 0x68; // I2C address of the MPU-6050

int16_t accelX, accelY, accelZ;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Initialize MPU-6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // Access the power management register
  Wire.write(0);    // Set to zero to wake up the MPU-6050
  Wire.endTransmission(true);
}

void loop() {
  // Read accelerometer data
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B); // Starting register for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6, true); // Request 6 bytes of data

  accelX = Wire.read() << 8 | Wire.read(); // Combine high and low byte
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();

  // Convert to g (assuming ±2g range, where 16384 LSB = 1g)
  float accelX_g = accelX / 16384.0;
  float accelY_g = accelY / 16384.0;
  float accelZ_g = accelZ / 16384.0;

  // Calculate tilt angles in radians
  float angleX_rad = atan2(accelY_g, accelZ_g);
  float angleY_rad = atan2(accelX_g, accelZ_g);
  float angleZ_rad = atan2(accelX_g, accelY_g);

  // Convert radians to degrees
  float angleX_deg = angleX_rad * 180.0 / PI;
  float angleY_deg = angleY_rad * 180.0 / PI;
  float angleZ_deg = angleZ_rad * 180.0 / PI;

  // Print the tilt angles
  Serial.print("Tilt Angle X: "); Serial.print(angleX_deg); Serial.print("°");  Serial.print(" ");
  Serial.print("Tilt Angle Y: "); Serial.print(angleY_deg); Serial.print("°");  Serial.print(" ");
  Serial.print("Tilt Angle Z: "); Serial.print(angleZ_deg); Serial.print("°");  Serial.print(" ");
    Serial.println(" ");

  delay(500); // Delay for readability
}
