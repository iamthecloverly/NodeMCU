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
Serial.print(".");
}
 
//If connection successful show IP address in serial monitor
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
