#include <ESP32Servo.h>

Servo myServo;  // Buat objek servo

const int servoPin = 27; // Tentukan pin GPIO yang terhubung ke pin sinyal servo

void setup() {
  // Izinkan pin GPIO untuk menjadi output PWM, yang diperlukan untuk servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo.setPeriodHertz(50); // Servo standar membutuhkan sinyal 50Hz

  myServo.attach(servoPin, 500, 2500); // Sambungkan objek servo ke pin dan tentukan rentang pulsa
                                        // 500us untuk 0 derajat, 2500us untuk 180 derajat
                                        // Ini mungkin perlu penyesuaian untuk servo spesifik Anda
  Serial.begin(115200);
  Serial.println("Servo Ready!");
}

void loop() {
  // Gerakkan servo dari 0 ke 180 derajat
  for (int pos = 0; pos <= 90; pos += 1) { // Pergi dari 0 ke 180 derajat
    myServo.write(pos); // Set posisi servo
    delay(10);          // Tunggu servo mencapai posisi
  }

  delay(5000); // Tunggu 1 detik

  // Gerakkan servo dari 180 ke 0 derajat
  for (int pos = 90; pos >= 0; pos -= 1) { // Pergi dari 180 ke 0 derajat
    myServo.write(pos); // Set posisi servo
    delay(10);          // Tunggu servo mencapai posisi
  }
  delay(5000); // Tunggu 1 detik
}