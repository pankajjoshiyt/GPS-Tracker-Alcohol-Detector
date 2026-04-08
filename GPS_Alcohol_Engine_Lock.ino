#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial gpsSerial(2, 3);
TinyGPSPlus gps;
/*

Hello everyone, welcome back to The Electronics Creator.
In this project, we have developed an Alcohol Detection System with GPS and GSM alert.
This system detects alcohol presence and instantly sends the live location via SMS.
In this project, we use an alcohol sensor to detect alcohol levels.

When the alcohol level crosses a predefined threshold:
- The system activates a buzzer and alert LEDs
- A relay is triggered to control the vehicle system
- And most importantly, an SMS alert is sent using a GSM module

The message also includes the live location fetched using a GPS module.
This location is sent as a Google Maps link, which can be opened directly.

An LCD display is used to show system status like:
- Normal condition
- Alcohol detected
- SMS sending and confirmation

This makes the system user-friendly and efficient.
*/
int alcoholSensor = A0;
int Red = 8;
int Green = 9;
int Buzzer = 12;
int Relay = 5;

int data = 0;
bool alertSent = false;
bool systemStartSent = false;

// ================= SETUP =================
void setup() {

  Serial.begin(9600);     // GSM
  gpsSerial.begin(9600);  // GPS

  lcd.begin();
  lcd.backlight();

  pinMode(alcoholSensor, INPUT);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Relay, OUTPUT);

  lcd.print("Alcohol System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(3000);
  lcd.clear();

  digitalWrite(Red, LOW);
  digitalWrite(Green, HIGH);
  digitalWrite(Buzzer, LOW);
  digitalWrite(Relay, LOW);

  if (!systemStartSent) {
    SendSystemStartSMS();
    systemStartSent = true;
  }
}

// ================= LOOP =================
void loop() {

  // Read GPS
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  data = analogRead(alcoholSensor);

  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.print(data);

  delay(1000);

  // ===== ALERT =====
  if (data > 120) {

    if (!alertSent) {
      SendAlertSMS();
      alertSent = true;
    }

    lcd.clear();
    lcd.print("ALCOHOL ALERT!");

    digitalWrite(Red, HIGH);
    digitalWrite(Green, LOW);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(Relay, HIGH);

    delay(2000);
  }

  // ===== NORMAL =====
  else {

    lcd.clear();
    lcd.print("Alcohol Normal");

    digitalWrite(Red, LOW);
    digitalWrite(Green, HIGH);
    digitalWrite(Buzzer, LOW);
    digitalWrite(Relay, LOW);

    delay(2000);

    alertSent = false;
  }

  lcd.clear();
}

// ================= GPS =================
String getLocation() {

  String location = "Loc not fixed";

  unsigned long start = millis();

  while (millis() - start < 3000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }
  }

  if (gps.location.isValid()) {
    float lat = gps.location.lat();
    float lng = gps.location.lng();

    location = "https://maps.google.com/?q=";
    location += String(lat, 6);
    location += ",";
    location += String(lng, 6);
  }

  return location;
}

// ================= SMS =================
void SendSystemStartSMS() {

  Serial.println("AT+CMGF=1");
  delay(1000);

  Serial.println("AT+CMGS=\"+917666238355\"");
  delay(1000);

  Serial.println("System ON - Monitoring Started");
  delay(100);

  Serial.println((char)26);
  delay(3000);
}

void SendAlertSMS() {

  String location = getLocation();

  // 🔵 Show sending status
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending SMS...");
  lcd.setCursor(0, 1);
  lcd.print("Please wait");

  Serial.println("AT+CMGF=1");
  delay(1000);

  Serial.println("AT+CMGS=\"+917666238355\"");
  delay(1000);

  Serial.print("ALERT! Alcohol Detected\n");
  Serial.print("Location: ");
  Serial.print(location);

  delay(100);

  Serial.println((char)26);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMS Sent");
  lcd.setCursor(0, 1);
  lcd.print("Successfully");

  delay(2000); 
}
