//ayyasamy
#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>

const char* ssid = "Ayyasamy";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,2,1);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);
uint8_t motor1=16;
uint8_t motor2=5;
uint8_t motor3=4;
uint8_t motor4=0;
void setup()
{
 // ClientRequest = "";
 Serial.println();
   Serial.print("MAC: ");
   Serial.println(WiFi.macAddress());
             

Serial.begin(9600);
pinMode(16, OUTPUT);
pinMode(5, OUTPUT);
pinMode(4, OUTPUT);
pinMode(0, OUTPUT);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  }
  Serial.println("Connected");
 
  server.on("/", handle_OnConnect);
  server.on("/motor1", handle_motor1on);
  server.on("/motor1", handle_motor1off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
   // ClientRequest = (client.readStringUntil('\r'));
    //ClientRequest = (client.remoteIP());
    server.handleClient();
    if (motor1,motor2,motor3,motor4 == "forward") {
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);

    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("Stop");
    client.println("</html>");
    client.stop();
    delay(1);
    Serial.print("Stop");
    client.flush();

}
