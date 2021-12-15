#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#define MDa 5
#define MGa 4
#define MD 0
#define MG 2


#define MQTT_USER "" //terrain2  
#define MQTT_PASS "" //56jpwYhr  


char *ssid = "PhoenixArdent";
char *password = "pioupiou";
int retries = 5;
DynamicJsonDocument docMqtt(512);
String clientId;
char buffer[512];

int i = 0;

WiFiClient espClient;
char mqtt_server[] = "test.mosquitto.org";  //mqtt-milles.imerir.org
PubSubClient MQTTclient(espClient);

StaticJsonDocument<200> jsonBuffer;




int ConnexionWifi();
void Wifisetup();
void MQTTsend(int qos);
void MQTTconnect();
void MQTTbutton(bool state);
void MQTTstatus(int position);
void JsonDecode();
void MQTTcallback(char* topic, byte* payload, unsigned int length);







void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wifisetup();;
  MQTTclient.setServer(mqtt_server, 1883);
  MQTTconnect();
  MQTTclient.setCallback(MQTTcallback);
  pinMode(MGa, INPUT);
  pinMode(MDa, INPUT);
  pinMode(MG, INPUT);
  pinMode(MD, INPUT);
}

void MQTTbutton(bool state){
  state=true;
  if (state){
docMqtt["package"]="true";
  }
  else{
    docMqtt["package"]="false";
  }
MQTTsend(2);
}

void MQTTstatus(int position){
  docMqtt["status"]=position;
  MQTTsend(1);
}


void MQTTsend(int qos) {
  //docMqtt["temperature"] = "33";  // TODO: find a way to add data in the docMqtt (global variable?)
  //docMqtt["humidity"] = "40";
  size_t n = serializeJson(docMqtt, buffer);
  String topsend= "field/robot/"+ clientId + "/button";
  const char* topicsend = topsend.c_str();
  MQTTclient.publish(topicsend, buffer, n);  // TODO: topic publish
  docMqtt.clear();
}

void MQTTconnect() {
  while (!MQTTclient.connected()) {
    Serial.print("Attente  MQTT connection...");
    clientId = "ROBOT3";
    //clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (MQTTclient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("connected");
      String topsend= "field/robot/"+ clientId + "/path";
      const char* topicsend = topsend.c_str();
      MQTTclient.subscribe(topicsend,2);  // TODO: topic subscribe
    } else {
      Serial.print("ECHEC, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTcallback(char* topic, byte* payload, unsigned int length) {


  Serial.print("Message MQTT [");
  Serial.print(topic);
  Serial.print("] ");

  payload[length] = '\0';
  String s = String((char*)payload);

 Serial.println("message reçu : "+s);
}


void loop() {
  static uint32_t  lastTimeMqtt= 0;
  MQTTclient.loop();
  if (millis() - lastTimeMqtt >= 10000)  // toutes les 20 secondes
   {
     lastTimeMqtt = millis();
     MQTTbutton(1);
     Serial.println("sended");
   }
}


int ConnexionWifi() {
  WiFi.begin(ssid, password);
  // tries each second (to let some time to scan WiFi)
  while (WiFi.status() != WL_CONNECTED && i < retries) {
    delay(1000);
    i++;
  }
  if (WiFi.status() == WL_CONNECTED) {  // successfully connected
    Serial.println("connecté");
    return 0;
  }
  Serial.println("erreur connexion");
  return -1;
}

void Wifisetup() {
  delay(1000);
  WiFi.mode(WIFI_STA);
  int wifitries = 1;
  switch (wifitries) {
    case 1:  //try the first WiFi
      if (ConnexionWifi() == 0) {
        wifitries = 0;
        break;
      } else {
        delay(1000);
        wifitries++;
      }
    case 2:  // fail to connect, reboot
      ESP.restart();
  }
}
