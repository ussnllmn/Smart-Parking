#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

constexpr uint8_t RST_PIN = D1;
constexpr uint8_t SS_PIN = D2;
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

String tag = "";

// Network credentials
const char* ssid     = "Mero Asebi";
const char* password = "james159";
WiFiServer server(80);

/////////////// Timer ///////////////
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
/////////////////////////////////////

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (tag == "") {
    if ( ! rfid.PICC_IsNewCardPresent()){
      Serial.println("not new");      
      return;}
    if (rfid.PICC_ReadCardSerial()) {
      Serial.println("new");
      for (byte i = 0; i < 4; i++) {
        tag += rfid.uid.uidByte[i];
      }
      Serial.print("UID = ");
      Serial.println(tag);
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  if (client) {                             // If a new client connects,
    Serial.println("\n--- New Client ---");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        //        header = client.readStringUntil('\r');
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //            // Display current state, and ON/OFF buttons for GPIO 5
            //            client.println("<p>GPIO 5 - State " + test + "</p>");
            client.println("<p>GPIO 5 - UID is " + tag + "</p>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop

            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    tag = "";
  }
}
