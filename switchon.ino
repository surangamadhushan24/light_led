
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char* ssid = "";
const char* password = "";
WiFiClient client;
HTTPClient http;


const char* host = "http://192.168.8.110/iot1/getdata.php";


const int bulb1Pin = D5;
const int bulb2Pin = D8;

void setup() {
  pinMode(bulb1Pin, OUTPUT);
  pinMode(bulb2Pin, OUTPUT);
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi connection failed");
  }
}

void loop() {
  http.begin(client, host);  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.GET();  
  String payload = http.getString(); 

  
  Serial.print("Payload: ");
  Serial.println(payload);


  if (payload == "11") {  
    digitalWrite(bulb1Pin, HIGH);
    digitalWrite(bulb2Pin, HIGH);
  } else if (payload == "10") {  
    digitalWrite(bulb1Pin, HIGH);
    digitalWrite(bulb2Pin, LOW);
  } else if (payload == "01") {  
    digitalWrite(bulb1Pin, LOW);
    digitalWrite(bulb2Pin, HIGH);
  } else if (payload == "00") {  
    digitalWrite(bulb1Pin, LOW);
    digitalWrite(bulb2Pin, LOW);
  }

  delay(500);  
  http.end();  
}



