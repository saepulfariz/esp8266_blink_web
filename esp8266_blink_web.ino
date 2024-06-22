#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "HTML.h"

// Konfigurasi WiFi
const char *ssid = "saepulfariz-device";
const char *password = "";

String ssidNew = "", passNew;

ESP8266WebServer server(80);

//== Rountin dieksekusi saat browser dibuka / page dipanggil ==//
void handleRoot(){
  server.send(200, "text/html", index_html);
}

void handleOn(){
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", on_html);
}

void handleOff(){
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/html", off_html);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  Serial.begin(115200);
  delay(1000);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(IP);

  server.on("/", handleRoot); // Routine untuk menghandle homepage
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin(); // Mulai server
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  // digitalWrite(LED_BUILTIN, LOW);
  //delay(1000);                      // Wait for a second
  //digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  //delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
  server.handleClient();
}
