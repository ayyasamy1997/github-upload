#include <Servo.h>
Servo myservo;  
#define sensor 7
int sensorstate;
void setup() {
 pinMode(sensor, INPUT);
 pinMode(13, OUTPUT);
 Serial.begin(9600);
 myservo.attach(9); 
 myservo.write(90);
 delay(1000);
}
void loop() {
 myservo.write(90);
 
 if(digitalRead(sensor) == HIGH){
   myservo.write(0);
   delay(500);
   myservo.write(90);
   delay(500);
   Serial.println("WHITE");
 }
 
 else if(digitalRead(sensor) == LOW){
   digitalWrite(13, HIGH);
   myservo.write(180);
   delay(500);
   myservo.write(90);
   delay(500);
   Serial.println("BLACK");
   digitalWrite(13, LOW);
 }
 delay(5000);
}
