#include <SPI.h>
#include <RFID.h>

#define SS_PIN D2
#define RST_PIN D1
RFID rfid(SS_PIN, RST_PIN);

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

String tag;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      /* With a new cardnumber, show it. */
      for (byte i = 0; i < 4; i++) {
        tag += rfid.serNum[i];
      }
      Serial.print("UID = ");
      Serial.println(tag);
      tag = "";
    }
  }
  rfid.halt();
}
