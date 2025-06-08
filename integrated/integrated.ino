#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin konfigurasi
#define SS_PIN    5    // SDA pin RFID
#define RST_PIN   4   // RST pin RFID
#define SERVO_PIN 2   // Pin sinyal servo
#define LED_PIN   21   // Pin sinyal LED
#define LCD_ADDR 0x27 // Alamat I2C LCD, sesuaikan jika berbeda
#define LCD_COLS 16
#define LCD_ROWS 2

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
  Serial.begin(9600);
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistem siap");
  lcd.setCursor(0, 1);
  lcd.print("Tempelkan kartu");

  // Inisialisasi Servo
  myServo.setPeriodHertz(50); // Set frekuensi PWM untuk servo
  myServo.attach(SERVO_PIN, 500, 2400); // Atur pin servo dan batas pulsa

  // Inisialisasi RFID
  SPI.begin();          // Inisialisasi SPI bus
  rfid.PCD_Init();      // Inisialisasi RFID
  Serial.println("Sistem siap. Tempelkan kartu RFID Anda.");
}

void loop() {
  // Tampilkan status di LCD
  lcd.setCursor(0, 0);
  lcd.print("Menunggu kartu  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  digitalWrite(LED_PIN, LOW); // Pastikan LED mati saat idle

  // Periksa apakah ada kartu baru yang terdeteksi
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // LED dan LCD: sedang membaca kartu
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Membaca kartu   ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(1500); // Delay 1.5 detik

    // LED dan LCD: kartu terdeteksi
    lcd.setCursor(0, 0);
    lcd.print("Kartu terdeteksi!");
    lcd.setCursor(0, 1);
    lcd.print("UID:           ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      lcd.print(rfid.uid.uidByte[i], HEX);
      lcd.print(" ");
    }
    Serial.print("UID terdeteksi: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    delay(2000); // Tampilkan UID selama 2 detik

    // Servo bergerak ke 180 derajat
    myServo.write(180);
    delay(1000); // Tunggu servo selesai bergerak
    myServo.write(0); // Kembali ke posisi awal (opsional, bisa dihapus jika ingin tetap di 180)

    // Hentikan komunikasi dengan kartu
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    digitalWrite(LED_PIN, LOW); // Matikan LED
    lcd.setCursor(0, 0);
    lcd.print("Sistem siap     ");
    lcd.setCursor(0, 1);
    lcd.print("Tempelkan kartu ");
  }
}

