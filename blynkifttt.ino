
#include "Adafruit_MQTT.h"                                  // Adafruit MQTT library
#include "Adafruit_MQTT_Client.h"                           // Adafruit MQTT library

#include <TinyGPS++.h> 
#include <SoftwareSerial.h>
#include<Blynk.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "5754d275026e47e6a341f1ad68f2eca5"; //gps
//char auth[] = "6c2929d13a7d4eeea2408d505014f695";
char ssid[] = "Boobal";
char pass[] = "boobal123";
unsigned int move_index = 1;       // fixed location for now
static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget

SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

BlynkTimer timer;

float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS




int pump=D3;
int gass=A0;
int sensorpin=D0;
int sensorvalue;
int buzzer=D4;

int val = 0; 



#define WLAN_SSID       "Boobal"                        // Enter Your router SSID
#define WLAN_PASS       "boobal123"                        // Enter Your router Password

//************************* Adafruit.io Setup *********************************

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                                // use 8883 for SSL
#define AIO_USERNAME    "Boobal"                      // Enter Your Adafruit IO Username
#define AIO_KEY         "38255efcf6c440419604e50fe84f7e93"                      // Enter Your Adafruit IO Key

//************ Global State (you don't need to change this!) ******************

WiFiClient client;                                          // Create an ESP8266 WiFiClient class to connect to the MQTT server.

const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;           // Store the MQTT server, username, and password in flash memory.
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

//****************************** Feeds ***************************************

// Setup a feed called 'motion' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char motion_FEED[] PROGMEM = AIO_USERNAME "/feeds/gas";
Adafruit_MQTT_Publish motion = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gas");

//************************** Setup *******************************************


void setup() {
Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  // put your setup code here, to run once:
pinMode(buzzer,OUTPUT);
pinMode(pump,OUTPUT);
pinMode(gass,INPUT);
pinMode(sensorpin,INPUT);


 WiFi.mode(WIFI_STA);                                    // Setup ESP8266 as a wifi station
  WiFi.disconnect();                                      // Disconnect if needed
  delay(100);                                             // short delay 
     
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
 
Serial.println();
  ss.begin(GPSBaud);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
}

void loop() {
  // put your main code here, to run repeatedly:

connectWifi();
  MQTT_connect();             
  
int gassval=analogRead(gass);
sensorvalue=digitalRead(sensorpin);
Serial.println(sensorvalue);
Serial.println(gassval);

 while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
  Blynk.run();
  timer.run();


if(sensorvalue==0)
{
  Serial.println("FIRE DETECTED");
  digitalWrite(buzzer,HIGH);
  digitalWrite(pump,HIGH);
  delay(1000);
  Blynk.notify("FIRE DETECTED");
  Blynk.email("boobalbpcs@gmail.com","subject:FIRE DETECTED","Fire Detected secure immediatly");
  }

  if (gassval>630)                                        // check if the input is HIGH
  {                                                       
    digitalWrite(buzzer, HIGH);                           // Turn the LED ON
    Serial.println("gas detected!");

    Blynk.notify("FIRE DETECTED");
    Blynk.email("boobalbpcs@gmail.com","subject:FIRE DETECTED","Fire Detected secure immediatly");

     
    if (! motion.publish(gassval))                        // Publish to Adafruit the PIR sensor value '1'
        {                                
         Serial.println(F("Failed"));                  // If it failed to publish, print Failed
        }    else 
           {             
             Serial.println(F("Data Sent!"));             // If data successfully published      
           }      
  } 

  
  /*if(gassval>800)
  {
    Serial.println("GASS LEAKED");
    digitalWrite(buzzer,HIGH);
    digitalWrite(pump,HIGH);
    delay(1000);
    Blynk.notify("FIRE DETECTED");
    Blynk.email("boobalbpcs@gmail.com","subject:FIRE DETECTED","Fire Detected secure immediatly");
    }*/
  else
  {
    Serial.println("NO FLAME NO GASS Stay Cool");
    motion.publish(gassval);
    digitalWrite(buzzer,LOW);
    digitalWrite(pump,LOW);
    delay(2000);
    }
 
      if(! mqtt.ping()) {mqtt.disconnect();}                // Ping Adafruit.IO to keep the MQTT connection alive

    Blynk.run();
}

//********************** WiFi Coonect *************************************
void connectWifi()
{   
  if (WiFi.status() == WL_CONNECTED){ return; }           // If already connected to WiFi, return to loop
   WiFi.begin(WLAN_SSID, WLAN_PASS);                      // Start a WiFi connection and enter SSID and Password
              while (WiFi.status() != WL_CONNECTED) {     // While waiting on connection to start display "..."
                  delay(500);
                  Serial.print(".");                  
              } 
              Serial.println("Connected");              
            MQTT_connect();                               // Run Procedure to connect to Adafruit IO MQTT              
}

// ******************* MQTT Connect - Adafruit IO **************************
void MQTT_connect() 
{
  int8_t ret;
  if (mqtt.connected()) { return; }                       // Stop if already connected to Adafruit
  Serial.println("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {                   // Connect to Adafruit, will return 0 if connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT...");
       mqtt.disconnect();
       delay(5000);                                       // wait 5 seconds
       retries--;
       if (retries == 0) {                                // basically die and wait for WatchDogTimer to reset me                                                          
         while (1);         
       }
  }
  Serial.println("MQTT Connected!");  
}

void displayInfo()
{ 

  if (gps.location.isValid() ) 
  {
    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               //get speed
       Blynk.virtualWrite(V3, spd);
       
       sats = gps.satellites.value();    //get number of satellites
       Blynk.virtualWrite(V4, sats);

       bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
       Blynk.virtualWrite(V5, bearing);               
      
    
  }
  

  Serial.println();
}
