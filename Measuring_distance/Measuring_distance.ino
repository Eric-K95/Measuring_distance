//Measuring distance or Detecting object by using Sonar sensor
//Sketched by JIN-WOO KIM

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int TRIGGER_PIN = 2; // trigger pin to Arduino pin 2
const int  ECHO_PIN = 3; // echo pin to Arduino pin 3
int  MAX_DISTANCE = 150; // Max. distance (range at 0-150cm)
int dist = 0;
#include <NewPing.h>
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // create a new NewPing instance call sonar
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 7
DHT dht(DHTPIN, DHTTYPE);

int ledPin1 = 13; //red led light
int ledPin2 = 12; //blue led light
int buzzerPin = 9;
void setup() {
  pinMode(ledPin1, OUTPUT); // initiaialize the LED pin as an output
  pinMode(ledPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  analogWrite(ledPin1, LOW);
  analogWrite(ledPin2, LOW);
  Serial.begin(9600); // set baud rate as 9600
  lcd.init();
  lcd.backlight();
  lcd.begin(20, 4);
  lcd.setCursor(5, 0); //first column, row #5
  lcd.print("Hello!");
  lcd.setCursor(0, 1); //second column, row #1
  lcd.print("Mechatronics:)");
  delay(2000);   //delay of the message
  lcd.clear();   // clear screen
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("UltrasonicSensor");
  lcd.setCursor(0, 1);
  lcd.print(" Temp  &  Humid ");
  delay(2000); //delay 2000ms
  lcd.clear();
  dht.begin();
}
void loop() {
  //print values on Serial Monitor
  Serial.print("Ping: "); //print name in Serial Monitor
  Serial.println(dist); //print measurement in Serial Monitor
  Serial.print("  |  ");
  if ( isnan(humi) || isnan(tempC) ) {
    Serial.println("Error");
  } //fail to read from DHT sensor
  else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");
    Serial.print("  |  ");
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ");
    Serial.print("  |  ");
  }
  //print values on lcd screen
  lcd.setCursor(0, 0); //first column, row #1
  lcd.print("Distance:"); //print name on LCD
  lcd.setCursor(13, 0); //first column, row #13
  lcd.print("cm"); //print units
  lcd.setCursor(10, 0); //first column, row #10
  lcd.print(dist); //print distance on LCD
  lcd.setCursor(0, 1); //second coulumn, row#0
  lcd.print("Temp:");
  lcd.setCursor(5, 1); //second coulumn, row#5
  lcd.print(tempC);
  lcd.setCursor(7, 1); //second coulumn, row#7
  lcd.print("c");  //unit of temperature
  lcd.setCursor(8, 1); //second coulumn, row#8
  lcd.print("Humi:");
  lcd.setCursor(13, 1); //second coulumn, row#13
  lcd.print(humi);
  lcd.setCursor(15, 1); //second coulumn, row#15
  lcd.print("%"); //percentage of huminity
  delay(1000); //delay 1000ms
  lcd.clear(); //clear the LCD screen to show next measurement

  int analogValue = analogRead(dist);
  if (dist > 30 || dist <= 0) {
    digitalWrite(ledPin1, LOW); //turn off ledPin1
    digitalWrite(ledPin2, HIGH); //turn on ledPin2
    digitalWrite(buzzerPin, LOW);
  } //turn off the buzzer
  else {
    digitalWrite(ledPin1, HIGH); //turn on the ledPin1
    digitalWrite(ledPin2, LOW); //turn off the ledPin2
    digitalWrite(buzzerPin, HIGH); //turn on the buzzer
  }
}
