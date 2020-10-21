#include <Servo.h>
Servo servo1;
int rainSen_pin = A5;
int Buzzer_pin = 13;
int servol=1;
void setup() {
  Serial.begin(9600);
  pinMode(rainSen_pin, INPUT);
  pinMode(Buzzer_pin, OUTPUT);
  digitalWrite(Buzzer_pin,LOW);
  delay(3000);
    

  
}

void loop() {

 servo1.write(0);
  if(rainSen_pin){
  servo1.write(80);
  }
 int RainSenReading = analogRead(rainSen_pin); 
 Serial.print("SensorValue:");
 Serial.print("\t");
 Serial.print(RainSenReading);
 Serial.print("\t");

 if (RainSenReading <= 800)
  {
    digitalWrite(Buzzer_pin, HIGH);
 
    Serial.println("Rain");
  }

  else
  {
    digitalWrite(Buzzer_pin, LOW);
  
    Serial.println("No Rain");
  }
  delay(250);
}
