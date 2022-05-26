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

        if (tag == "83173155167")
          user = "DEW";
        if (tag == "6620217313")
          user = "FON";
        if (tag == "21119012328")
          user = "SEK";

        Serial.print("UID = ");
        Serial.print(tag);
        Serial.println(" " + user);

        result += user;
        result += ",";
        result += park[0];
        result += ",";
        result += park[1];
        result += ",";
        result += park[2];
        MegaSerial.print(result);
        result = "";
        in_status = true;

        thisUser += "WELCOME " + user + "            ";
        tft.setCursor (20, 170);
        tft.print (thisUser);
        thisUser = "";

      } else {
        Serial.print(".");
      }
    }
  }
  rfid.halt();
}

void Parking() {
  park1 = digitalRead(p1);
  park2 = digitalRead(p2);
  park3 = digitalRead(p3);

  if ((park[0] != park1) || (park[1] != park2) || (park[2] != park3)) {
    park[0] = park1;
    park[1] = park2;
    park[2] = park3;
    result += "update";
    result += ",";
    result += park[0];
    result += ",";
    result += park[1];
    result += ",";
    result += park[2];
    MegaSerial.print(result);
    result = "";
  }

  park[0] = park1;
  park[1] = park2;
  park[2] = park3;

  if (park1 == true)
    tft.fillRect(2, 2, 104, 120, GREEN);
  else
    tft.fillRect(2, 2, 104, 120, RED);
  if (park2 == true)
    tft.fillRect(107, 2, 105, 120, GREEN);
  else
    tft.fillRect(107, 2, 105, 120, RED);
  if (park3 == true)
    tft.fillRect(214, 2, 104, 120, GREEN);
  else
    tft.fillRect(214, 2, 104, 120, RED);
}

void Clock() {
  t = rtc.getTime();
  char *result = malloc(5);

  sprintf(result, "%02d", t.hour);
  thisTime += result;
  thisTime += ":";
  sprintf(result, "%02d", t.min);
  thisTime += result;
  thisTime += ":";
  sprintf(result, "%02d", t.sec);
  thisTime += result;

  //  Serial.print("Time = ");
  //  Serial.println(thisTime);

  tft.setCursor (210, 210);
  tft.print (thisTime);
  //  delay (200);
  thisTime = "";
  if ( t.hour == 00 && t.min == 00 && t.sec == 00) {
    digitalWrite(S_store , HIGH);
    delay(50);
    digitalWrite(S_store , LOW);
    delay(100);
    digitalWrite(S_reset , HIGH);
    delay(50);
    digitalWrite(S_reset , LOW);
  }
}

void Door() {
  in = digitalRead(In_ir);
  out = digitalRead(Out_ir);

  if (in_status == true && in == false && pass == true) {
    In_servo.write(90);
    bfor = 1;
  } else if (in_status == true && in == true && bfor == 1) {
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
    In_servo.write(0);
  }
  if (out == false) {
    Out_servo.write(90);
    delay(3000);
    Out_servo.write(0);
  }
}
