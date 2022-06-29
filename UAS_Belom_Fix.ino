/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLTwaGNoli"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "2wwrhNqRiI0F2WytDfOCThtn0kz803R0"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <OneWire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2

char auth[] = BLYNK_AUTH_TOKEN;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Rahasia";
char pass[] = "12345678";

//code written by Md iqbal
//website:-techiqbal.com
//Youtube:-Techiqbal
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void sendSensor()
{
float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println('Failed to read from DHT sensor!');
return;
}

Blynk.virtualWrite(V5, h); //V5 is for Humidity
Blynk.virtualWrite(V6, t); //V6 is for Temperature
}
void setup()
{
Serial.begin(9600);
dht.begin();

timer.setInterval(1000L, sendSensor);
Blynk.begin(auth, ssid, pass);
sensors.begin();
}
int sensor=0;
int output=0;
void sendTemps()
{
sensor=analogRead(A0);
output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
delay(1000);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
Serial.println(temp);
Serial.print('moisture = ');
Serial.print(output);
Serial.println('%');
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,output);
delay(1000);
}
void loop()
{
Blynk.run();
timer.run();
sendTemps();
}   
//code written by Md iqbal
//website:-techiqbal.com
//Youtube:-Techiqbal
