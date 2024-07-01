#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>
#include <DHT.h>

// Konfigurasi untuk IR Receiver dan Transmitter
#define recvPin 2
#define dhtPin 3
#define irLedPin 13
// IRsend IrSender(irLedPin);

unsigned int address;
unsigned long command;

// Konfigurasi untuk LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C mungkin perlu disesuaikan

// Variabel untuk menyimpan mode AC
String modeAC = "OFF";

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(recvPin, false);  // Mulai IR Receiver
  IrSender.begin(irLedPin);

  // Inisialisasi LCD I2C
  lcd.init();
  lcd.backlight();
}
uint8_t sRepeats = 0;
void loop() {
  // Penerimaan kode IR dari remote asli
  if (IrReceiver.decode()) {

    // Tampilkan di Serial Monitor
    address = (uint16_t)IrReceiver.decodedIRData.address;
    command = (uint8_t)IrReceiver.decodedIRData.command;


    // Menampilkan informasi
    Serial.print("Address: 0x");
    Serial.println(address);
    Serial.print("Command: 0x");
    Serial.println(command);

    

    // Tampilkan pada LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Kode IR:");


    switch (command) {
      case 129:
        Serial.println("Menggunakan fungsi on");
        IrSender.sendNEC(address, command, sRepeats);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("AC On/Off");

        // Tambahkan aksi yang sesuai untuk command 0x01
        break;
      case 151:
        Serial.println("Menggunakan fungsi Turunkan Suhu");
        IrSender.sendNEC(address, command, sRepeats);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("AC Down");
        // Tambahkan aksi yang sesuai untuk command 0x02
        break;
      case 150:
        Serial.println("Menggunakan fungsi Naikkan Suhu");
        IrSender.sendNEC(address, command, sRepeats);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("AC Up");
        // Tambahkan aksi yang sesuai untuk command 0x03
        break;
      default:
        Serial.println("Command tidak dikenali");
        // Aksi default jika command tidak cocok dengan case mana pun
        break;
    }

    IrReceiver.resume();  // Siap menerima sinyal berikutnya
    delay(1000);          // Tunggu sebentar untuk melihat kode
  }

  // Pengiriman kode IR dan pengubahan mode AC
  // if (Serial.available() > 0) {
  //   IrReceiver.compensateAndPrintIRResultAsPronto(&Serial);
  //   String input = Serial.readStringUntil('\n'); // Baca input dari Serial Monitor
  //   input.trim(); // Hilangkan spasi tambahan

  //   // Percabangan untuk mode AC
  //   if (input.equalsIgnoreCase("COOL")) {
  //     modeAC = "COOL";
  //     // Kirim kode IR yang sesuai untuk mode COOL
  //     irsend.sendNEC(0x20DF10EF, 32); // Contoh kode IR, sesuaikan dengan AC Anda
  //   } else if (input.equalsIgnoreCase("HEAT")) {
  //     modeAC = "HEAT";
  //     // Kirim kode IR yang sesuai untuk mode HEAT
  //     irsend.sendNEC(0x20DF906F, 32); // Contoh kode IR, sesuaikan dengan AC Anda
  //   } else if (input.equalsIgnoreCase("FAN")) {
  //     modeAC = "FAN";
  //     // Kirim kode IR yang sesuai untuk mode FAN
  //     irsend.sendNEC(0x20DF40BF, 32); // Contoh kode IR, sesuaikan dengan AC Anda
  //   } else if (input.equalsIgnoreCase("OFF")) {
  //     modeAC = "OFF";
  //     // Kirim kode IR yang sesuai untuk mode OFF
  //     irsend.sendNEC(0x20DF8C7F, 32); // Contoh kode IR, sesuaikan dengan AC Anda
  //   } else {
  //     // Jika input adalah kode IR dalam format HEX
  //     unsigned long irCode = strtoul(input.c_str(), NULL, 16); // Ubah kode menjadi nilai heksadesimal
  //     irsend.sendNEC(irCode, 32); // Sesuaikan dengan protokol IR yang digunakan
  //   }

  //   // Tampilkan mode pada LCD
  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("Mode: ");
  //   lcd.print(modeAC);

  //   // Tampilkan input pada Serial Monitor
  //   Serial.print("Input yang diterima: ");
  //   Serial.println(input);
  // }
}
