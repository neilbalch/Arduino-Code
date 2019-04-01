#include <Arduino.h>
#include <HardwareSerial.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#undef LED_BUILTIN
#define LED_BUILTIN PC13

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(250000);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();

  Serial.print((String)(millis() / 1000.0));

  // Serial.print("t: ");
  // Serial.print(mpu6050.getTemp());
  Serial.print("\tαX: ");
  Serial.print(mpu6050.getAccX());
  Serial.print("\tαY: ");
  Serial.print(mpu6050.getAccY());
  Serial.print("\tαZ: ");
  Serial.print(mpu6050.getAccZ());

  Serial.print("\tωX: ");
  Serial.print(mpu6050.getGyroX());
  Serial.print("\tωY: ");
  Serial.print(mpu6050.getGyroY());
  Serial.print("\tωZ: ");
  Serial.print(mpu6050.getGyroZ());

  // Serial.print("\tαθX: ");
  // Serial.print(mpu6050.getAccAngleX());
  // Serial.print("\tαθY: ");
  // Serial.print(mpu6050.getAccAngleY());

  // Serial.print("\tωθX: ");
  // Serial.print(mpu6050.getGyroAngleX());
  // Serial.print("\tωθY: ");
  // Serial.print(mpu6050.getGyroAngleY());
  // Serial.print("\tωθZ: ");
  // Serial.print(mpu6050.getGyroAngleZ());

  // Serial.print("\tθX: ");
  // Serial.print(mpu6050.getAngleX());
  // Serial.print("\tθY: ");
  // Serial.print(mpu6050.getAngleY());
  // Serial.print("\tθZ: ");
  // Serial.print(mpu6050.getAngleZ());
  Serial.println();
}