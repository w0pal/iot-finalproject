// #include <ESP32Servo.h>

// Servo myServo;  // Buat objek servo

// const int servoPin = 27;  // Tentukan pin GPIO yang terhubung ke pin sinyal servo

// void setup() {
//   // Izinkan pin GPIO untuk menjadi output PWM, yang diperlukan untuk servo
//   ESP32PWM::allocateTimer(0);
//   ESP32PWM::allocateTimer(1);
//   ESP32PWM::allocateTimer(2);
//   ESP32PWM::allocateTimer(3);
//   myServo.setPeriodHertz(50);  // Servo standar membutuhkan sinyal 50Hz

//   myServo.attach(servoPin, 500, 2500);  // Sambungkan objek servo ke pin dan tentukan rentang pulsa
//                                         // 500us untuk 0 derajat, 2500us untuk 180 derajat
//                                         // Ini mungkin perlu penyesuaian untuk servo spesifik Anda
//   Serial.begin(115200);
//   Serial.println("Servo Ready!");
// }

// void loop() {
//   // Gerakkan servo dari 0 ke 180 derajat
//   for (int pos = 0; pos <= 90; pos += 1) {  // Pergi dari 0 ke 180 derajat
//     myServo.write(pos);                     // Set posisi servo
//     delay(10);                              // Tunggu servo mencapai posisi
//   }

//   delay(5000);  // Tunggu 1 detik

//   // Gerakkan servo dari 180 ke 0 derajat
//   for (int pos = 90; pos >= 0; pos -= 1) {  // Pergi dari 180 ke 0 derajat
//     myServo.write(pos);                     // Set posisi servo
//     delay(10);                              // Tunggu servo mencapai posisi
//   }
//   delay(5000);  // Tunggu 1 detik
// }
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// Pin konfigurasi
#define SS_PIN    5    // SDA pin RFID
#define RST_PIN   22   // RST pin RFID
#define SERVO_PIN 13   // Pin sinyal servo
#define LED_PIN   21   // Pin sinyal LED

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

void setup() {
  Serial.begin(9600);
  
  // Inisialisasi Servo
  myServo.setPeriodHertz(50); // Set frekuensi PWM untuk servo
  myServo.attach(SERVO_PIN, 500, 2400); // Atur pin servo dan batas pulsa

  // Inisialisasi LED
  pinMode(LED_PIN, OUTPUT);

  // Inisialisasi RFID
  SPI.begin();          // Inisialisasi SPI bus
  rfid.PCD_Init();      // Inisialisasi RFID

  Serial.println("Sistem siap. Tempelkan kartu RFID Anda.");
}

void loop() {
  // Gerakkan servo dari 0° ke 180° dan kembali
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(10);
  }
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(10);
  }

  // LED berkedip
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);

  // Periksa apakah ada kartu baru yang terdeteksi
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("UID terdeteksi: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Hentikan komunikasi dengan kartu
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

