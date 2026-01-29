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
enum Pattern { P_DISABLED, P_IDLE, P_DRIVING, P_INTAKING, P_SHOOTING, P_CLIMBING };
volatile Pattern currentPattern = P_DISABLED;

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

  // reply
  packet.printf("ACK: %u bytes", packet.length());
}

void drawDisabled() {
    Serial.println("Drawing DISABLED pattern");
}

void drawIdle() {
    Serial.println("Drawing IDLE pattern");
}

void drawDriving() {
    Serial.println("Drawing DRIVING pattern");
}

void drawIntaking() {
    Serial.println("Drawing INTAKING pattern");
}

void drawShooting() {
    Serial.println("Drawing SHOOTING pattern");
}

void drawClimbing() {
    Serial.println("Drawing CLIMBING pattern");
}

void setupLEDs() {
  // Initialize matrix
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    for(;;);
  }

  // start with DISABLED
  drawDisabled();
}

void setup() {
  Serial.begin(115200);
  setupUDP();
  setupLEDs();
}

void loop() {
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