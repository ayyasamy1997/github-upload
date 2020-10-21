#include<SoftwareSerial.h>

#define TxD 3
#define RxD 2
#define LED_PIN 13
#define LED_PIN1 12
#define LED_PIN2 11
#define LED_PIN3 10

SoftwareSerial bluetoothSerial(TxD, RxD);

char c;

void setup() {
  bluetoothSerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
   pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
     pinMode(LED_PIN3, OUTPUT);
  }

void loop() {
  if(bluetoothSerial.available()){
    c = bluetoothSerial.read();
    Serial.println(c);
    if(c=='1'){
      digitalWrite(LED_PIN, HIGH);          
    }
    if(c=='0'){
      digitalWrite(LED_PIN, LOW);
    }
    if(c=='1'){
      digitalWrite(LED_PIN1, HIGH);          
    }
    if(c=='0'){
      digitalWrite(LED_PIN1, LOW);
    }
    if(c=='1'){
      digitalWrite(LED_PIN2, HIGH);          
    }
    if(c=='0'){
      digitalWrite(LED_PIN2, LOW);
    }
    if(c=='1'){
      digitalWrite(LED_PIN3, HIGH);          
    }
    if(c=='0'){
      digitalWrite(LED_PIN3, LOW);
    }
  }
}
