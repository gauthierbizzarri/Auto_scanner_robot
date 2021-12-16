# An Amazon En Mieux Scanner    🔍
### A Python3 🐍 &OpenCv app 

![N|Solid](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT3D3aBeLr69N4cnxkqpVyEFExJ6czj-RqlIw&usqp=CAU)

# *The Goal :*
The main goal to this app is to responde to the following situation : 
*"When a signal is received from a topic, you have to wait to scan a signal corresponding QrCode, and if it is correct , you must send a signal in response"*

# 0/ Preliminaries
Let's understand the first lines , the paramaters , each one of them are explained with a comment 
```python
id_camera = 3  # = Group Number
broker = 'mqtt-milles.imerir.org'
port = 1883  # = Broker port
ID_ROBOT = "ROBOT3"  # = ID of the Robot
topic_to_write = "field/camera/{}/color".format(id_camera)
topic_to_listen = "field/camera/3/scan"
username = "terrain1"
password = "w87KNd2b"

Signal_recu = None  # Global var used to store the
rayon_perce = 90    #minimum size to detect
lum = 30 #parameter to handle luminosity
```
#  Understand the functionment 
![Screenshot](etat_machine.jpg)
First lets see the **MQTT part :** 
```python
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(topic_to_listen)


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    etat = 0
    x = json.loads(msg.payload)
    global Signal_recu
    Signal_recu = x
    x = json.loads(msg.payload)
    # If we receive a payload from the topic
    if Signal_recu is not None:
        print("received: ", x, "from:{}".format(topic_to_listen))
        # Checking if the payload , converted as a Json corresponds
        if 'robot' in Signal_recu.keys() and Signal_recu['robot'] == ID_ROBOT:
            etat = 1
            # Moving to etat = 1 , the system is no longer sleeping , and is prepared to scan the QR Code
    if etat == 0:
        pass
    if etat == 1:
        run(etat)


client = mqtt.Client()
client.on_connect = on_connect
client.username_pw_set(username, password)
client.on_message = on_message
client.connect(broker, 1883)
client.loop_forever()
```
Will listen to the *topic_to_listen* and convert the payload to a Json , this Json will be stored into Signal_recu var and will also be printed


## **Main function**
```python
run()
```
*You may understand the entire code by reading the comments*

