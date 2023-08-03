#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <Servo.h>

#define SERVO_PIN  6
#define SDA_PIN A4
#define SCL_PIN A5  

Servo servo;
int angle = 0; // the current angle of the servo motor

int GLED = 8;
int RLED = 7;

PN532_I2C pn532_i2c(Wire);
PN532 nfc(pn532_i2c);

uint8_t success;
uint8_t uid[] = { 0, 0, 0, 0 };
uint8_t uidLength;

uint8_t Unlock[] = {
  0x00, /* CLA */
  0xA4, /* INS */
  0x04, /* P1  */
  0x00, /* P2  */
  0x07, /* Length of AID  */
  0xF0, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* AID  */
  0x00  /* Le  */
};

uint8_t Lock[] = {
  0x00, /* CLA */
  0xA4, /* INS */
  0x04, /* P1  */
  0x00, /* P2  */
  0x07, /* Length of AID  */
  0xF0, 0x09, 0x8, 0x07, 0x06, 0x05, 0x04, /* AID  */
  0x00  /* Le  */
};

uint8_t UnlockResponse[] = {69, 54, 49, 54, 32, 85, 110, 108, 111, 99, 107};
uint8_t LockResponse[] = {69, 54, 49, 54, 32, 76, 111, 99, 107};

void setup(void) {
  Serial.begin(115200);

  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, LOW);



  servo.attach(SERVO_PIN);
  servo.write(angle); // rotate servo motor to 0°

  nfc.begin(); //begin the commmunication

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

void loop() {
  Serial.println("Listening...");
  Serial.println("Something's there...");


    Serial.println("Waitig to Unlock");
    
    bool toUnlock = false;
    
    while(!toUnlock) {
      if (nfc.inListPassiveTarget()) {

        uint8_t responseUnlock[255];
        uint8_t responseLengthUnlock = sizeof(responseUnlock);
        
        bool successUnlock = nfc.inDataExchange(Unlock, sizeof(Unlock), responseUnlock, &responseLengthUnlock);
      
        int conditionAPDULength = 0;
        for (int i = 0; i < responseLengthUnlock; i++) {
          if (responseUnlock[i] == UnlockResponse[i]) {
            conditionAPDULength = conditionAPDULength + 1;
          }
        }
    
        if (conditionAPDULength == responseLengthUnlock) {
          Serial.println("Unlocked");
          
          // change angle of the servo motor
          angle = 0;     
    
          // control servo motor according to the angle
          servo.write(angle);
          Serial.print("Angle: ");
          Serial.println(angle);
          
          digitalWrite(GLED, HIGH);
          digitalWrite(RLED, LOW);
  
          toUnlock = true;
            
        } else {
          
          digitalWrite(GLED, LOW);
          digitalWrite(RLED, HIGH);
          
           toUnlock = false;
        }
      }
    }
    
    

    delay(2000);

    //++++++++++++++++++++++++++++++++++++++++++++++++++
    //Lock

    Serial.println("Waiting to Lock");

    bool toLock = false;
    
    while (!toLock) {
      if (nfc.inListPassiveTarget()) {
         uint8_t responseLock[255];
         uint8_t responseLengthLock = sizeof(responseLock);
        
         bool successLock = nfc.inDataExchange(Lock, sizeof(Lock), responseLock, &responseLengthLock);
  
         int conditionAPDULength = 0;
  
         for (int i = 0; i < responseLengthLock; i++){
            if (responseLock[i] == LockResponse[i]) {
              conditionAPDULength = conditionAPDULength + 1;
            }
         }
  
         if (conditionAPDULength == responseLengthLock) {
           Serial.println("Locked");
          
           // change angle of the servo motor
           angle = 90;
        
           // control servo motor according to the angle
           servo.write(angle);
           Serial.print("Angle: ");
           Serial.println(angle);
            
           digitalWrite(GLED, HIGH);
           digitalWrite(RLED, LOW);
           delay(1000);
           digitalWrite(GLED, HIGH);
           digitalWrite(RLED, HIGH);
           delay(1000);
           digitalWrite(GLED, HIGH);
           digitalWrite(RLED, LOW);
           delay(1000);
           digitalWrite(GLED, LOW);
           digitalWrite(RLED, HIGH);
    
           toLock = true;
           
           } else {
            digitalWrite(GLED, LOW);
            digitalWrite(RLED, HIGH);

            toLock = false;
        }
         
      }    
    }
}
