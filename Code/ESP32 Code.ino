#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 32   
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int mqpin = 33;


const char* ssid     = "Reverb";
const char* password = "Pr0p$rtyflip";
const char* serverName = "http://wearehelgg.com/post-esp-dt.php";
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "MQ135 + DHT22";
String sensorLocation = "Office";






void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}
void loop() {

  int mqdata = analogRead(mqpin);
  int mqconv = abs(mqdata*0.01);
 
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  //dht.humidity().getEvent(&event);
  //Serial.print(event.temperature);
  //Serial.println(event.relative_humidity);
  int humid = (event.temperature*2.5);
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    int ore=55;
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Prepare your HTTP POST request data
    
String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation +
"&value1=" + String(event.temperature) + "&value2=" + String(humid) + "&value3=" + String(mqconv);


    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);
}
