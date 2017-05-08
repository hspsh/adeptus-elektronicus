#include <MFRC522.h>
#include <SPI.h>
/*
 * Projekt pokazowy wz2 stworzony na potrzeby czwartego spotkania adeptus elektronicus. Więcej szczegulow i
 *  opis znajduje sie w prezentacji "Spotkanie 4 - Wielkie otwarcie - zamki elektromagnetyczne".
 */
#define SAD 10
#define RST 9
#define LOCK_PIN 4
#define LED_PIN 13
#define ALLOW_PIN 8
#define OPEN_PIN 3

MFRC522 nfc(SAD, RST);

void setup() {

  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(ALLOW_PIN, INPUT);
  digitalWrite(ALLOW_PIN, HIGH);
  pinMode(OPEN_PIN, INPUT);
  digitalWrite(OPEN_PIN, HIGH);

  SPI.begin();
  // Read a fast as possible. There is a limit for how long we are
  // allowed to read from the tags.
  Serial.begin(115200);

  Serial.println("Looking for MFRC522.");
  nfc.begin();

  // Get the firmware version of the RFID chip
  byte version = nfc.getFirmwareVersion();
  if (! version) {
    Serial.print("Didn't find MFRC522 board.");
  } else {
    Serial.print("Found chip MFRC522 ");
    Serial.print("Firmware ver. 0x");
    Serial.print(version, HEX);
    Serial.println(".");
  }
}
byte keyA[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
byte keyB[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
byte authorizedSerial[] = {0xFF, 0xFF, 0xFF, 0xFF};


bool tagAllowed = false;

void openTheDoors() {
  digitalWrite(LOCK_PIN, HIGH);
  delay(3000);
  digitalWrite(LOCK_PIN, LOW);
}

void attemptUnlock(byte serial[5]){
  bool tagAllowed = true;
    for (int i = 0; i < 4; i++) {
      Serial.print(serial[i], HEX);
      Serial.print(", ");
      if (serial[i] != authorizedSerial[i]) {
        tagAllowed = false;
      }
    }
    if (tagAllowed) {
      openTheDoors();
    }
}

void saveId(byte serial[5]){
  Serial.println("The serial nb of the tag is:");
  for (int i = 0; i < 4; i++) {
    Serial.print(serial[i], HEX);
    authorizedSerial[i] = serial[i];
    Serial.print(", ");
  }
}

void loop() {
  byte status;
  byte data[MAX_LEN];
  int i, j, pos;
  byte serial[5];

  if(!digitalRead(OPEN_PIN)){
    openTheDoors();
  }
  // Send a general request out into the aether. If there is a tag in
  // the area it will respond and the status will be MI_OK.
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    Serial.println("Tag detected.");
    Serial.print("Type: ");
    Serial.print(data[0], HEX);
    Serial.print(", ");
    Serial.println(data[1], HEX);

    // calculate the anti-collision value for the currently detected
    // tag and write the serial into the data array.
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    Serial.println("The serial nb of the tag is:");
    if(!digitalRead(ALLOW_PIN)){
      saveId(serial);
    } else {
      attemptUnlock(serial); 
    }
    // Stop the tag and get ready for reading a new tag.
    nfc.haltTag();
  }
}
