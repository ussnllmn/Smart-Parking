void RFID() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      if (rfid.serNum[0] != serNum0
          && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2
          && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4
         ) {
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];
        tag = "";
        for (byte i = 0; i < 4; i++) {
          tag += rfid.serNum[i];
        }
        Serial.print("UID = ");
        Serial.println(tag);
        espSerial.println(tag);
      } else {
        Serial.print(".");
      }
    }
  }
  rfid.halt();
}

void Clock() {
  t = rtc.getTime();

  Serial.print("Today = ");
  Serial.print(t.date, DEC);
  Serial.print(" ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" ");
  Serial.println(t.year, DEC);

  Serial.print("Time = ");
  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.println(t.sec, DEC);
  Serial.println("- - - - - - - - - - -");
  delay (1000);
}
