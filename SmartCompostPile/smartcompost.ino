//Prototype Ciro Sirignno and Ulrich from Permatopia

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//library for temperature
#include "OneWire.h" 
#include "DallasTemperature.h"

// temperature for ttgo Pin 13: Data wire is plugged into digital pin 2 on the Arduino
//Check forum https://rntlab.com/question/esp32-pin-15-onewire-for-ds18b20-conflict-with-lora/

#define ONE_WIRE_BUS 13

// Temperature: Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//Include library for sensor

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Value to give moinsture a percentage
const int SensorPin = 25;
int sensormin = 1500;
int sensormax = 3500;
int soilMoistureValue = 0;
int soilmoisturepercent=0;
int percentage = 0;

//Led
#define LED_BUILTIN 17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  //initialize Serial Monitor
  Serial.begin(115200);
  pinMode (LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);

  soilMoistureValue = analogRead(25);
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");

  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  soilmoisturepercent=(int)((soilMoistureValue - sensormax) * 100) / (sensormin - sensormax);
  Serial.print("Moisture Percentage:");
  Serial.println(soilmoisturepercent);
  display.println(soilmoisturepercent);
  display.println(soilmoisturepercent);
  display.setCursor(70,40);
  display.setTextSize(3);
  display.println(" %");
  display.display();

  delay(1000);
  display.clearDisplay();
  display.setCursor(0,0);

//then Temperature
  sensors.begin();
  sensors.requestTemperatures(); 
  uint32_t temp = sensors.getTempCByIndex(0);
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(10,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Temperat.");

  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println(temp);
  Serial.print("Temperature:");
  Serial.println(temp);
  display.setCursor(70,40);
  display.setTextSize(3);
  display.print((char)247);
  display.println("C");
  display.display();
  
  delay(1000);
  display.clearDisplay();
  display.setCursor(0,0);
}
