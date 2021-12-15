import paho.mqtt.client as mqtt
import json
"""USED TO PUBLISH A JSON TO ACTIVATE CAMERA"""
id_camera = 3  # = Group Number
# broker = 'test.mosquitto.org'  # = Broker name
broker = 'mqtt-milles.imerir.org'
port = 1883  # = Broker port
ID_ROBOT = "ROBOT3"  # = ID of the Robot
#LISTEN F
username = "terrain1"
password = "w87KNd2b"


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.username_pw_set(username, password)
client.on_message = on_message
client.connect(broker, 1883)
data_set = {"robot": "ROBOT3", }
json_dump = json.dumps(data_set)
client.publish("field/camera/3/scan", json_dump)