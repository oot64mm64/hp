#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <HeatPump.h>

#ifndef STASSID
#define STASSID "shasta-2.4"
#define STAPSK "drinktoldmixturemade"
#endif

int port = 8888;  //Port number
WiFiServer server(port);
const char* ssid = STASSID;
const char* password = STAPSK;

//variabls for blinking an LED with Millis
unsigned long previousMillis = 0;  // will store last time LED was updated
int interval = 100; // initial blink rate
const int blink_count = 10; //how many times to blink before changing rate
int count = 0; //counter for number of blinks since change of rate
int ledState = LOW;  // ledState used to set the LED
String input = "A";


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH); //Turn LED OFF
// OTA CODE BELOW // 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting..."); //debug info on serial port
    delay(5000);
    ESP.restart();
  }
  Serial.println("");                             //debug info on serial port
  Serial.print("Connected to ");                  //debug info on serial port
  Serial.println(ssid);                           //debug info on serial port
  Serial.print("IP address: ");                   //debug info on serial port
  Serial.println(WiFi.localIP());                 //debug info on serial port
  server.begin();                                 //debug info on serial port
  Serial.print("Open Telnet and connect to IP:"); //debug info on serial port
  Serial.print(WiFi.localIP());                   //debug info on serial port
  Serial.print(" on port ");                      //debug info on serial port
  Serial.println(port);                           //debug info on serial port
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
// OTA CODE ABOVE //
}

void loop() {
  ArduinoOTA.handle();  //OTA COMMAND

  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())                //debug info on serial port
    {                                     //debug info on serial port
      Serial.println("Client Connected"); //debug info on serial port
    }                                     //debug info on serial port
    
    while(client.connected()){    
//    digitalWrite(LED_BUILTIN, LOW); //Turn LED ON  
      while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read());    //debug info on serial port
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }

    }
    client.stop();
//  digitalWrite(LED_BUILTIN, HIGH); //Turn LED OFF
    Serial.println("Client disconnected");    
  }


}
