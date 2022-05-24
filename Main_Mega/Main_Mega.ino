#include <SPI.h>
#include <RFID.h>
#include <DS1302.h>
#include <SoftwareSerial.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

#define SS_PIN 45
#define RST_PIN 53
RFID rfid(SS_PIN, RST_PIN);

DS1302 rtc(26, 24, 22);
Time t;

SoftwareSerial MegaSerial(A8, A9); 
int park[3];
int InputA = 14, InputB = 15, A, B;
String tag, thisTime, thisUser, cars, user , result;

int BLACK = 0x31C9, WHITE = 0xFFFF, RED = 0x9800, GREEN = 0x04C0, BLUE = 0x001F;
int CYAN = 0x07FF, MAGENTA = 0xF81F, YELLOW = 0xFFE0, GREY = 0x2108;
byte LCD_CS = A3, LCD_CD = A2, LCD_WR = A1, LCD_RD = A0, LCD_RESET = A4;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup()
{
  Serial.begin(9600);
  MegaSerial.begin(57600);
  SPI.begin();
  rfid.init();
  rtc.halt(false);
  rtc.writeProtect(false);
  pinMode(InputA, OUTPUT);
  pinMode(InputB, OUTPUT);
  // The following lines can be commented out to use the values already stored in the DS1302
  // rtc.setDOW(MONDAY); // Set Day-of-Week to FRIDAY
  // rtc.setTime(19,55, 10); // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(23, 5, 2022); // Set the date to August 6th, 2010

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(3);
  tft.fillScreen(0x31C9);
  // Border screen
  tft.fillRect(318, 0, 2, 240, 0xBC9F);
  tft.fillRect(0, 0, 2, 240, 0xBC9F);
  tft.fillRect(0, 0, 320, 2, 0xBC9F);
  tft.fillRect(0, 238, 320, 2, 0xBC9F);
  // Border parking
  tft.fillRect(105, 2, 2, 155, 0xBC9F);
  tft.fillRect(212, 2, 2, 155, 0xBC9F);
  tft.fillRect(0, 155, 320, 2, 0xBC9F);

  tft.setTextSize (2);
  tft.setTextColor (WHITE, 0x31C9);

  tft.setCursor (20, 131);
  tft.print ("Park 1");
  tft.setCursor (125, 131);
  tft.print ("Park 2");
  tft.setCursor (231, 131);
  tft.print ("Park 3");

  tft.setCursor (39, 170);
  tft.print ("Please tap your card");

  //  // Draw clock face
  //  tft.drawCircle(xpos, 120 - dec, 125 - dec, 0xFFE0);
  //  tft.fillCircle(xpos, 120 - dec, 118 - dec, 0x001F); //warna lingkaran luar
  //  tft.fillCircle(xpos, 120 - dec, 110 - dec, 0x31C9); //warna jam bagian dalam
  //  for (int a = 95; a < 104; a++)
  //    tft.drawCircle(xpos, 120 - dec, a - dec, 0xFFFF);
}

void loop()
{
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
  RFID();
  if (park[0] == 0)
    tft.fillRect(2, 2, 104, 120, GREEN);
  else
    tft.fillRect(2, 2, 104, 120, RED);
  if (park[1] == 0)
    tft.fillRect(107, 2, 105, 120, GREEN);
  else
    tft.fillRect(107, 2, 105, 120, RED);
  if (park[2] == 0)
    tft.fillRect(214, 2, 104, 120, GREEN);
  else
    tft.fillRect(214, 2, 104, 120, RED);

  Clock();
}

void Decoder() {
  A = digitalRead(InputA);
  B = digitalRead(InputB);

  if (A == 0 && B == 0)
    cars = "0,0,0";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  else if (A == 0 && B == 1)
    cars = "0,0,1";
  Serial.println(cars);
}
