#include <SPI.h>
#include <mcp_can.h>

// CAN setup
#define CAN_CS 53 // Chip select pin for the CAN module
MCP_CAN CAN(CAN_CS);

void setup() {
  Serial.begin(115200);
  
  // Initialize CAN bus
  Serial.println("Initializing CAN bus...");
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("CAN Bus Initialized on Mega");
  } else {
    Serial.println("CAN Bus Init Failed. Check wiring and module configuration.");
    while (1); // Stop if CAN initialization fails
  }
  
  // Set CAN to normal mode
  CAN.setMode(MCP_NORMAL);
  Serial.println("CAN Bus set to Normal Mode.");
}

void loop() {
  long unsigned int canId;
  unsigned char len = 0;
  unsigned char buf[8];

  // Check if data is received
  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    CAN.readMsgBuf(&canId, &len, buf); // Read CAN message

    // Print received data
    Serial.print("Message Received: CAN ID = 0x");
    Serial.print(canId, HEX);
    Serial.print(", Data = ");
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
