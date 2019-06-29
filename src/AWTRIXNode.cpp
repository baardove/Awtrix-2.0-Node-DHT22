#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "node-conf.h"

#include "DHTesp.h"


DHTesp dht;
float humidity = 0;
float temperature =0;



WiFiClient espClient;
PubSubClient client(espClient);
bool updating = false;
unsigned long previousMillis = 0;


void sendToAwtrixS(String name, String text, int icon) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = name;
  JsonObject& command = root.createNestedObject("command");
  command["icon"] = icon;
  command["text"] = text;

  String JS;
  root.printTo(JS);
  client.publish("awtrixnode", JS.c_str());
  Serial.println(JS.c_str());
}

//modify the code here
//You can send a text an a IconID from AWTRIXER


void fetchdata() {


  delay(dht.getMinimumSamplingPeriod());

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

}


void doJob() {

  String sname;
  String sbuf;
  char * cbuf;

  sbuf= "";

  fetchdata();



// Temperature

  sbuf= String(temperature);
  sendToAwtrixS(nodenameT, sbuf, iconIDT);

// Humidity

  sbuf= String(humidity);
  sendToAwtrixS(nodenameH, sbuf, iconIDH);


}



void reconnect() {

  while (!client.connected()) {
    String clientId = "AWTRIXnode-";
    clientId += String(random(0xffff), HEX);
    if (!client.connect(clientId.c_str())) {
      delay(5000);
    }
  }

}


void setup() {

  Serial.begin(115200);
  Serial.println();
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(awtrix_server, 7001);
  ArduinoOTA.begin();

}

void loop() {

  ArduinoOTA.handle();
  if (!updating) {
    if (!client.connected()) {
      reconnect();
    } else {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        doJob();
      }
    }
    client.loop();
  }

}
