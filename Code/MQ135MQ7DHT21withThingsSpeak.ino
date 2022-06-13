#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <WiFi.h>
#include <WiFiMulti.h>
#include "DHT.h"
#define DHTPIN 32    
int co2;
int co;
#define DHTTYPE DHT21  

DHT dht(DHTPIN, DHTTYPE);
WiFiMulti WiFiMulti;

const char* ssid     = "Reverb"; // Your SSID (Name of your WiFi)
const char* password = "Pr0p$rtyflip"; //Your Wifi password

const char* host = "api.thingspeak.com";

String api_key = "NMT1E6UIVL3LNZEL"; // Your API Key provied by thingspeak
void setup(){
  Serial.begin(9600);
   Serial.println(F("DHTxx test!"));
   pinMode(33,INPUT);
  dht.begin();
  lcd.setCursor(0, 0);
  lcd.init();                    
  lcd.backlight();
}

void loop(){

  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);
  co2=map(analogRead(33),0,2111,0,200);
  co=map(analogRead(35),2900,4095,0,200);

  lcd.setCursor(0, 0);
  lcd.print("Tmp:");
  lcd.setCursor(4, 0);
  lcd.print(t);
  lcd.setCursor(6, 0);
  lcd.print("%");

  lcd.setCursor(10, 0);
  lcd.print("Hm:");
  lcd.setCursor(11, 0);
  lcd.print(h);
  lcd.setCursor(12, 0);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Co2:");
  lcd.setCursor(4, 1);
  lcd.print(co2);
  lcd.setCursor(6, 1);
  lcd.print("%");

  lcd.setCursor(8, 1);
  lcd.print("Co:");
  lcd.setCursor(11, 1);
  lcd.print(co);
   lcd.setCursor(15, 1);
  lcd.print("%");
  Connect_to_Wifi();
  Send_Data(t,h,co2,co);

}

void Connect_to_Wifi()
{
  // We start by connecting to a WiFi network
  WiFiMulti.addAP(ssid, password);

  Serial.println();

  
    while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void Send_Data(float t, float h ,int co2,int co)
{
  // map the moist to 0 and 100% for a nice overview in thingspeak.
  Serial.println("");
  Serial.println("Prepare to send data");
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(t);
    data_to_send += "&field2=";
    data_to_send += String(h);
    data_to_send += "&field3=";
    data_to_send += String(co2);
    data_to_send += "&field4=";
    data_to_send += String(co);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(1000);
  }

  client.stop();

}