#define PIN_TEMP D8     // TEMP PIN

// Temperature sensor
#include <Wire.h>
#include <DallasTemperature.h>

// LCP sensor
#include <U8g2lib.h>
#include <U8x8lib.h>
U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2 (U8G2_R0, D1, D2);

float sensorTemp0 ;
float sensorTemp1 ;

OneWire oneWire(PIN_TEMP); // Setup a oneWire instance to communicate with any OneWire devices  
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 


void setup() {
  Serial.begin(9600);
  
  Serial.println(".");
  Serial.println(".");
  Serial.println(".");
 
  sensors.begin();
  u8g2.begin();
  u8g2.clear();
  
  delay(2000);
   
}

void GetAllSensorValues() {
  
  sensors.requestTemperatures(); // Send the command to get temperature readings 
    sensorTemp0 = sensors.getTempCByIndex(0);
    sensorTemp1 = sensors.getTempCByIndex(1);

    if (sensorTemp0 <= 0 ) sensorTemp0 =0;
    if (sensorTemp1 <= 0 ) sensorTemp1 =0;
    
}

void loop() {
  
  
  GetAllSensorValues();
  
  DisplayLCD();
  
  delay(1000);
}




void DisplayLCD(){
  String line1 = "";
  String line2 = "";
  String line3 = "";
  
  float txtTemp0 = round(sensorTemp0*10);
  txtTemp0 = txtTemp0/10;
  float txtTemp1 = round(sensorTemp1*10);    
  txtTemp1 = txtTemp1 /10;
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_tf);
  
  /* ------- LINE 1 ------- */
  line1 = String(txtTemp0).substring(0, 4) + " | " + String(txtTemp1).substring(0, 4) + " | " ;

  u8g2.drawStr(0,12, line1.c_str() );
  
  u8g2.sendBuffer();
  
}
