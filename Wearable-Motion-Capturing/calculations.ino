#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  mpu.initialize();

  // Verify the connection
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
  }

  delay(1000);
}

void loop() {
  // Read sensor data
  int16_t ax, ay, az, gx, gy, gz;
  float roll, pitch, yaw;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert raw values to actual units
  float accelerationX = ax / 16384.0; // LSB/g
  float accelerationY = ay / 16384.0; // LSB/g
  float accelerationZ = az / 16384.0; // LSB/g

  float gyroX = gx / 131.0; // LSB/degrees per second
  float gyroY = gy / 131.0; // LSB/degrees per second
  float gyroZ = gz / 131.0; // LSB/degrees per second

  roll = atan2(ay, az) * (180.0 / PI);
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * (180.0 / PI);
  yaw = atan2(gy, gz) * (180.0 / PI);

  // Print the acceleration and gyrometer values
  Serial.print("Acceleration (g): ");
  Serial.print("X = ");
  Serial.print(accelerationX);
  Serial.print(", Y = ");
  Serial.print(accelerationY);
  Serial.print(", Z = ");
  Serial.println(accelerationZ);

  Serial.print("Gyrometer (degrees/s): ");
  Serial.print("X = ");
  Serial.print(gyroX);
  Serial.print(", Y = ");
  Serial.print(gyroY);
  Serial.print(", Z = ");
  Serial.println(gyroZ);

  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("\tPitch: ");
  Serial.print(pitch);
  Serial.print("\tYaw: ");
  Serial.println(yaw);

  // Send values to the Serial Plotter
  Serial.print(accelerationX);
  Serial.print(",");
  Serial.print(accelerationY);
  Serial.print(",");
  Serial.print(accelerationZ);
  Serial.print(",");
  Serial.print(gyroX);
  Serial.print(",");
  Serial.print(gyroY);
  Serial.print(",");
  Serial.print(gyroZ);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  Serial.println(yaw);

  delay(10); // Adjust delay as per your requirements
}
