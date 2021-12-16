#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>

#define MDa 5 // pins used by the motors
#define MGa 4
#define MD 0
#define MG 2

#define MQTT_USER "terrain1" // terrain2
#define MQTT_PASS "w87KNd2b" // 56jpwYhr

String ssid = "IMERIR_IoT";        // IMERIR_IoT
String password = "kohWoong5oox";  // kohWoong5oox
int retries = 5;                   // number of retries (wifi connection)
int i = 0;


DynamicJsonDocument docMqtt(5000); // just a bunch of big arrays
DynamicJsonDocument rdocMqtt(5000);
StaticJsonDocument<5000> doc;
char buffer[5000];

String clientId;
String test;
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;


WiFiClient espClient;
char mqtt_server[] = "mqtt-milles.imerir.org"; // mqtt-milles.imerir.org
PubSubClient MQTTclient(espClient);

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

int ConnexionWifi() // connect to the wifi
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
    return 0;
  }
  return -1;
}

void Wifisetup() // try to connect to the wifi hotspot (many hotspot possible)
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

void MQTTsend(int qos, String topic) // send data to the broker
{
  serializeJson(docMqtt, buffer);
  String topsend = "field/robot/" + clientId + "/" + topic;
  const char *topicsend = topsend.c_str();
  MQTTclient.publish(topicsend, buffer, false);
  docMqtt.clear();
  memset(buffer, 0, sizeof buffer);
}

void MQTTconnect()
{ // connect to the broker and subscribe
  while (!MQTTclient.connected())
  {
    clientId = "ROBOT3";
    // Attempt to connect
    if (MQTTclient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS))
    {
      MQTTclient.subscribe("field/robot/ROBOT3/path");
      // MQTTclient.subscribe("field/robot/ROBOT3/status");
      // MQTTclient.subscribe("field/robot/ROBOT3/button");
      // MQTTclient.subscribe("field/camera/3/color");
    }
    else
    {
      delay(5000);
    }
  }
}

void MQTTbutton(char *donnees) // publish to the broker the state of the button (if the ball in on the robot)
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

void MQTTstatus(char *donnees) // publish to the broker the curent position of the robot (up to pos 99)
{
  String tempbuff1 = "";
  String tempbuff2 = "";
  tempbuff1 = donnees[1];
  tempbuff2 = donnees[2];
  String tosend = "";
  tosend += tempbuff1;
  tosend += tempbuff2;
  docMqtt["status"] = tosend.toInt();
  MQTTsend(1, "status");
}

void MQTTcallback(char *topic, byte *payload, unsigned int length)
{ // function called when data is recieved from the broker
  rdocMqtt.clear();
  deserializeJson(rdocMqtt, payload, length);
  decodejson();
}

void sendData(String donnees) // send data to the serial port (used for debug)
{
  Serial.println(donnees);
}

void parsedata(char *donnees) // check the data from the serial port and start publishing
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

void recvWithEndMarker() // recieve data from the serial port (if there is some)
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

void decodejson()
{ // decode the json comming from the broker and send it to the serial port
  int a = rdocMqtt["size"];
  String s = String(a);
  if (s != "0")
  {
    Serial.println("P" + s);
  }
  for (int b = 0; b < a; b++)
  {
    int t = rdocMqtt["data"][b]["id"];
    String tosend = String(t);
    String tosend2 = rdocMqtt["data"][b]["direction"];
    tosend += tosend2;
    Serial.println(tosend);
  }
}

void setup()
{
  MQTTclient.setBufferSize(5000);
  Serial.begin(9600);
  Wifisetup();
  MQTTclient.setServer(mqtt_server, 1883);
  MQTTclient.setCallback(MQTTcallback);
  MQTTconnect();
  pinMode(MGa, INPUT);
  pinMode(MDa, INPUT);
  pinMode(MG, INPUT);
  pinMode(MD, INPUT);
}

void loop()
{
  if (!MQTTclient.connected())
  {
    MQTTconnect();
  }
  MQTTclient.loop();
  recvWithEndMarker();
}
