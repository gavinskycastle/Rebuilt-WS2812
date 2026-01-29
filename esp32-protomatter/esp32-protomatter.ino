#include <Arduino.h>

#define ASYNC_UDP_ESP32_ETHERNET_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_ESP32_ETHERNET_LOGLEVEL_      2

#define ESP32_Ethernet_onEvent            ESP32_W5500_onEvent
#define ESP32_Ethernet_waitForConnect     ESP32_W5500_waitForConnect

#include <AsyncUDP_ESP32_Ethernet.h>

IPAddress remoteIPAddress = IPAddress(10, 42, 1, 2);

#define UDP_REMOTE_PORT         5800

/////////////////////////////////////////////

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

/////////////////////////////////////////////

AsyncUDP udp;

void initEthernet()
{
  UDP_LOGWARN(F("Default SPI pinout:"));
  UDP_LOGWARN1(F("SPI_HOST:"), ETH_SPI_HOST);
  UDP_LOGWARN1(F("MOSI:"), MOSI_GPIO);
  UDP_LOGWARN1(F("MISO:"), MISO_GPIO);
  UDP_LOGWARN1(F("SCK:"),  SCK_GPIO);
  UDP_LOGWARN1(F("CS:"),   CS_GPIO);
  UDP_LOGWARN1(F("INT:"),  INT_GPIO);
  UDP_LOGWARN1(F("SPI Clock (MHz):"), SPI_CLOCK_MHZ);
  UDP_LOGWARN(F("========================="));

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_Ethernet_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W6100_Mac = W6100_Default_Mac);
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[millis() % NUMBER_OF_MAC] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  //ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_Ethernet_waitForConnect();

  ///////////////////////////////////
}

void setupUDP() {
  while (!Serial && (millis() < 5000));

  delay(500);

  Serial.print(F("\nStart Async_UDPClient on "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);

  Serial.println(WEBSERVER_ESP32_W5500_VERSION);
  
  Serial.println(ASYNC_UDP_ESP32_ETHERNET_VERSION);

  Serial.setDebugOutput(true);

  ///////////////////////////////////

  initEthernet();

  ///////////////////////////////////

  // Client address
  Serial.print("Async_UDPClient started @ IP address: ");
  Serial.println(ETH.localIP());

  if (udp.connect(remoteIPAddress, UDP_REMOTE_PORT))
  {
    Serial.println("UDP connected");

    udp.onPacket([](AsyncUDPPacket packet)
    {
      parsePacket( packet);
    });

    //Send unicast
    udp.print("Hello Server!");
  }
}

#include <Adafruit_Protomatter.h>

// --- Matrix pins and size (32x32 panel) ---
uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12}; // R1,G1,B1,R2,G2,B2
uint8_t addrPins[] = {17, 18, 19, 20, 21};   // A0-A4 for 32 rows
uint8_t clockPin   = 14;
uint8_t latchPin   = 15;
uint8_t oePin      = 16;

// Configure for a single 32x32 panel. rgb count = 6 (R1,G1,B1,R2,G2,B2)
Adafruit_Protomatter matrix(32, 32, 1, rgbPins, 6, addrPins, clockPin, latchPin, oePin, false);

// Pattern state
enum Pattern { P_OFF, P_SOLID, P_CHECKER, P_RAINBOW, P_TEXT };
volatile Pattern currentPattern = P_OFF;
volatile uint8_t solidR = 0, solidG = 0, solidB = 0;
String textMessage = "";

// Animation parameters
unsigned long lastUpdate = 0;
const uint16_t frameDelayMs = 40; // ~25 FPS
uint16_t rainbowHue = 0;

// Helpers
uint16_t color565_from_rgb(uint8_t r, uint8_t g, uint8_t b) {
  return matrix.color565(r, g, b);
}

// Convert HSV (0..255) to RGB (0..255)
void hsvToRgb(uint8_t h, uint8_t s, uint8_t v, uint8_t &r, uint8_t &g, uint8_t &b) {
  uint8_t region = h / 43;
  uint8_t remainder = (h - (region * 43)) * 6;

  uint8_t p = (v * (255 - s)) >> 8;
  uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

  switch(region) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    default: r = v; g = p; b = q; break;
  }
}

