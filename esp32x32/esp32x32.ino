#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B  21  // GPIO ESP32-S3 pin that connects to WS2812B
#define NUM_PIXELS  1024  // The number of LEDs (pixels) on WS2812B

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  WS2812B.begin(); // INITIALIZE WS2812B strip object (REQUIRED)
  WS2812B.setBrightness(15); // a value from 0 to 255
  Serial.begin(9600);

  WS2812B.clear();
  WS2812B.fill(WS2812B.Color(255,255,255));
  WS2812B.show();
}

void loop() {
  WS2812B.clear();
  WS2812B.fill(WS2812B.Color(255,255,255));
  WS2812B.show();
  delay(1000);
}
