#include <String.h>
#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
#include <Wire.h>  // Comes with Arduino IDE
#define echopin 11 // Echo Pin
#define trigpin 10 // Trigger Pin
int duration, distance;
int stats;
int count = 0;
void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  pinMode(trigpin, OUTPUT);   // sets the trigpin as output
  pinMode(echopin, INPUT);    // sets the echopin as input
  delay(800);
}
 
void loop()
{

  digitalWrite(trigpin, LOW);    // sets voltage to 0v
  delayMicroseconds(1000);        // delays for 1000 microseconds
  digitalWrite(trigpin, HIGH);     // sets voltage to 5v
  duration = pulseIn(echopin, HIGH);    // waits for the pin to go from LOW to HIGH, starts timing, then waits for the pin to go LOW and stops timing
  distance = ( duration / 2) / 29.1;     // calculates distance
  if (distance < 20) {
    stats = 1;
  } else {
    stats = 0;
  }
  if (stats == 1) {
    count = count + 1;
  }
  Serial.print(distance);
  Serial.println();
  delay(300);
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
  gprsSerial.println("AT");
  delay(800);
  gprsSerial.println("AT+CPIN?");
  delay(800);
  gprsSerial.println("AT+CREG?");
  delay(1000);
  gprsSerial.println("AT+CGATT?");
  delay(800);
  gprsSerial.println("AT+CIPSHUT");
  delay(800);
  gprsSerial.println("AT+CIPSTATUS");
  delay(800);
  gprsSerial.println("AT+CIPMUX=0");
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CIPSPRT=0");
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(800);
  ShowSerialData();
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(800);
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key=CFIUX7V82XF1AQ0J&field1=" + String(distance) +"&field2="+String(count);
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  delay(50);
  ShowSerialData();
  gprsSerial.println((char)26);//sending
  delay(50);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
  ShowSerialData();
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(50);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(500); 
}