#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>

#define MDa 5
#define MGa 4
#define MD 0
#define MG 2

#define MQTT_USER "terrain1" // terrain2
#define MQTT_PASS "w87KNd2b" // 56jpwYhr

char *ssid = "PhoenixArdent";
char *password = "pioupiou";
int retries = 5;
DynamicJsonDocument docMqtt(512);
DynamicJsonDocument rdocMqtt(512);
String clientId;
char buffer[512];
String test;

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

int i = 0;

WiFiClient espClient;
char mqtt_server[] = "mqtt-milles.imerir.org"; // mqtt-milles.imerir.org
PubSubClient MQTTclient(espClient);

StaticJsonDocument<200> doc;

const int serialComm = 3;


int ConnexionWifi();
void Wifisetup();
void MQTTsend(int qos, String topic);
void MQTTconnect();
void MQTTbutton(char *donnees);
void MQTTstatus(char *donnees);
void MQTTcallback(char *topic, byte *payload, unsigned int length);
void sendData(String donnees);
void parsedata(char *donnees);
void recvWithEndMarker();
void decodejson();


int ConnexionWifi()
{
  WiFi.begin(ssid, password);
  // tries each second (to let some time to scan WiFi)
  while (WiFi.status() != WL_CONNECTED && i < retries)
  {
    delay(1000);
    i++;
  }
  if (WiFi.status() == WL_CONNECTED)
  { // successfully connected
    Serial.println("connecte");
    return 0;
  }
  Serial.println("erreur connexion");
  return -1;
}

void Wifisetup()
{
  delay(1000);
  WiFi.mode(WIFI_STA);
  int wifitries = 1;
  switch (wifitries)
  {
  case 1: // try the first WiFi
    if (ConnexionWifi() == 0)
    {
      wifitries = 0;
      break;
    }
    else
    {
      delay(1000);
      wifitries++;
    }
  case 2: // fail to connect, reboot
    ESP.restart();
  }
}


void MQTTsend(int qos, String topic)
{
  size_t n = serializeJson(docMqtt, buffer);
  String topsend = "field/robot/" + clientId + "/" + topic;
  Serial.println(topsend);
  const char *topicsend = topsend.c_str();
  Serial.println("buffer:");
  Serial.println(buffer);
  MQTTclient.publish(topicsend, buffer, n); // TODO: false -> n en cas de bug
  docMqtt.clear();
   memset(buffer,0,sizeof buffer);
}



void MQTTconnect() {
  while (!MQTTclient.connected()) {
      Serial.print("Attente  MQTT connection...");
      clientId = "ROBOT3";

    // Attempt to connect
    if (MQTTclient.connect(clientId.c_str(),MQTT_USER,MQTT_PASS)) {
      Serial.println("connected");
      MQTTclient.subscribe("field/robot/ROBOT3/path");
      MQTTclient.subscribe("field/robot/ROBOT3/button"); // TODO: topic subscribe
      MQTTclient.subscribe("field/camera/3/color");
    } else {
      Serial.print("ECHEC, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void MQTTbutton(char *donnees)
{
  if (donnees[1] == '1')
  {
    docMqtt["package"] = true;
  }
  else if (donnees[1] == '0')
  {
    docMqtt["package"] = false;
  }
  MQTTsend(2, "button");
}

void MQTTstatus(char *donnees)
{
  String tempbuff1="";
  String tempbuff2="";
  tempbuff1 = donnees[1];
  tempbuff2 = donnees[2];
  String tosend="";
  tosend += tempbuff1;
  tosend += tempbuff2;
  docMqtt["status"] = tosend.toInt();
  MQTTsend(1, "status");
}


void MQTTcallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message MQTT [");
  Serial.print(topic);
  Serial.print("] ");
  rdocMqtt.clear();
  deserializeJson(rdocMqtt, payload, length);  
  String s=rdocMqtt["color"];
  Serial.println(s);
  decodejson();
}


void sendData(String donnees)
{
  Serial.println(donnees);
}


void parsedata(char *donnees)
{
  if (donnees[0] == '1')
  {
    MQTTbutton(donnees);
  }
  else if (donnees[0] == '2')
  {
    MQTTstatus(donnees);
  }
}

void recvWithEndMarker()
{
  static byte ndx = 0;
  char endMarker = '.';
  char rc;
  if (Serial.available() > 0)
  {
    rc = Serial.read();

    if (rc != endMarker)
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars)
      {
        ndx = numChars - 1;
      }
    }
    else
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      parsedata(receivedChars);
    } 
  }
}


void decodejson(){
  int a=rdocMqtt["size"];
  Serial.println("size:"+ a);
  for (int b=0; b<a; b++){
    String tosend = rdocMqtt[b]["id"]; 
    String tosend2 = rdocMqtt[b]["direction"];
    tosend+= tosend2;
    Serial.println("tosend:");
    Serial.println(tosend);
  }
}


void setup() {
Serial.begin(9600);
  // Conexion WIFI
    Wifisetup();
   Serial.println("Connected");
   MQTTclient.setServer(mqtt_server, 1883);
   MQTTclient.setCallback(MQTTcallback);
   MQTTconnect();
     pinMode(MGa, INPUT);
  pinMode(MDa, INPUT);
  pinMode(MG, INPUT);
  pinMode(MD, INPUT);
}

void loop() {
  /*
  MQTTclient.loop();
  recvWithEndMarker();
  */
  String test;
  sendData("P04");
  sendData("0L");
  sendData("1F");
  sendData("2F");
  sendData("3G");
}
