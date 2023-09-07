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

//Vars for WiFi connect to AP and be a TCP server stuff
int port = 8888;  //Port number
WiFiServer server(port);
const char* ssid = STASSID;
const char* password = STAPSK;

//Vars for command handling
char clientInput;
const char clientCommand = 'M';
const char clientRequest = 'R';
int interval = 100; // was for blink rate, now just a dummy value for a clientRequest command

//Vars for controlling Heat Pump
heatpumpSettings settings = { // Variable for settings
  "OFF",  /* ON/OFF */
  "FAN", /* HEAT/COOL/FAN/DRY/AUTO */
  26,    /* Between 16 and 31 */
  "4",   /* Fan speed: 1-4, AUTO, or QUIET */
  "3",   /* Air direction (vertical): 1-5, SWING, or AUTO */
  "|"    /* Air direction (horizontal): <<, <, |, >, >>, <>, or SWING */
};

HeatPump hp;

void setup() {
// OTA CODE BELOW // 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  server.begin();                                 
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
//    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
//    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
//    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
//    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
//      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
//      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
//      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
//      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
//      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
// OTA CODE ABOVE //

// HEAT PUMP CODE BELOW //

// HEAT PUMP CODE ABOVE //
}

void loop() {
  ArduinoOTA.handle();  //OTA COMMAND

  WiFiClient client = server.available();
  if (client) {
//    if(client.connected())                //debug info on serial port
//    {                                     //debug info on serial port
//      Serial.println("Client Connected"); //debug info on serial port
//    }                                     //debug info on serial port
    
    while(client.connected()){    
      while(client.available()>0){
        // read data from the connected client
        clientInput=client.read();
//        Serial.println(clientInput);
        //Set Blink Rate
//        if(input == clientCommand){
          //Get num ms following command char
//          interval=client.readString().toInt();
//          Serial.println(interval);
//          client.print(interval);
//        }
        //request for Blink Rate
        if(clientInput == clientRequest){
          client.print(settings);
        }
      }
      //Send Data to connected client
//      while(Serial.available()>0)
//      {
//        client.write(Serial.read());
//      }

      }
    }
    client.stop();
//    Serial.println("Client disconnected");
        
}
