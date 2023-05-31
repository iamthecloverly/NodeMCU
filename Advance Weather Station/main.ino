#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Our HTML webpage contents with javascripts
#include "DHTesp.h" //DHT11 Library for ESP

#define LED 2 //On board LED

#define RAIN_SENSOR_PIN A0 // Rain sensor analog pin
#define DHTPIN D5          // DHT11 sensor pin
#define DHTTYPE DHT11     // DHT11 sensor type
 
#define ALTITUDE 1655.0 // Altitude in meters
 
DHTesp dht;

const char* ssid = "FROSTY";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
String s = MAIN_page; //Read HTML contents
server.send(200, "text/html", s); //Send web page
}

float humidity, temperature;
 
void handleADC() {
char status;
double T,P,p0,a;
double Tdeg, Tfar, phg, pmb;
 
int rain = analogRead(A0);
 
//Create JSON data
String data = "{\"Rain\":\""+String(rain)+"\",\"Pressuremb\":\""+String(pmb)+"\",\"Pressurehg\":\""+String(phg)+"\", \"Temperature\":\""+ String(temperature) +"\", \"Humidity\":\""+ String(humidity) +"\"}";
 
digitalWrite(LED,!digitalRead(LED)); //Toggle LED on data request ajax
server.send(200, "text/plane", data); //Send ADC value, temperature and humidity JSON to client ajax request
 
delay(dht.getMinimumSamplingPeriod());
 
humidity = dht.getHumidity();
temperature = dht.getTemperature();
 
Serial.print("H:");
Serial.println(humidity);
Serial.print("T:");
Serial.println(temperature); //dht.toFahrenheit(temperature));
Serial.print("R:");
Serial.println(rain);
}
 
void setup()
{
Serial.begin(115200);
Serial.println();
 
// dht11 Sensor
 
dht.setup(DHTPIN, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
pinMode(LED,OUTPUT);

WiFi.begin(ssid, password); //Connect to your WiFi router
Serial.println("");
 
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("Connecting");
Serial.print(".");
}
 
//If connection successful show IP address in serial monitor

Serial.println("");
  Serial.println(" * File: weather.ino");
  Serial.println(" * Author: SriBalaji");
  Serial.println(" * Date: May 31, 2023");
  Serial.println(" * Description: Arduino program for temperature and weather display");
  Serial.println(" * Website: www.sribalaji.eu.org");
  Serial.println(" *");
  Serial.println(" * MIT License");
  Serial.println(" *");
  Serial.println(" * Copyright (c) 2023 SriBalaji");
  Serial.println(" *");
  Serial.println(" * Permission is hereby granted, free of charge, to any person obtaining a copy");
  Serial.println(" * of this software and associated documentation files (the \"Software\"), to deal");
  Serial.println(" * in the Software without restriction, including without limitation the rights");
  Serial.println(" * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell");
  Serial.println(" * copies of the Software, and to permit persons to whom the Software is");
  Serial.println(" * furnished to do so, subject to the following conditions:");
  Serial.println(" *");
  Serial.println(" * The above copyright notice and this permission notice shall be included in all");
  Serial.println(" * copies or substantial portions of the Software.");
  Serial.println(" *");
  Serial.println(" * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
  Serial.println(" * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
  Serial.println(" * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
  Serial.println(" * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
  Serial.println(" * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
  Serial.println(" * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
  Serial.println(" * SOFTWARE.");
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP
 
server.on("/", handleRoot); //Which routine to handle at root location. This is display page
server.on("/readADC", handleADC); //This page is called by java Script AJAX
 
server.begin(); //Start server
Serial.println("HTTP server started");
}

void loop()
{
server.handleClient(); //Handle client requests
}
