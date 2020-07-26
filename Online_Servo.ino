
// Load Wi-Fi library
#include <ESP8266WiFi.h>
// Load Servo library
#include <Servo.h>

//Wi-Fi Station data
const char* ssid = "REDJAM-2.4G-W23H";
const char* password = "pepito777";

// Set web server port number to 80
WiFiServer server(80);
//Define servo
Servo servo1;        
//Define url variable
String header;
//Variable of state
String outputState = "off";
//Assign variables
#define SERVO_PIN 5



void setup() {
  // Baud rate (debugging purposes)
  Serial.begin(115200);
  // Servo default options
  servo1.attach(5);   
  servo1.write(0);
  delay(2000); 

  //----------------------------------------------------------------------------
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  }
  //----------------------------------------------------------------------------


void loop() {
  

  WiFiClient client = server.available(); // Listen for incoming clients
  if (client) { // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        header += c;
        if (c == '\n') { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
           if (currentLine.length() == 0) {
             // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
             // and a content-type so the client knows what's coming, then a blank line:
             client.println("HTTP/1.1 200 OK");
             client.println("Content-type:text/html");
             client.println("Connection: close");
             client.println();

             //ACTIONS
             if (header.indexOf("GET /servo/on") >= 0) {
               Serial.println("Servo in 180 degree.");
               outputState = "on";
               servo1.write(180);   
             } else if (header.indexOf("GET /servo/off") >= 0) {
               Serial.println("Servo in 0 degree.");
               outputState = "off";
               servo1.write(0);                                  
             } 
          
             //Display the HTML web page
             client.println("<!DOCTYPE html><html>");
             client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
             client.println("<link rel=\"icon\" href=\"data:,\">");
             //CSS
             client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
             client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
             client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
             
             // Web Page Title
             client.println("<body><h1>IoT Cafetera</h1>");
             //Led status
             client.println("<p>Servo State " + outputState + "</p>");
          
             if (outputState=="off") {
               client.println("<p><a href=\"/servo/on\"><button class=\"button\">ON</button></a></p>");
             } else {
               client.println("<p><a href=\"/servo/off\"><button class=\"button\">OFF</button></a></p>");
             }
        
             client.println("</body></html>");
             client.println();
             break;
        
           } else{
             currentLine="";
           }
          } else if(c != '\r'){
            currentLine +=c;
          }
        }
      }
    //Clear header variable
      header="";
    //Close connection
      client.stop();
      Serial.println("Client Disconnected. ");
      Serial.println("");
   
  }       
}
