#include <dht.h>

dht DHT;

#define DHT11_PIN 7
#define Fan 6
void setup(){
  pinMode(Fan,OUTPUT);
  digitalWrite(Fan,HIGH);
  Serial.begin(9600);
  delay(900);
  Serial.println("DH11 Humidity & temperature sensor\n\n");
  delay(1000);
}

void loop()
{
  
  int chk = DHT.read11(DHT11_PIN);
//  int cha = DHT.readTemperature;
  Serial.print("current humidity");
  Serial.print(DHT.humidity);
  Serial.print("%");
  Serial.print("temperature");  
  Serial.print(DHT.temperature);
  Serial.print("C");

       if(chk<27)
  {
    digitalWrite(Fan,HIGH);
    Serial.println("Fan on");
    delay(100);
  }
  else{
    digitalWrite(Fan,LOW);
    Serial.println("FAN OFF");
  }
  delay(100);
}


