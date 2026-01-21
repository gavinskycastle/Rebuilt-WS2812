#include <Adafruit_NeoPixel.h>
#include "test_pattern.h"

#define PIN_WS2812B  21  // GPIO ESP32-S3 pin that connects to WS2812B
#define NUM_PIXELS  5  // The number of LEDs (pixels) on WS2812B

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  WS2812B.begin(); // INITIALIZE WS2812B strip object (REQUIRED)
  WS2812B.setBrightness(20); // a value from 0 to 255
  Serial.begin(9600);
}

void loop() {
  
  for(uint32_t* frame : frames) {
    WS2812B.clear();

    for (uint16_t pixel = 0; pixel < NUM_PIXELS; pixel++) {
      WS2812B.setPixelColor(pixel, frame[pixel]);
    }

    WS2812B.show();
    delay(1000);
  }
  //   Serial.println("Displayed frame");
  //   delay(frame_time * 1000);
  // }
}
