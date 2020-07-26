
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>




//===============================================================
//Configuración WI-FI.
//===============================================================
const char* ssid = "REDJAM-2.4G-W23H";
const char* password = "pepito777";

ESP8266WebServer server(80); //Server on port 80

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
 String txt = server.arg("txt"); 
 Serial.println(txt);
 server.send(200, "text/html", "<meta http-equiv='refresh' content='0;URL=/' />"); //Redirección a la página principal
}
//==============================================================






void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/", base);             //Envio
  server.on("/action_page", text);  //Recepcion
  server.begin();                 
  
}
void loop(void){
  server.handleClient();          
}
