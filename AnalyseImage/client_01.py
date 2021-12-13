import random
import time
import sys
import time
import cv2
import imutils
import numpy as np
from paho.mqtt import client as mqtt_client


broker = 'broker.emqx.io'
port = 1883
topic_QR_ = "python/mqtt"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = 'emqx'
password = 'public'

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


def publish(client,message_recu):
    message_recu = message_recu
    msg = f"messages: {message_recu}"
    result = client.publish(topic_QR_, msg)
    # result: [0, 1]
    status = result[0]
    if status == 0:
        print(f"Send `{msg}` to topic `{topic_QR_}`")
    else:
        print(f"Failed to send message to topic {topic}")


def run():
    client = connect_mqtt()
    client.loop_start()
    while True :
        status , message = QR()
        if status:
            publish(client,message)



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
    time.sleep(1)

    while True:
        ret, frame = cap.read()
        cv2.imshow("frame", frame)
        key = cv2.waitKey(1) & 0xFF
        
        
        #example code from google TODO: link
        qr_decoder = cv2.QRCodeDetector()
    
        # Detect and decode the qrcode
        data, bbox, rectified_image = qr_decoder.detectAndDecode(frame)
        if len(data)>0:
            print("Decoded Data : {}".format(data))
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