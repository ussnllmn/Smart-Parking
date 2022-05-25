#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D2, D3);

// Network credentials
const char* ssid     = "Mero Asebi";
const char* password = "james159";
WiFiServer server(80);

/////////////// Timer ///////////////
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
/////////////////////////////////////

int b1 = 0, b2 = 0, b3 = 0;
String recive = "", total, temp = "", username;
String header;

void setup() {
  Serial.begin(9600);
  NodeSerial.begin(57600);
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

  while (NodeSerial.available() > 0)
  {
    recive = "";
    recive = NodeSerial.readString();
    temp = recive;
    Serial.println(recive);
    int index = recive.indexOf(',');
    username = recive.substring(0, index);
    if (username == "DEW") NodeSerial.println(b1);
    else if (username == "FON") NodeSerial.println(b2);
    else if (username == "SEK") NodeSerial.println(b3);
  }

  WiFiClient client = server.available();   // Listen for incoming clients
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
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /1/100") >= 0) b1 += 100;
            else if (header.indexOf("GET /2/100") >= 0) b2 += 100;
            else if (header.indexOf("GET /3/100") >= 0) b3 += 100;

            if (recive == "") {
              recive = "Guest,0,0,0";
              temp = recive;
            }
            else {
              recive = "";
              recive = temp;
              if (username == "DEW") NodeSerial.println(b1);
              else if (username == "FON") NodeSerial.println(b2);
              else if (username == "SEK") NodeSerial.println(b3);
            }

            recive += ",";
            recive += b1;
            recive += ",";
            recive += b2;
            recive += ",";
            recive += b3;

            client.print(recive);
            Serial.println(recive);

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
  }
}
