#define TFT_BLACK   0x31C9
#define TFT_BLUE    0x001F
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF
#define TFT_GREY    0x5AEB

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120; // Saved H, M, S x & y coords
int16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0, x00 = 0, yy00 = 0;
uint32_t targetTime = 0;                    // for next 1 second timeout
uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
uint8_t hh, mm, ss;
boolean initial = 1;
char d;

void Display_clock() {
  t = rtc.getTime();
  hh = t.hour;
  mm = t.min;
  ss = t.sec;

  // Pre-compute hand degrees, x & y coords for a fast screen update
  sdeg = ss * 6;                     // 0-59 -> 0-354
  mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds, but these increments are not used
  hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds, but these increments are not used
  hx = cos((hdeg - 90) * 0.0174532925);
  hy = sin((hdeg - 90) * 0.0174532925);
  mx = cos((mdeg - 90) * 0.0174532925);
  my = sin((mdeg - 90) * 0.0174532925);
  sx = cos((sdeg - 90) * 0.0174532925);
  sy = sin((sdeg - 90) * 0.0174532925);

  if (ss == 0 || initial) {
    initial = 0;
    // Erase hour and minute hand positions every minute
    tft.drawLine(ohx, ohy, xpos, 121 - dec, TFT_BLACK);
    ohx = hx * 62 + xpos + 1;
    ohy = hy * 62 + 121 - dec;
    tft.drawLine(omx, omy, xpos, 121 - dec, TFT_BLACK);
    omx = mx * 84 + xpos;
    omy = my * 84 + 121 - dec;
  }

  // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
  tft.drawLine(osx, osy, xpos, 121 - dec, TFT_BLACK);
  osx = sx * 90 + xpos + 1;
  osy = sy * 90 + 121 - dec;
  tft.drawLine(osx, osy, xpos, 121 - dec, TFT_RED);
  tft.drawLine(ohx, ohy, xpos, 121 - dec, TFT_CYAN);
  tft.drawLine(omx, omy, xpos, 121 - dec, TFT_WHITE);
  tft.drawLine(osx, osy, xpos, 121 - dec, TFT_RED);
  tft.fillCircle(xpos, 121 - dec, 3, TFT_RED);

  //  tft.setCursor(xpos-40, 45);
  //  tft.setTextSize(2);
  //  tft.print("CLOCK");

  // Draw MINI clock face "SECOND"
  tft.drawCircle(xpos, 155 - dec, 20, TFT_YELLOW);
  tft.drawCircle(xpos, 155 - dec, 18, TFT_BLUE);
  tft.drawCircle(xpos, 155 - dec, 17, TFT_CYAN);
  tft.drawCircle(xpos, 155 - dec, 16, TFT_CYAN);
  tft.fillRect(xpos - 10, 149 - dec, 22, 15, TFT_BLACK); //erase
  if (ss < 10) {
    tft.setCursor(xpos - 10, 149 - dec); tft.setTextSize(2);
    tft.print('0'); tft.setCursor(xpos + 2, 149 - dec);
  }
  else {
    tft.setCursor(xpos - 10, 149 - dec);
  }
  tft.setTextSize(2);
  tft.print(ss);

  // Draw MINI clock face "Minutes"
  tft.drawCircle(xpos + 35, 117 - dec, 20, TFT_YELLOW);
  tft.drawCircle(xpos + 35, 117 - dec, 18, TFT_BLUE);
  tft.drawCircle(xpos + 35, 117 - dec, 17, TFT_CYAN);
  tft.drawCircle(xpos + 35, 117 - dec, 16, TFT_CYAN);
  tft.fillRect(xpos + 25, 111 - dec, 22, 15, TFT_BLACK); //erase
  if (mm < 10) {
    tft.setCursor(xpos + 25, 111 - dec); tft.setTextSize(2);
    tft.print('0'); tft.setCursor(xpos + 37, 111 - dec);
  }
  else {
    tft.setCursor(xpos + 25, 111 - dec);
  }
  tft.println(mm);

  // Draw MINI clock face "Hour"
  tft.drawCircle(xpos - 35, 117 - dec, 20, TFT_YELLOW);
  tft.drawCircle(xpos - 35, 117 - dec, 18, TFT_BLUE);
  tft.drawCircle(xpos - 35, 117 - dec, 17, TFT_CYAN);
  tft.drawCircle(xpos - 35, 117 - dec, 16, TFT_CYAN);
  tft.fillRect(xpos - 45, 111 - dec, 22, 15, TFT_BLACK); //erase
  if (hh < 10) {
    tft.setCursor(xpos - 45, 111 - dec); tft.setTextSize(2);
    tft.print('0'); tft.setCursor(xpos - 33, 111 - dec);
  }
  else {
    tft.setCursor(xpos - 45, 111 - dec);
  }
  tft.setTextSize(2);
  tft.print(hh);
  //tft.setCursor(xpos-65, 111);
  //tft.println(':');

  if (hh >= 0 && hh < 12) d = 'A'; else {
    d = 'P';
  }
  tft.drawRoundRect(xpos - 14, 72 - dec, 29, 21, 5, TFT_CYAN);
  tft.fillRect(xpos - 11, 75 - dec, 23, 15, TFT_BLACK); //erase
  tft.setCursor(xpos - 11, 75 - dec);
  tft.setTextSize(2);
  tft.print(d);
  tft.println('M');

}
