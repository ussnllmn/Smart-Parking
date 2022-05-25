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
        
        Send_to_node();
        in_status = true;

        digitalWrite(S_rfid , HIGH);
        delay(100);
        digitalWrite(S_rfid , LOW);

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
void Send_to_node() {
  result += user;
  result += ",";
  result += park[0];
  result += ",";
  result += park[1];
  result += ",";
  result += park[2];
  MegaSerial.print(result);
  result = "";
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

void Door() {
  in = digitalRead(In_ir);
  out = digitalRead(Out_ir);
  //  Serial.println(out);
  if (in_status == true && in == false) {
    In_servo.write(90);
    bfor = 1;
  } else if (in_status == true && in == true && bfor == 1) {
    delay(5000);
    bfor = 0;
    in_status = false;
    In_servo.write(0);
  }
  if (out == false) {
    Out_servo.write(90);
    delay(5000);
    Out_servo.write(0);
  }
}
