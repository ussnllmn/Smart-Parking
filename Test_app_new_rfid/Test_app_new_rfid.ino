#include <SPI.h>
#include <RFID.h>
#include <ESP8266WiFi.h>

#define SS_PIN D2
#define RST_PIN D1
RFID rfid(SS_PIN, RST_PIN);

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
String tag;

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
  SPI.begin();
  rfid.init();
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
  RFID();
  if (client) {                             // If a new client connects,
    Serial.println("\n--- New Client ---"); // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor

        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

           
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
    client.stop();
    Serial.println("Client disconnected.");
  }
}

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
      } else {
        Serial.print(".");
      }
    }
  }
  rfid.halt();
}
