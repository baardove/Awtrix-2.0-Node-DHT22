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
int counter=0;
//int iconID=0;


WiFiClient espClient;
PubSubClient client(espClient);
bool updating = false;
unsigned long previousMillis = 0;



void sendToAwtrix(char * text, int icon) {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = nodename;
  JsonObject& command = root.createNestedObject("command");
  command["icon"] = icon;
  command["text"] = text;
  String JS;
  root.printTo(JS);
  client.publish("awtrixnode", JS.c_str());
  Serial.println(JS.c_str());
}

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

void charToString(char S[], String &D)
{

 String rc(S);
 D = rc;

}

void charToStringL(const char S[], String &D)
{
    byte at = 0;
    const char *p = S;
    D = "";

    while (*p++) {
      D.concat(S[at++]);
      }
}

void fetchdata() {


  delay(dht.getMinimumSamplingPeriod());

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

/**
  Serial.println("");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("%\t");
  Serial.print(temperature, 1);
  Serial.print(" C\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);

  Serial.println("");
**/
}


void doJob() {

  String sname;
  String sbuf;
  char * cbuf;

  sbuf= "";

  fetchdata();


  sname="Temp";

  // sbuf+=

//  dtostrf(temperature,2,1,cbuf);

  // sbuf+= cbuf;
//  charToString(cbuf, sbuf);
// strncpy(message, html.c_str(), sizeof (message));

  sbuf= String(temperature);

  Serial.print("temp: ");
  Serial.println(temperature);


  Serial.print("sbuf: ");
  Serial.println(sbuf);

  sendToAwtrixS(sname,sbuf,  2369);

  counter++;
  iconID++;

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


  Serial.println("\n\nStatus\tHumidity (%)\tTemperature (C)\tHeatIndex (C)");

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
