#include <Wire.h> // Library untuk komunikasi I2C
#include <LiquidCrystal_I2C.h> // Library untuk LCD I2C

// Inisialisasi objek LCD I2C.
// 0x27 adalah alamat I2C umum untuk LCD 16x2.
// 16 adalah jumlah kolom, 2 adalah jumlah baris.
// Jika LCD Anda tidak menyala, coba ganti 0x27 dengan 0x3F.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200); // Inisialisasi komunikasi serial untuk debugging
  Wire.begin(21, 22); // Inisialisasi I2C untuk ESP32: SDA di GPIO 21, SCL di GPIO 22

  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menyalakan backlight LCD

  Serial.println("LCD Dinyalakan!");
  lcd.print("Halo, Dunia!"); // Menampilkan teks di baris pertama
  lcd.setCursor(0, 1); // Pindah ke kolom 0, baris 1 (baris kedua)
  lcd.print("Dari ESP32!"); // Menampilkan teks di baris kedua
}

void loop() {
  // Kode yang akan dijalankan berulang kali bisa diletakkan di sini
  // Untuk contoh ini, kita hanya menampilkan teks statis
}