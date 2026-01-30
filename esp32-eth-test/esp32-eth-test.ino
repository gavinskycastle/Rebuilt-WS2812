#if !( defined(ESP32) )
  #error This code is designed for (SP32_S2/3, ESP32_C3 + W5500) to run on ESP32 platform! Please check your Tools->Board setting.
#endif

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

//////////////////////////////////////////////////////////

// Optional values to override default settings
// Don't change unless you know what you're doing
//#define ETH_SPI_HOST        SPI3_HOST
//#define SPI_CLOCK_MHZ       25

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            4

//#define MISO_GPIO           13
//#define MOSI_GPIO           11
//#define SCK_GPIO            12
//#define CS_GPIO             10

//////////////////////////////////////////////////////////

#include <WebServer_ESP32_SC_W5500.h>

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
IPAddress myIP(10, 42, 1, 12);
IPAddress myGW(10, 42, 1, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

// Remote server that will send UDP packets to this ESP32
// (source server on 10.42.1.2:25000)
IPAddress remoteIP(10, 42, 1, 2);

unsigned int localPort    = 25000;             // local port to listen for UDP packets

const int UDP_TIMEOUT     = 2000;     // timeout in milliseconds to wait for an UDP packet to arrive

byte packetBuffer[NTP_PACKET_SIZE];          // buffer to hold incoming packet
byte ReplyBuffer[] = "ACK";      // a string to send back

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B  21  // GPIO ESP32-S3 pin that connects to WS2812B
#define NUM_PIXELS  256  // The number of LEDs (pixels) on WS2812B

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

// Pattern state
enum Pattern { P_DISABLED, P_IDLE, P_DRIVING, P_INTAKING, P_SHOOTING, P_CLIMBING };
volatile Pattern currentPattern = P_DISABLED;

// Updated packet parser: set global pattern & parameters
void parsePacket(AsyncUDPPacket packet)
{
  // Simple command parsing (case-insensitive)
  msg.toLowerCase();
  if(msg == "disabled") {
    currentPattern = P_DISABLED;
  } else if(msg == "idle") {
    currentPattern = P_IDLE;
  } else if(msg == "driving") {
    currentPattern = P_DRIVING;
  } else if(msg == "intaking") {
    currentPattern = P_INTAKING;
  } else if(msg == "shooting") {
    currentPattern = P_SHOOTING;
  } else if(msg == "climbing") {
    currentPattern = P_CLIMBING;
  }
}

void drawDisabled() {
    Serial.println("Drawing DISABLED pattern");
    WS2812B.clear();
    // Fill with red color to indicate disabled
    WS2812B.fill(WS2812B.Color(255, 0, 0));
    WS2812B.show();
}

void drawIdle() {
    Serial.println("Drawing IDLE pattern");
    WS2812B.clear();
    // Fill with white color to indicate idle
    WS2812B.fill(WS2812B.Color(255, 255, 255));
    WS2812B.show();
}

void drawDriving() {
    Serial.println("Drawing DRIVING pattern");
    WS2812B.clear();
    // Fill with green color to indicate driving
    WS2812B.fill(WS2812B.Color(0, 255, 0));
    WS2812B.show();
}

void drawIntaking() {
    Serial.println("Drawing INTAKING pattern");
    WS2812B.clear();
    // Fill with orange color to indicate intaking
    WS2812B.fill(WS2812B.Color(255, 165, 0));
    WS2812B.show();
}

void drawShooting() {
    Serial.println("Drawing SHOOTING pattern");
    WS2812B.clear();
    // Fill with blue color to indicate shooting
    WS2812B.fill(WS2812B.Color(0, 0, 255));
    WS2812B.show();
}

void drawClimbing() {
    Serial.println("Drawing CLIMBING pattern");
    WS2812B.clear();
    // Fill with purple color to indicate climbing
    WS2812B.fill(WS2812B.Color(128, 0, 128));
    WS2812B.show();
}

void setupLEDs() {
  // Initialize matrix
  WS2812B.begin(); // INITIALIZE WS2812B strip object (REQUIRED)
  WS2812B.setBrightness(30); // a value from 0 to 255

  // start with DISABLED
  drawDisabled();
}

void setup() {
  Serial.begin(115200);

  while (!Serial && (millis() < 5000));

  delay(500);

  Serial.print(F("\nStart UDPSendReceive on "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_ESP32_SC_W5500_VERSION);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("SPI_HOST:"), ETH_SPI_HOST);
  ET_LOGWARN1(F("MOSI:"), MOSI_GPIO);
  ET_LOGWARN1(F("MISO:"), MISO_GPIO);
  ET_LOGWARN1(F("SCK:"),  SCK_GPIO);
  ET_LOGWARN1(F("CS:"),   CS_GPIO);
  ET_LOGWARN1(F("INT:"),  INT_GPIO);
  ET_LOGWARN1(F("SPI Clock (MHz):"), SPI_CLOCK_MHZ);
  ET_LOGWARN(F("========================="));

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_W5500_onEvent();

  // start the ethernet connection and the server:
  uint16_t index = millis() % NUMBER_OF_MAC;

  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W5500_Mac = W5500_Default_Mac);
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[index] );
  
  bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_W5500_waitForConnect();

  ///////////////////////////////////

  Serial.println(F("\nStarting connection to server..."));
  // if you get a connection, report back via serial:
  Udp.begin(localPort);

  Serial.print(F("Listening on port "));
  Serial.println(localPort);

  setupLEDs();
}

void loop() {
  // wait for a reply for UDP_TIMEOUT milliseconds
  unsigned long startMs = millis();

  while (!Udp.available() && (millis() - startMs) < UDP_TIMEOUT) {}

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    Serial.print(F("UDP Packet received, size "));
    Serial.println(packetSize);
    Serial.print(F("From "));
  IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(F(", port "));
    Serial.println(Udp.remotePort());

    // We've received a packet, read the data from it into the buffer
    Udp.read(packetBuffer, NTP_PACKET_SIZE);
    // Optionally send an ACK back to the sender (useful for testing)
    // This replies to the actual sender's IP/port so it will work whether
    // the packet originated from 10.42.1.2:25000 or another source.
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer, sizeof(ReplyBuffer) - 1); // don't send trailing null
    Udp.endPacket();
    Serial.println(F("Sent ACK reply"));
  }
  
  // Change the current pattern based on received packet
  String msg = String((char*)packetBuffer).substring(0, packetSize);
   parsePacket(msg);

  // Choose what to draw based on currentPattern
  switch(currentPattern) {
    case P_DISABLED: drawDisabled(); break;
    case P_IDLE: drawIdle(); break;
    case P_DRIVING: drawDriving(); break;
    case P_INTAKING: drawIntaking(); break;
    case P_SHOOTING: drawShooting(); break;
    case P_CLIMBING: drawClimbing(); break;
  }
}