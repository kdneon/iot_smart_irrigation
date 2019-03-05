#include<DHT.h>
#include "UbidotsMicroESP8266.h"
#define TOKEN  "A1E-JJMfEqh5SStkskqz0MmSaWmyzusZmS"  // Put here your Ubidots TOKEN
#define WIFISSID "kd"// SSID NAME
#define PASSWORD "kd" //SSID PASSWORD
#define DHTPIN 4
//int motor =17;
const int sensor_pin = A0;
int motor =12;

Ubidots client(TOKEN);
DHT dht(DHTPIN,DHT22);
void setup(){
  pinMode(motor,OUTPUT);
    Serial.begin(115200);
    delay(10);
    dht.begin();
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
       float moisture_percentage;
      float hum = dht.readHumidity();
     float temp = dht.readTemperature();
     //moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
   moisture_percentage = analogRead(sensor_pin);
    moisture_percentage = map(moisture_percentage,0,1023,0,100);
   moisture_percentage=100-moisture_percentage;
 
  Serial.println("moisture_percentage %");
  Serial.println(moisture_percentage);
  
    client.add("Temperature", temp);
    client.add("humidity",hum);
    client.add("Soil Moisture %",moisture_percentage);

   if(moisture_percentage <= 15)
   {
    digitalWrite(motor,HIGH);
     client.add("Motor",1);
   } 
   else
   {
     digitalWrite(motor,LOW);
      client.add("Motor",0);
   }
       client.sendAll(true);
}