// Pattern renderers
void drawOff() {
  matrix.fillScreen(0);
  matrix.show();
}

void drawSolid() {
  uint16_t c = color565_from_rgb(solidR, solidG, solidB);
  matrix.fillScreen(c);
  matrix.show();
}

void drawChecker() {
  matrix.fillScreen(0);
  for(int y=0; y<matrix.height(); y++) {
    for(int x=0; x<matrix.width(); x++) {
      bool odd = ((x/4) + (y/4)) & 1; // 4x4 blocks
      if(odd) matrix.drawPixel(x, y, matrix.color565(255, 255, 255));
      else matrix.drawPixel(x, y, matrix.color565(0, 0, 0));
    }
  }
  matrix.show();
}

void drawRainbow() {
  // Shift hue over time across the panel
  for(int y=0; y<matrix.height(); y++) {
    for(int x=0; x<matrix.width(); x++) {
      uint8_t h = (uint8_t)(rainbowHue + (x * 256 / matrix.width()) + (y * 8));
      uint8_t r,g,b;
      hsvToRgb(h, 255, 128, r, g, b);
      matrix.drawPixel(x, y, matrix.color565(r,g,b));
    }
  }
  rainbowHue++;
  matrix.show();
}

void drawText() {
  matrix.fillScreen(0);
  matrix.setTextWrap(true);
  matrix.setCursor(0, 0);
  matrix.setTextColor(matrix.color565(255,255,255));
  matrix.setTextSize(1);
  matrix.println(textMessage);
  matrix.show();
}

// Updated packet parser: set global pattern & parameters
void parsePacket(AsyncUDPPacket packet)
{
  // print debug
  Serial.print("UDP Packet From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(" Length:");
  Serial.println(packet.length());

  String msg = "";
  if(packet.length() > 0) {
    msg = String((const char*)packet.data());
    msg.trim();
  }

  Serial.print("Message: '");
  Serial.print(msg);
  Serial.println("'");

  // Simple command parsing (case-insensitive)
  msg.toUpperCase();
  if(msg == "OFF") {
    currentPattern = P_OFF;
  } else if(msg == "RAINBOW") {
    currentPattern = P_RAINBOW;
  } else if(msg == "CHECKER") {
    currentPattern = P_CHECKER;
  } else if(msg.startsWith("SOLID")) {
    // SOLID R G B  (0-255 each)
    int r=-1,g=-1,b=-1;
    // parse numbers
    sscanf(msg.c_str(), "SOLID %d %d %d", &r, &g, &b);
    if(r>=0 && g>=0 && b>=0) {
      solidR = (uint8_t)r; solidG = (uint8_t)g; solidB = (uint8_t)b;
      currentPattern = P_SOLID;
    }
  } else if(msg.startsWith("TEXT:")) {
    // Keep original case for text display
    // find position of ':' then copy original packet data
    const char *raw = (const char*)packet.data();
    const char *colon = strchr(raw, ':');
    if(colon) {
      textMessage = String(colon + 1);
      textMessage.trim();
      currentPattern = P_TEXT;
    }
  }

  // reply
  packet.printf("ACK: %u bytes", packet.length());
}

void setupLEDs() {
  // Initialize matrix
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    for(;;);
  }

  // start with OFF
  drawOff();
}

void setup() {
  Serial.begin(115200);
  setupUDP();
  setupLEDs();
}

void loop() {
  unsigned long now = millis();
  if(now - lastUpdate < frameDelayMs) return;
  lastUpdate = now;

  // Choose what to draw based on currentPattern
  switch(currentPattern) {
    case P_OFF: drawOff(); break;
    case P_SOLID: drawSolid(); break;
    case P_CHECKER: drawChecker(); break;
    case P_RAINBOW: drawRainbow(); break;
    case P_TEXT: drawText(); break;
    default: drawOff(); break;
  }

  // Optionally debug frame count occasionally
  static unsigned long lastFps = 0;
  if(now - lastFps > 1000) {
    Serial.print("Frame count: ");
    Serial.println(matrix.getFrameCount());
    lastFps = now;
  }
}