#include <SPI.h>
#include <RFID.h>

#define SS_PIN D2
#define RST_PIN D1

RFID rfid(SS_PIN, RST_PIN);

int buzzPin = D4;

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

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
      if (rfid.serNum[0] != serNum0
          && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2
          && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4
         ) {
        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        //Serial.println(" ");
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");
        //buzzer
        analogWrite(3, 20);
        delay(500);
        analogWrite(3, 0);
      } else {
        /* If we have the same ID, just write a dot. */
        Serial.print(".");
      }
    }
  }

  rfid.halt();
}
