
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(2, 0); // GPIO2 => SDA, GPIO0 => SCK 
  pinMode(LED_BUILTIN, OUTPUT);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  delay(2000);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Sistema Actualizado");
  display.display(); 
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1000);                     
  digitalWrite(LED_BUILTIN, LOW);    
  delay(1000);                       
  
}
