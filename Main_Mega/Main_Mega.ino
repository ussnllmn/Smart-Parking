#include <SPI.h>
#include <RFID.h>
#include <DS1302.h>
#include <SoftwareSerial.h>

#define SS_PIN 45
#define RST_PIN 53
RFID rfid(SS_PIN, RST_PIN);

DS1302 rtc(26, 24, 22);
Time t;

SoftwareSerial espSerial(46, 44);

int serNum0, serNum1, serNum2, serNum3, serNum4;
String tag;

void setup()
{
  Serial.begin(115200);
  espSerial.begin(115200);
  SPI.begin();
  rfid.init();
  rtc.halt(false);
  rtc.writeProtect(false);

  // The following lines can be commented out to use the values already stored in the DS1302
  // rtc.setDOW(MONDAY); // Set Day-of-Week to FRIDAY
  // rtc.setTime(19,55, 10); // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(23, 5, 2022); // Set the date to August 6th, 2010
}

void loop()
{
  RFID();

}
