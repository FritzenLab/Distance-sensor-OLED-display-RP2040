#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // Configure our 64x32 pixels display

int distancemm; // varible for the distance from the VL53L0x sensor
long oldtime; // variable for keeping track of time

void setup() {
  u8g2.begin();
  
  Serial.begin(115200);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous(50);

}

// fonts https://github.com/olikraus/u8g2/wiki/fntlistall#4-pixel-height (I have picked two of them for this article)

void loop()
{
  
  if(millis() - oldtime > 100){ // Only does anything every 100ms
    oldtime= millis();

    distancemm= sensor.readRangeContinuousMillimeters();
    Serial.println(distancemm);  
    
    u8g2.clearBuffer();          // clear the internal memory  
    u8g2.setCursor(0, 24);
    u8g2.setFont(u8g2_font_t0_17_tn);  // choose a suitable font
    u8g2.print(distancemm); 
    u8g2.setCursor(40, 24);
    u8g2.setFont(u8g2_font_9x18_mf);
    u8g2.print("mm"); 
    u8g2.sendBuffer();          // transfer internal memory to the display 
  }
     
}
