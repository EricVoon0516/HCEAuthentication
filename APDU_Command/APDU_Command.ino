#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>

#define SDA_PIN A4
#define SCL_PIN A5

PN532_I2C pn532_i2c(Wire);
PN532 nfc(pn532_i2c);

uint8_t success;
uint8_t uid[] = { 0, 0, 0, 0 };
uint8_t uidLength;

uint8_t selectApdu[] = {
  0x00, /* CLA */
  0xA4, /* INS */
  0x04, /* P1  */
  0x00, /* P2  */
  0x07, /* Length of AID  */
  0xF0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* AID  */
  0x00  /* Le  */
};

uint8_t response[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; //Hello, not using in this situation


void setup(void) {
  Serial.begin(115200);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();

  nfc.begin();
}

void loop(void) {
  Serial.println("Listening...");
  if (nfc.inListPassiveTarget()) {
    Serial.println("Something's there...");

    uint8_t response[255];
    uint8_t responseLength = sizeof(response);

    bool success = nfc.inDataExchange(Lock, sizeof(Lock), response, &responseLength);

    Serial.print("Response Length: ");
    Serial.println(responseLength);

    Serial.print("Response: ");
    for (int i = 0; i < responseLength; i++) {
      Serial.print(response[i]);
      Serial.print(" ");
    }
    Serial.println();

    if (success) {
      Serial.println("Sent");
      nfc.PrintHexChar(response, responseLength);

    } else {
      Serial.println("Not sent");
    }

    int n = 0;
    for (int i = 0; i < responseLength; i++) {
      if (response[i] == LockResponse[i]) {
        n = n + 1;
        Serial.print(i);
        Serial.print(" ");
        Serial.print(response[i]);
        Serial.print(" ");
        Serial.print(LockResponse[i]);
        Serial.print(" ");
        Serial.print(n);
        Serial.println(" ");
      }

      Serial.print("ComAPDU");
      Serial.print(" ");
      Serial.print(response[i]);
      Serial.println(" ");
    }

  }


  Serial.print("n: ");
  Serial.println(n);
}
