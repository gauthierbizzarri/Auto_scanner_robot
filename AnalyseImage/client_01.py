import random
import time
import sys
import time
import cv2
import imutils
import json
import numpy as np
from paho.mqtt import client as mqtt_client
import color_detection


id_camera = 3 ##num groupe

broker = 'broker.emqx.io'

port = 1883

# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = 'emqx'
password = 'public'

ID_ROBOT = "ROBOT3"

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def publish(client,action=None,id_robot=None):
    while(True):
        if action =="QR_CODE":
            topic = "field/camera/{}/scan".format(id_camera)
            result = client.publish(topic, id_robot)
            status = result[0]
            if status == 0:
                data_set = {"robot": id_robot}
                json_dump = json.dumps(data_set)
                print(f"Send {json_dump}to topic `{topic_QR_}`")
            else:
                print(f"Failed to send message to topic {topic_QR_}")


def run():
    client = connect_mqtt()
    client.loop_start()
    response = []
    cap = cv2.VideoCapture(4)
    cap.set(4, 640)
    cap.set(4, 480)
    while(True):
        #time.sleep(1)
        ret, frame = cap.read()
        cv2.imshow("frame", frame)
        key = cv2.waitKey(1) & 0xFF
        
        
        #example code from google TODO: link
        qr_decoder = cv2.QRCodeDetector()

        # Detect and decode the qrcode
        data, bbox, rectified_image = qr_decoder.detectAndDecode(frame)
        if len(data)>0 and data ==ID_ROBOT:
           topic = "field/camera/{}/scan".format(id_camera)
           data_set = {"robot": data}
           json_dump = json.dumps(data_set)
           result = client.publish(topic, json_dump)
           status = result[0]
           if status == 0:
                print(f"Send {json_dump}to topic `{topic}`")


    # Display barcode and QR code location
def display(im, bbox):
    n = len(bbox)
    for j in range(n):
        cv2.line(im, tuple(bbox[j][0]), tuple(bbox[ (j+1) % n][0]), (255,0,0), 3)
    # Display results
    cv2.imshow("Results", im)

def QR():
    response = []
    cap = cv2.VideoCapture(4)
    cap.set(3, 640)
    cap.set(4, 480)
    #time.sleep(1)
    ret, frame = cap.read()
    cv2.imshow("frame", frame)
    key = cv2.waitKey(1) & 0xFF
    
    
    #example code from google TODO: link
    qr_decoder = cv2.QRCodeDetector()

    # Detect and decode the qrcode
    data, bbox, rectified_image = qr_decoder.detectAndDecode(frame)
    if len(data)>0 and data ==ID_ROBOT:
        response.append(True)
        response.append(data)
        return response
        #rectified_image = np.uint8(rectified_image);
        #cv2.imshow("Rectified QRCode", rectified_image);
    else:
        pass
    if cv2.waitKey(10) & 0xFF == ord('q'):
        cap.release()
        cv2.destroyAllWindows()


if __name__ == '__main__':
    run()