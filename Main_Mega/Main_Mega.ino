#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <DS1302.h>
#include <SoftwareSerial.h>
#include <SPFD5408_Adafruit_TFTLCD.h>

Servo In_servo;
Servo Out_servo;
int In_ir = A10, Out_ir = A11, in, out;
int p1 = 43, p2 = 41, p3 = 39, park1, park2, park3;
boolean in_status, bfor, pass;

#define SS_PIN 45
#define RST_PIN 53
RFID rfid(SS_PIN, RST_PIN);

DS1302 rtc(26, 24, 22);
Time t;

SoftwareSerial MegaSerial(A8, A9);
int park[3];
int InputA = A13, InputB = A14, A, B;
String tag, thisTime, thisUser, user = "Guest" , result, balance, cars;

int BLACK = 0x31C9, WHITE = 0xFFFF, RED = 0x9800, GREEN = 0x04C0, BLUE = 0x001F;
int CYAN = 0x07FF, MAGENTA = 0xF81F, YELLOW = 0xFFE0, GREY = 0x2108;
byte LCD_CS = A3, LCD_CD = A2, LCD_WR = A1, LCD_RD = A0, LCD_RESET = A4;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

////////////// FPGA //////////////
int S_rfid = A15, S_store = 35;
//////////////////////////////////

void setup()
{
  Serial.begin(9600);
  MegaSerial.begin(57600);
  SPI.begin();
  rfid.init();
  rtc.halt(false);
  rtc.writeProtect(false);
  In_servo.attach(44);
  Out_servo.attach(46);
  pinMode(InputA, INPUT);
  pinMode(InputB, INPUT);
  pinMode(In_ir, INPUT);
  pinMode(Out_ir, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);

  pinMode(S_store , OUTPUT);
  pinMode(S_rfid , OUTPUT);

  //   The following lines can be commented out to use the values already stored in the DS1302
  //   rtc.setDOW(MONDAY); // Set Day-of-Week to FRIDAY
  rtc.setTime(23, 59, 00); // Set the time to 12:00:00 (24hr format)
  //   rtc.setDate(23, 5, 2022); // Set the date to August 6th, 2010

  In_servo.write(0);
  Out_servo.write(0);

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
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

}

void loop()
{
  while (MegaSerial.available() > 0)
  {
    balance = MegaSerial.readString();
    //    Serial.println(balance.toInt());
    if (balance.toInt() >= 50) {
      tft.setCursor (20, 210);
      tft.print ("                        ");
      tft.setCursor (20, 210);
      tft.print ("Balance " + balance);
      tft.fillRect(318, 0, 2, 240, 0xBC9F);
      tft.fillRect(0, 0, 2, 240, 0xBC9F);
      tft.fillRect(0, 0, 320, 2, 0xBC9F);
      tft.fillRect(0, 238, 320, 2, 0xBC9F);
      pass = true;
      in_status = true;
    } else {
      tft.setCursor (20, 210);
      tft.print ("Inefficient balance         ");
      tft.fillRect(318, 0, 2, 240, 0xBC9F);
      tft.fillRect(0, 0, 2, 240, 0xBC9F);
      tft.fillRect(0, 0, 320, 2, 0xBC9F);
      tft.fillRect(0, 238, 320, 2, 0xBC9F);
      delay(3000);
      bfor = 0;
      tft.setCursor (20, 170);
      tft.print ("   ");
      tft.setCursor (39, 170);
      tft.print ("Please tap your card");
      tft.setCursor (20, 210);
      tft.print ("                        ");
      pass = false;
      in_status = false;
    }
  }

  RFID();
  Door();
  Parking();

  if (in_status == false) {
    Decoder();
    Clock();
  }
}

void Decoder() {
  A = digitalRead(InputA);
  B = digitalRead(InputB);

  if (A == 0 && B == 0)
    cars = "0";
  else if (A == 0 && B == 1)
    cars = "1";
  else if (A == 1 && B == 0)
    cars = "2";
  else if (A == 1 && B == 1)
    cars = "3";

  tft.setCursor (20, 210);
  tft.print ("Total car: " + cars);
//  Serial.println(cars);
}
