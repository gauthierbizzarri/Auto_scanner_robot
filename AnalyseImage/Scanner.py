import random
import time
import cv2
import json
import numpy as np
from paho.mqtt import client as mqtt_client

"""
GLOBAL VARS
"""
id_camera = 3  # = Group Number
broker = 'test.mosquitto.org'  # = Broker name
port = 1883  # = Broker port
ID_ROBOT = "ROBOT3"  # = ID of the Robot
topic = "field/robot/{}/button".format(ID_ROBOT)  # = topic to write
username = 'emqx'  # UserName
password = 'public'  # password

Signal_recu = None  # Global var used to store the

"""
MQTT PART 
"""


def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:

            client.subscribe(topic)
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    # Set Connecting Client ID
    client = mqtt_client.Client()
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    topic_to_listen = "field/camera/<id_camera>/scan".format(id_camera)

    def on_message(client, userdata, msg):
        x = json.loads(msg.payload)
        global Signal_recu
        Signal_recu = x
        x = json.loads(msg.payload)
        print("received: ", x, "from topic ", topic_to_listen)

    client.subscribe(topic_to_listen)
    client.on_message = on_message


def on_connect(client, userdata, flags, rc):
    client.subscribe(topic)


"""MAIN FUNCTION"""


def run():
    # Var of the camera Video capture initialized to None to checks if camera is running
    cap = None
    #ETAT 0 , the machine is sleeping and awaiting the signal from the QT Interface
    etat = 0
    client = connect_mqtt()  # Connect to MQTT
    while (True):  # The machine is always running but , it's sleeping
        while etat == 0:
            #Looping and awaiting the payload
            subscribe(client)
            client.loop_start()
            # If we receive a payload from the topic
            if Signal_recu is not None:
                print(Signal_recu)
                # Checking if the payload , converted as a Json corresponds
                if 'robot' in Signal_recu.keys():
                    # Moving to etat = 1 , the system is no longer sleeping , and is prepared to scan the QR Code
                    etat = 1
            etat = 1 ####
        print(etat)
        # If camera is opened , we close it
        if cap and cap.isOpened():
            cap.release()
        # ETAT 1
        if etat == 1:
            # Opening the camera
            cap = cv2.VideoCapture(4)

            # Fixing the camera resolution : (640x480) in order to be more efficient
            cap.set(4, 640)
            cap.set(4, 480)
        # Looping into etat 1 while the QR code Scanned is not corresponding to the payload received
        while (etat == 1):
            # getting the camera stream
            ret, frame = cap.read()
            # Display the stream into a window
            cv2.imshow("QR CODE SCANNER", frame)
            key = cv2.waitKey(1) & 0xFF
            # Method from cv2 to # Detect and decode the qrcode
            qr_decoder = cv2.QRCodeDetector()
            data, bbox, rectified_image = qr_decoder.detectAndDecode(frame)
            # Test if the data is correponding to our ROBOT
            if len(data) > 0 and data == ID_ROBOT:
                start_time = time.time()
                # Moving to etat = 2 , the system is no longer scanning QR Code , and is going to scan colors
                etat = 2
        # Looping into etat 2 while no colors are detected
        while (etat == 2):
            #Getting video stream
            _, imageFrame = cap.read()

            # Convert the imageFrame in
            # BGR(RGB color space) to
            # HSV(hue-saturation-value)
            # color space
            hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

            # Set range for red color and
            # define mask
            red_lower = np.array([136, 87, 111], np.uint8)
            red_upper = np.array([180, 255, 255], np.uint8)
            red_mask = cv2.inRange(hsvFrame, red_lower, red_upper)

            # Set range for green color and
            # define mask
            green_lower = np.array([40, 40, 40], np.uint8)
            green_upper = np.array([70, 255, 255], np.uint8)
            green_mask = cv2.inRange(hsvFrame, green_lower, green_upper)

            # Set range for blue color and
            # define mask
            blue_lower = np.array([100, 150, 0], np.uint8)
            blue_upper = np.array([105, 255, 255], np.uint8)
            blue_mask = cv2.inRange(hsvFrame, blue_lower, blue_upper)

            # Set range for yellow color and
            # define mask
            yellow_lower = np.array([22, 93, 0], np.uint8)
            yellow_upper = np.array([45, 255, 255], np.uint8)
            yellow_mask = cv2.inRange(hsvFrame, yellow_lower, yellow_upper)

            # Morphological Transform, Dilation
            # for each color and bitwise_and operator
            # between imageFrame and mask determines
            # to detect only that particular color
            kernal = np.ones((5, 5), "uint8")

            # For red color
            red_mask = cv2.dilate(red_mask, kernal)
            res_red = cv2.bitwise_and(imageFrame, imageFrame,
                                      mask=red_mask)

            # For green color
            green_mask = cv2.dilate(green_mask, kernal)
            res_green = cv2.bitwise_and(imageFrame, imageFrame,
                                        mask=green_mask)

            # For blue color
            blue_mask = cv2.dilate(blue_mask, kernal)
            res_blue = cv2.bitwise_and(imageFrame, imageFrame,
                                       mask=blue_mask)

            # For yellow color
            yellow_mask = cv2.dilate(yellow_mask, kernal)
            res_yell = cv2.bitwise_and(imageFrame, imageFrame,
                                       mask=yellow_mask)

            # Creating contour to track red color
            contours, hierarchy = cv2.findContours(red_mask,
                                                   cv2.RETR_TREE,
                                                   cv2.CHAIN_APPROX_SIMPLE)
            #Track red color
            for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if (area > 300):
                    x, y, w, h = cv2.boundingRect(contour)
                    #Detect red if only size of w and h > 50
                    if w > 50 and h > 50:
                        imageFrame = cv2.rectangle(imageFrame, (x, y),
                                                   (x + w, y + h),
                                                   (0, 0, 255), 2)
                        #Display a red text to inform about red color
                        cv2.putText(imageFrame, "Red Colour", (x, y),
                                    cv2.FONT_HERSHEY_SIMPLEX, 1.0,
                                    (0, 0, 255))
                        #Publishing response as  a Json to the topic
                        data_set = {"robot": data, "color": "red"}
                        json_dump = json.dumps(data_set)
                        result = client.publish(topic, json_dump)
                        status = result[0]
                        if status == 0:
                            print(f"Send {json_dump}to topic `{topic}`")
                            # Going back to etat 0 awaiting a new order
                            etat = 0

                        else:
                            print(f"Failed to send message to topic {topic}")

            # Creating contour to track green color
            contours, hierarchy = cv2.findContours(green_mask,
                                                   cv2.RETR_TREE,
                                                   cv2.CHAIN_APPROX_SIMPLE)
            # Track green color
            for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if (area > 300):
                    x, y, w, h = cv2.boundingRect(contour)
                    # Detect green if only size of w and h > 50
                    if w > 50 and h > 50:
                        imageFrame = cv2.rectangle(imageFrame, (x, y),
                                                   (x + w, y + h),
                                                   (0, 255, 0), 2)
                        # Display a green text to inform about red color
                        cv2.putText(imageFrame, "Green Colour", (x, y),
                                    cv2.FONT_HERSHEY_SIMPLEX,
                                    1.0, (0, 255, 0))
                        # Publishing response as  a Json to the topic
                        data_set = {"robot": data, "color": "green"}
                        json_dump = json.dumps(data_set)
                        result = client.publish(topic, json_dump)
                        status = result[0]
                        if status == 0:
                            print(f"Send {json_dump}to topic `{topic}`")
                            # Going back to etat 0 awaiting a new order
                            etat = 0

                        else:
                            print(f"Failed to send message to topic {topic}")

            # Creating contour to track blue color
            contours, hierarchy = cv2.findContours(blue_mask,
                                                   cv2.RETR_TREE,
                                                   cv2.CHAIN_APPROX_SIMPLE)
            # Track blue color
            for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if (area > 300):
                    x, y, w, h = cv2.boundingRect(contour)
                    # Detect blue if only size of w and h > 50
                    if w > 50 and h > 50:
                        imageFrame = cv2.rectangle(imageFrame, (x, y),
                                                   (x + w, y + h),
                                                   (255, 0, 0), 2)

                        cv2.putText(imageFrame, "Blue Colour", (x, y),
                                    cv2.FONT_HERSHEY_SIMPLEX,
                                    1.0, (255, 0, 0))
                        # Publishing response as  a Json to the topic
                        data_set = {"robot": data, "color": "blue"}
                        json_dump = json.dumps(data_set)
                        result = client.publish(topic, json_dump)
                        status = result[0]
                        # Going back to etat 0 awaiting a new order
                        if status == 0:
                            print(f"Send {json_dump}to topic `{topic}`")
                            # Retrour à l'état  0
                            etat = 0

                        else:
                            print(f"Failed to send message to topic {topic}")
            # Creating contour to track yellow color
            contours, hierarchy = cv2.findContours(yellow_mask,
                                                   cv2.RETR_TREE,
                                                   cv2.CHAIN_APPROX_SIMPLE)
            # Track yellow color
            for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if (area > 300):
                    x, y, w, h = cv2.boundingRect(contour)
                    # Detect blue if only size of w and h > 50
                    if w > 50 and h > 50:
                        imageFrame = cv2.rectangle(imageFrame, (x, y),
                                                   (x + w, y + h),
                                                   (0, 255, 255), 2)

                        cv2.putText(imageFrame, "Yellow Colour", (x, y),
                                    cv2.FONT_HERSHEY_SIMPLEX, 1.0,
                                    (0, 255, 255))
                        # Publishing response as  a Json to the topic
                        data_set = {"robot": data, "color": "yellow"}
                        json_dump = json.dumps(data_set)
                        result = client.publish(topic, json_dump)
                        status = result[0]
                        if status == 0:
                            print(f"Send {json_dump}to topic `{topic}`")
                            # Going back to etat 0 awaiting a new order
                            etat = 0

                        else:
                            print(f"Failed to send message to topic {topic}")
            if etat == 0:
                print("--- %s seconds ---" % (time.time() - start_time))
            # Program Termination
            cv2.imshow("Multiple Color Detection in Real-TIme", imageFrame)
            key = cv2.waitKey(1) & 0xFF


if __name__ == '__main__':
    run()
