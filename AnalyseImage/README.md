# An Amazon En Mieux Scanner    🔍
### A Python3 🐍 &OpenCv app 

![N|Solid](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT3D3aBeLr69N4cnxkqpVyEFExJ6czj-RqlIw&usqp=CAU)

# *The Goal :*
The main goal to this app is to responde to the following situation : 
*"When a signal is received from a topic, you have to wait to scan a signal corresponding QrCode, and if it is correct , you must send a signal in response"*

# 0/ Preliminaries
Let's understand the first lines , the paramaters , each one of them are explained with a comment 
```python
id_camera = ...             # = Id of the camera , defined by the staff
broker = ...                # = Name of the broker , defined by the host of the server : IMERIR
port = ...                  # = Port of the broker , defined by the host of the server : IMERIR
ID_ROBOT = ...              # = Id of the robot , defined by the staff
topic = ...
username = ...
password = ...
Signal_recu = ...
```
#  Understand the functionment 
![Screenshot](etat_machine.jpg)
First lets see the **MQTT part :** 
```python
connect_mqtt():
```
Will simply connect the user to the broker

```python
subscribe():
```
Will listen to the *topic_to_list* and convert the payload to a Json , this Json will be sotred into Signal_recu var and will also be printed

```python
on_connect()
```
Will automatically launch *subscribe()*

## **Main function**
```python
run()
```
*You may understand the entire code by reading the comments*

