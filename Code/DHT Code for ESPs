#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <Ticker.h>
DHTesp dht;
void tempTask(void *pvParameters);
void triggerGetTemp();
TaskHandle_t tempTaskHandle = NULL;
Ticker tempTicker;
ComfortState cf;
bool tasksEnabled = false;
int dhtPin = 32;


bool initTemp() {
  byte resultValue = 0;
  // Initialize temperature sensor
  dht.setup(dhtPin, DHTesp::DHT22);
  xTaskCreatePinnedToCore(
      tempTask,                       /* Function to implement the task */
      "tempTask ",                    /* Name of the task */
      4000,                           /* Stack size in words */
      NULL,                           /* Task input parameter */
      5,                              /* Priority of the task */
      &tempTaskHandle,                /* Task handle. */
      1);                             /* Core where the task should run */
    tempTicker.attach(5, triggerGetTemp);
}


void triggerGetTemp() {
  if (tempTaskHandle != NULL) {
     xTaskResumeFromISR(tempTaskHandle);
  }
}


void tempTask(void *pvParameters) {
  Serial.println("tempTask loop started");
  while (1){ // tempTask loop
  TempAndHumidity newValues = dht.getTempAndHumidity();
  if (dht.getStatus() != 0) {
    Serial.println("DHT11 error status: " + String(dht.getStatusString()));
  }
  float heatIndex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
  float dewPoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint));
    vTaskSuspend(NULL);
  }
}



  
void setup()
{
  Serial.begin(115200);
 initTemp();
 tasksEnabled = true;
}
void loop() {

}