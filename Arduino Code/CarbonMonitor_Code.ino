//Carbon monoxide emission monitor. 
//Using NodeMCU ESP8266 ,MQ135, DHT11
//Written by Oluwafemi Oreoluwa ,07/01/2022
//Before compling the code , ensure you added the Respective lbraries to your Arduino IDE

#define MQ135_Sensor A0

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
int Raw_Data=analogRead(MQ135_Sensor);
int Mapped_Data=map(MQ135_Sensor,0,1024,0,100);
Serial.println(Mapped_Data);
delay(500);

}