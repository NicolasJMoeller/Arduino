//Author: Nicolas Möller, Cedric Bühler
#include "arduino_secrets.h"
#include "thingProperties.h" //Bibliothek thingProperties einbeziehen
#include "M5Stack.h" //Bibliothek M5Stack einbeziehen
#include <Adafruit_NeoPixel.h> //Bibliothek Adafruit_NeoPixel einbeziehen
#include <WiFi.h>// Bibliothek Wifi.h einbeziehen

#define M5STACK_FIRE_NEO_NUM_LEDS 10 // Anzahl LEDS
#define M5STACK_FIRE_NEO_DATA_PIN 15 // Pin 15 wird Data für Adafruit_NeoPixel
#define BRIGHTNESS 100 // Leuchtkraft einstellen (100% / Volle Leistung)
// Variable für Pixels des Adafruit_NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(M5STACK_FIRE_NEO_NUM_LEDS, M5STACK_FIRE_NEO_DATA_PIN, NEO_GRB + NEO_KHZ800); //
// Wifi Variablen
const char* ssid = "Data_miner";
const char* password = "3h20aua1oupzt";

//Setupphase des Geräts
void setup() {
  M5.begin(); //M5Stack soll Starten
  M5.Power.begin(); //M5Stack Strom soll Starten
  M5.Lcd.setTextColor(WHITE); //Textfarbe auf Weiss stellen
  M5.Lcd.setTextSize(4); //Grösse des Textes verstellen
  pinMode(36, INPUT); // Pin 36 wird als Input Quelle aktivert
  // Port werden angesprochen für die Nutzung deren Dienste
  Serial.begin(9600);
  Serial.begin(115200);
  // Zeit verzögerung 1500 milisekunden
  delay(1500);
  //Wifi verbindung
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  // Defined in thingProperties.h
  initProperties();

  // Verbindung zur Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}
// Start des Hauptprogramms
void loop() {
  // Button an aus funktion
  if (alarm_enable == false) {
    M5.Lcd.clear(BLACK);// Bildschrim reinigen
    M5.Speaker.mute();// sound stumm
    // Alle LED 1 - 9  ausschalten
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));
    pixels.setPixelColor(8, pixels.Color(0, 0, 0));
    pixels.setPixelColor(9, pixels.Color(0, 0, 0));
    pixels.show();// Macht die oben genannte einstellung Live
    mobile_alarm = false;//Variable mobile_alarm wird bei true wert von Pin 36 auf Wert false
    ArduinoCloud.update();
    M5.Lcd.setTextColor(WHITE); M5.Lcd.setTextSize(3);// setzt Farbe und Grösse für denn Text unten
        M5.Lcd.setCursor(60, 70); M5.Lcd.println("Bewegungs-"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text Bewegungs- aus
        M5.Lcd.setCursor(72, 110); M5.Lcd.println("melder"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text melder aus
        M5.Lcd.setCursor(65, 150); M5.Lcd.println("deaktiviert"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text dektiviert aus
        //Setzt oben Links die unteren Texte
        M5.Lcd.setCursor(0, 0); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("Motion-Alert with LED");
        M5.Lcd.setCursor(0, 15); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("by Nicolas and Cedric");
        delay(500);
    }
  else{
      ArduinoCloud.update();
        //if statment der wenn Pin 36 (Bewegungssensor) aktiviert ist wird der wert true
        if (digitalRead(36) == 1) {
        mobile_alarm = true; //Variable mobile_alarm wird bei true wert von Pin 36 auf Wert true
        ArduinoCloud.update(); // Update zur IoT Cloud
        M5.Lcd.fillScreen(RED); //Kompletter Bildschirm Rot machen
        // Alle LED 1 - 9 Blau machen
        pixels.setPixelColor(0, pixels.Color(0, 0, 255));
        pixels.setPixelColor(1, pixels.Color(0, 0, 255));
        pixels.setPixelColor(2, pixels.Color(0, 0, 255));
        pixels.setPixelColor(3, pixels.Color(0, 0, 255));
        pixels.setPixelColor(4, pixels.Color(0, 0, 255));
        pixels.setPixelColor(5, pixels.Color(0, 0, 255));
        pixels.setPixelColor(6, pixels.Color(0, 0, 255));
        pixels.setPixelColor(7, pixels.Color(0, 0, 255));
        pixels.setPixelColor(8, pixels.Color(0, 0, 255));
        pixels.setPixelColor(9, pixels.Color(0, 0, 255));
        pixels.show(); // Macht die oben genannte einstellung Live
        //Dreieck einblenden
        M5.Lcd.fillTriangle(160, 90, 130, 140, 190, 140, BLUE);
        // Ausrufezeichen erstellen (einzel pixel erstellung)
        M5.Lcd.drawPixel(160, 110, BLACK);
        M5.Lcd.drawPixel(160, 111, BLACK);
        M5.Lcd.drawPixel(160, 112, BLACK);
        M5.Lcd.drawPixel(160, 113, BLACK);
        M5.Lcd.drawPixel(160, 114, BLACK);
        M5.Lcd.drawPixel(160, 115, BLACK);
        M5.Lcd.drawPixel(160, 116, BLACK);
        M5.Lcd.drawPixel(160, 117, BLACK);
        M5.Lcd.drawPixel(160, 118, BLACK);
        M5.Lcd.drawPixel(160, 119, BLACK);
        M5.Lcd.drawPixel(160, 120, BLACK);
        M5.Lcd.drawPixel(160, 121, BLACK);
        M5.Lcd.drawPixel(160, 122, BLACK);
        M5.Lcd.drawPixel(160, 123, BLACK);
        M5.Lcd.drawPixel(160, 124, BLACK);
        M5.Lcd.drawPixel(161, 110, BLACK);
        M5.Lcd.drawPixel(161, 111, BLACK);
        M5.Lcd.drawPixel(161, 112, BLACK);
        M5.Lcd.drawPixel(161, 113, BLACK);
        M5.Lcd.drawPixel(161, 114, BLACK);
        M5.Lcd.drawPixel(161, 115, BLACK);
        M5.Lcd.drawPixel(161, 116, BLACK);
        M5.Lcd.drawPixel(161, 117, BLACK);
        M5.Lcd.drawPixel(161, 118, BLACK);
        M5.Lcd.drawPixel(161, 119, BLACK);
        M5.Lcd.drawPixel(161, 120, BLACK);
        M5.Lcd.drawPixel(161, 121, BLACK);
        M5.Lcd.drawPixel(161, 122, BLACK);
        M5.Lcd.drawPixel(161, 123, BLACK);
        M5.Lcd.drawPixel(161, 124, BLACK);
        M5.Lcd.drawPixel(159, 110, BLACK);
        M5.Lcd.drawPixel(159, 111, BLACK);
        M5.Lcd.drawPixel(159, 112, BLACK);
        M5.Lcd.drawPixel(159, 113, BLACK);
        M5.Lcd.drawPixel(159, 114, BLACK);
        M5.Lcd.drawPixel(159, 115, BLACK);
        M5.Lcd.drawPixel(159, 116, BLACK);
        M5.Lcd.drawPixel(159, 117, BLACK);
        M5.Lcd.drawPixel(159, 118, BLACK);
        M5.Lcd.drawPixel(159, 119, BLACK);
        M5.Lcd.drawPixel(159, 120, BLACK);
        M5.Lcd.drawPixel(159, 121, BLACK);
        M5.Lcd.drawPixel(159, 122, BLACK);
        M5.Lcd.drawPixel(159, 123, BLACK);
        M5.Lcd.drawPixel(159, 124, BLACK);
        M5.Lcd.drawPixel(160, 126, BLACK);
        M5.Lcd.drawPixel(160, 127, BLACK);
        M5.Lcd.drawPixel(160, 128, BLACK);
        M5.Lcd.drawPixel(161, 126, BLACK);
        M5.Lcd.drawPixel(161, 127, BLACK);
        M5.Lcd.drawPixel(161, 128, BLACK);
        M5.Lcd.drawPixel(159, 126, BLACK);
        M5.Lcd.drawPixel(159, 127, BLACK);
        M5.Lcd.drawPixel(159, 128, BLACK);
        M5.Lcd.setTextColor(WHITE); M5.Lcd.setTextSize(4);// setzt Farbe und Grösse für denn Text unten
        M5.Lcd.setCursor(80, 40); M5.Lcd.println("Bewegung"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text Bewegung aus
        M5.Lcd.setCursor(80, 170); M5.Lcd.println("entdeckt"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text endeckt aus
        M5.Speaker.tone(800, 1000); //Lautsprecher Ton wird ausgegeben
        //Setzt oben Links die unteren Texte
        M5.Lcd.setCursor(0, 0); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("Motion-Alert with LED");
        M5.Lcd.setCursor(0, 15); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("by Nicolas and Cedric");
        delay(500); // Verzögerung von einer halben Sekunden
        M5.Lcd.fillScreen(BLUE);//Kompletter Bildschirm Blau machen
        // Alle LED 1 - 9 Rot machen
        pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.setPixelColor(1, pixels.Color(255, 0, 0));
        pixels.setPixelColor(2, pixels.Color(255, 0, 0));
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));
        pixels.setPixelColor(4, pixels.Color(255, 0, 0));
        pixels.setPixelColor(5, pixels.Color(255, 0, 0));
        pixels.setPixelColor(6, pixels.Color(255, 0, 0));
        pixels.setPixelColor(7, pixels.Color(255, 0, 0));
        pixels.setPixelColor(8, pixels.Color(255, 0, 0));
        pixels.setPixelColor(9, pixels.Color(255, 0, 0));
        pixels.show(); // Macht die oben genannte einstellung Live
        M5.Speaker.tone(400, 1000); //Lautsprecher Ton wird ausgegeben
        //Dreieck einblenden
        M5.Lcd.fillTriangle(160, 90, 130, 140, 190, 140, RED);
        // Ausrufezeichen erstellen (einzel pixel erstellung)
        M5.Lcd.drawPixel(160, 110, BLACK);
        M5.Lcd.drawPixel(160, 111, BLACK);
        M5.Lcd.drawPixel(160, 112, BLACK);
        M5.Lcd.drawPixel(160, 113, BLACK);
        M5.Lcd.drawPixel(160, 114, BLACK);
        M5.Lcd.drawPixel(160, 115, BLACK);
        M5.Lcd.drawPixel(160, 116, BLACK);
        M5.Lcd.drawPixel(160, 117, BLACK);
        M5.Lcd.drawPixel(160, 118, BLACK);
        M5.Lcd.drawPixel(160, 119, BLACK);
        M5.Lcd.drawPixel(160, 120, BLACK);
        M5.Lcd.drawPixel(160, 121, BLACK);
        M5.Lcd.drawPixel(160, 122, BLACK);
        M5.Lcd.drawPixel(160, 123, BLACK);
        M5.Lcd.drawPixel(160, 124, BLACK);
        M5.Lcd.drawPixel(161, 110, BLACK);
        M5.Lcd.drawPixel(161, 111, BLACK);
        M5.Lcd.drawPixel(161, 112, BLACK);
        M5.Lcd.drawPixel(161, 113, BLACK);
        M5.Lcd.drawPixel(161, 114, BLACK);
        M5.Lcd.drawPixel(161, 115, BLACK);
        M5.Lcd.drawPixel(161, 116, BLACK);
        M5.Lcd.drawPixel(161, 117, BLACK);
        M5.Lcd.drawPixel(161, 118, BLACK);
        M5.Lcd.drawPixel(161, 119, BLACK);
        M5.Lcd.drawPixel(161, 120, BLACK);
        M5.Lcd.drawPixel(161, 121, BLACK);
        M5.Lcd.drawPixel(161, 122, BLACK);
        M5.Lcd.drawPixel(161, 123, BLACK);
        M5.Lcd.drawPixel(161, 124, BLACK);
        M5.Lcd.drawPixel(159, 110, BLACK);
        M5.Lcd.drawPixel(159, 111, BLACK);
        M5.Lcd.drawPixel(159, 112, BLACK);
        M5.Lcd.drawPixel(159, 113, BLACK);
        M5.Lcd.drawPixel(159, 114, BLACK);
        M5.Lcd.drawPixel(159, 115, BLACK);
        M5.Lcd.drawPixel(159, 116, BLACK);
        M5.Lcd.drawPixel(159, 117, BLACK);
        M5.Lcd.drawPixel(159, 118, BLACK);
        M5.Lcd.drawPixel(159, 119, BLACK);
        M5.Lcd.drawPixel(159, 120, BLACK);
        M5.Lcd.drawPixel(159, 121, BLACK);
        M5.Lcd.drawPixel(159, 122, BLACK);
        M5.Lcd.drawPixel(159, 123, BLACK);
        M5.Lcd.drawPixel(159, 124, BLACK);
        M5.Lcd.drawPixel(160, 126, BLACK);
        M5.Lcd.drawPixel(160, 127, BLACK);
        M5.Lcd.drawPixel(160, 128, BLACK);
        M5.Lcd.drawPixel(161, 126, BLACK);
        M5.Lcd.drawPixel(161, 127, BLACK);
        M5.Lcd.drawPixel(161, 128, BLACK);
        M5.Lcd.drawPixel(159, 126, BLACK);
        M5.Lcd.drawPixel(159, 127, BLACK);
        M5.Lcd.drawPixel(159, 128, BLACK);
        M5.Lcd.setTextColor(WHITE); M5.Lcd.setTextSize(4);// setzt Farbe und Grösse für denn Text unten
        M5.Lcd.setCursor(80, 40); M5.Lcd.println("Bewegung"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text Bewegung aus
        M5.Lcd.setCursor(80, 170); M5.Lcd.println("entdeckt"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text endeckt aus
        //Setzt oben Links die unteren Texte
        M5.Lcd.setCursor(0, 0); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("Motion-Alert with LED");
        M5.Lcd.setCursor(0, 15); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("by Nicolas and Cedric");
        delay(500); // Verzögerung von einer halben Sekunden
      }
    // Wenn Pin 36 nicht aktiviert ist dann ist der Wert false
    else {
        mobile_alarm = false;//Variable mobile_alarm wird bei false wert von Pin 36 auf Wert false
        ArduinoCloud.update(); // Update zur IoT Cloud
        M5.Lcd.fillScreen(BLACK); //Kompletter Bildschirm Schwarz machen
        // Alle LED 1 - 9  ausschalten
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.setPixelColor(1, pixels.Color(0, 0, 0));
        pixels.setPixelColor(2, pixels.Color(0, 0, 0));
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.setPixelColor(4, pixels.Color(0, 0, 0));
        pixels.setPixelColor(5, pixels.Color(0, 0, 0));
        pixels.setPixelColor(6, pixels.Color(0, 0, 0));
        pixels.setPixelColor(7, pixels.Color(0, 0, 0));
        pixels.setPixelColor(8, pixels.Color(0, 0, 0));
        pixels.setPixelColor(9, pixels.Color(0, 0, 0));
        pixels.show();// Macht die oben genannte einstellung Live
        M5.Speaker.mute(); // Lautsprecher wird stumm geschalten
        M5.Lcd.setTextColor(WHITE); M5.Lcd.setTextSize(3);// setzt Farbe und Grösse für denn Text unten
        M5.Lcd.setCursor(60, 70); M5.Lcd.println("Bewegungs-"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text Bewegungs- aus
        M5.Lcd.setCursor(72, 110); M5.Lcd.println("melder"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text melder aus
        M5.Lcd.setCursor(65, 150); M5.Lcd.println("aktiviert"); // Setzt den Cursor auf die Bestimmte stelle und gibt den Text aktiviert aus
        //Setzt oben Links die unteren Texte
        M5.Lcd.setCursor(0, 0); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("Motion-Alert with LED");
        M5.Lcd.setCursor(0, 15); M5.Lcd.setTextColor(GREEN); M5.Lcd.setTextSize(1); M5.Lcd.println("by Nicolas and Cedric");
        delay(250); // Verzögerung von einer Viertel Sekunde
      }
  }
}
// void für die Cloud funktion des mobile_alarm
void onMobileAlarmChange()  {

}

void onAlarmEnableChange(){
  
}
