// Blynk template details (Add your details correctly)
#define BLYNK_TEMPLATE_ID "TMPL3co5SVbNX"
#define BLYNK_TEMPLATE_NAME "Smart Home Automation"
#define BLYNK_AUTH_TOKEN "xlRp2WpR8VFIjQJVq_8hiTsIBEmxNwTE"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <mcp_can.h>

// WiFi credentials
char ssid[] = "Butterfly";
char pass[] = "Butterflyy";

// CAN setup
#define CAN_CS 5
MCP_CAN CAN(CAN_CS);

int servoPosition = 90; // Default servo position

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize CAN Bus
  if (CAN.begin(MCP_ANY, 500000, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Bus Initialized");
  } else {
    Serial.println("CAN Bus Initialization Failed!");
    while (1);
  }
  CAN.setMode(MCP_NORMAL);
}

// Slider widget control (V0 in Blynk App)
BLYNK_WRITE(V0) {
  int servoPosition = param.asInt(); // Get slider value from Blynk
  Serial.print("Servo position to send: ");
  Serial.println(servoPosition);

  // Send servo position via CAN bus
  byte data[1] = {servoPosition};
  if (CAN.sendMsgBuf(0x10, 0, 1, data) == CAN_OK) {
    Serial.println("Servo position sent via CAN Bus");
  } else {
    Serial.println("Failed to send via CAN Bus");
  }
}

void loop() {
  Blynk.run();
}