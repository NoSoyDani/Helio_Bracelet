
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//===============================================================
//Configuración Pantalla.
//===============================================================
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//===============================================================
//Configuración WI-FI.
//===============================================================
const char* ssid = "REDJAM-2.4G-W23H";
const char* password = "pepito777";

ESP8266WebServer server(80); 

//===============================================================
// Formulario Principal.
//===============================================================
void base() {
 server.send(200,"text/html","<form action=\"/action_page\" method=\"POST\"><input type=\"text\" name=\"txt\" placeholder=\"\"><input type=\"submit\" value=\"Submit\"></form>"); 
}
//===============================================================
// Valor del texto de entrada.
//===============================================================
void text() {
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
   Serial.println(F("SSD1306 allocation failed"));
   for(;;); 
 }
 display.clearDisplay();
 display.setTextSize(0.5);
 display.setTextColor(WHITE);
 display.setCursor(0, 10);
 String txt = server.arg("txt"); 
 Serial.println(txt);
 display.println(txt);
 display.display(); 
 server.send(200, "text/html", "<meta http-equiv='refresh' content='0;URL=/' />"); //Redirección a la página principal
}
//==============================================================



void setup(void){
  Serial.begin(9600);
  //Wire.begin(2, 0); //Descomentar si ESP-01/S
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  WiFi.begin(ssid, password);    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("HELIO");
  server.on("/", base);             //Envio
  server.on("/action_page", text);  //Recepcion
  server.begin();                 
  display.display(); 
}
void loop(void){
  server.handleClient();          
}
