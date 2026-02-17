#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 1024 //number of pixels on the led
#define PIN_WS2812B 21 // pin that connects
// defining all three modes
#define PIN_MODE1 16 //DIO 9
#define PIN_MODE2 17 //DIO 8
#define PIN_MODE3 18 //DIO 7

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

LED_STATES currentState = DISABLED;


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_MODE1, INPUT);
  pinMode(PIN_MODE2, INPUT);
  pinMode(PIN_MODE3, INPUT);

  WS2812B.begin();
  WS2812B.setBrightness(15);

  WS2812B.clear();
  WS2812B.fill(WS2812B.Color(255,255,255));
  WS2812B.show();
}

void loop() {
  // put your main code here, to run repeatedly:
    if (digitalRead(PIN_MODE1)) {
      WS2812B.fill(WS2812B.Color(0,255,10));

    } else if (digitalRead(PIN_MODE2)){
      WS2812B.fill(WS1228B.Color())
    }
  delay(1500);
}
