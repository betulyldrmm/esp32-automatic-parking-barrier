/*
  ESP32 Otomatik Otopark Bariyeri Sistemi

  HC-SR04 sensörü ile araç algılanır.
  Araç 15 cm mesafeye geldiğinde SG90 servo motor bariyeri açar.
  Son algılamadan 3 saniye sonra bariyer otomatik olarak kapanır.

  Donanımlar:
  - ESP32
  - HC-SR04 ultrasonik mesafe sensörü
  - SG90 servo motor
  - SSD1306 OLED ekran
*/


#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 33
#define ECHO_PIN 34
#define SERVO_PIN 13
#define SDA_PIN 26
#define SCL_PIN 25

Adafruit_SSD1306 ekran(128, 64, &Wire, -1);

Servo bariyer;

const int ACILMA_MESAFESI = 15;
const int KAPALI_ACI = 90;
const int ACIK_ACI = 0;
const int BEKLEME_SURESI = 3000;

bool bariyerAcik = false;
unsigned long sonAlgilama = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!ekran.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED baslatilamadi!");
  } else {
    Serial.println("OLED calisti!");
  }

  ekran.clearDisplay();
  ekran.setTextColor(SSD1306_WHITE);
  ekran.setTextSize(2);
  ekran.setCursor(5, 10);
  ekran.println("OTOPARK");
  ekran.setTextSize(1);
  ekran.setCursor(5, 40);
  ekran.println("HOS GELDINIZ");
  ekran.display();
  delay(500);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  bariyer.attach(SERVO_PIN);
  bariyer.write(KAPALI_ACI);
}

long mesafeOlc() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long sure = pulseIn(ECHO_PIN, HIGH, 40000);
  if (sure == 0) return 999;
  return sure * 0.0343 / 2;
}

void loop() {
  long mesafe = mesafeOlc();
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");

  if (mesafe <= ACILMA_MESAFESI && mesafe > 0) {
    sonAlgilama = millis();
    if (!bariyerAcik) bariyerAc();
  }

  if (bariyerAcik && (millis() - sonAlgilama > BEKLEME_SURESI)) {
    bariyerKapat();
  }

  delay(100);
}

void bariyerAc() {
  for (int aci = KAPALI_ACI; aci >= ACIK_ACI; aci--) {   // 90'dan 0'a AZALT
    bariyer.write(aci);
    delay(15);
  }
  bariyerAcik = true;
  Serial.println("Bariyer ACILDI");
}

void bariyerKapat() {
  for (int aci = ACIK_ACI; aci <= KAPALI_ACI; aci++) {   // 0'dan 90'a ARTIR
    bariyer.write(aci);
    delay(15);
  }
  bariyerAcik = false;
  Serial.println("Bariyer KAPANDI");
}
