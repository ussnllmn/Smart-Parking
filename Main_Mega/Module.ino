int serNum0, serNum1, serNum2, serNum3, serNum4;
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

        if (tag == "83173155167") {
          user = "DEW";
          park[0] = 1;
        }
        if (tag == "6620217313") {
          user = "FON";
          park[1] = 1;
        }
        if (tag == "21119012328") {
          user = "SEK";
          park[2] = 1;
        }

        Serial.print("UID = ");
        Serial.println(tag);

        Serial.println(user);

        result += user;
        result += ",";
        result += park[0];
        result += ",";
        result += park[1];
        result += ",";
        result += park[2];
        
        in_status = true;
        
        MegaSerial.print(result);
        result = "";
        thisUser += "WELCOME " + user + "            ";
        tft.setCursor (20, 170);
        tft.print (thisUser);
        thisUser = "";

//        tft.setCursor (20, 210);
//        tft.print (tag + "  ");

      } else {
        Serial.print(".");
      }
    }
  }
  rfid.halt();
}

void Clock() {
  t = rtc.getTime();
  thisTime += t.hour;
  thisTime += ":";
  thisTime += t.min;
  thisTime += ":";
  thisTime += t.sec;
  //  Serial.print("Time = ");
  //  Serial.println(thisTime);
  tft.setCursor (210, 210);
  tft.print (thisTime);
  delay (200);
  thisTime = "";
}
