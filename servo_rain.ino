#include<Servo.h>
int rain_sensor = A5, servo=1;
Servo myServo;
void setup() {
 Serial.begin(9600);
 myServo.attach(servo);
 myServo.write(0);// put your setup code here, to run once:

}

void loop() {
  int sensorvalue=analogRead(rain_sensor);
  int motor= map(sensorvalue,220,1023,180,0);
  myServo.write(motor);
  Serial.println("sensor value is:");
  Serial.print(sensorvalue);
  Serial.print("servo motro ratates by agle");
  
  Serial.print(motor);
  delay(10000);// put your main code here, to run repeatedly:

}
