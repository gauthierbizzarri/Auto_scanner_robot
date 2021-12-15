import random
import time
import cv2
import json
import numpy as np
from paho.mqtt import client as mqtt

"""
GLOBAL VARS
"""
id_camera = 3  # = Group Number
broker = 'mqtt-milles.imerir.org'
port = 1883  # = Broker port
ID_ROBOT = "ROBOT3"  # = ID of the Robot
topic_to_write = "field/camera/{}/color".format(id_camera)
topic_to_listen = "field/camera/3/scan"
username = "terrain1"
password = "w87KNd2b"

Signal_recu = None  # Global var used to store the

"""
MQTT PART 
"""


def run(etat):
    # Var of the camera Video capture initialized to None to checks if camera is running
    cap = None
    # If camera is opened , we close it
    if cap and cap.isOpened():
        cap.release()
        time.sleep(1)
    # ETAT 1
    if etat == 1:
        # Opening the camera
        cap = cv2.VideoCapture(4)

        # Fixing the camera resolution : (640x480) in order to be more efficient
        cap.set(4, 800)
        cap.set(4, 600)
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
        # Getting video stream
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
        green_lower = np.array([55, 40, 40], np.uint8)
        green_upper = np.array([70, 255, 255], np.uint8)
        green_mask = cv2.inRange(hsvFrame, green_lower, green_upper)

        # Set range for blue color and
        # define mask
        blue_lower = np.array([100, 150, 0], np.uint8)
        blue_upper = np.array([105, 255, 255], np.uint8)
        blue_mask = cv2.inRange(hsvFrame, blue_lower, blue_upper)

        # Set range for yellow color and
        # define mask
        yellow_lower = np.array([22, 170, 0], np.uint8)
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
        # Track red color
        for pic, contour in enumerate(contours):
            area = cv2.contourArea(contour)
            if (area > 300):
                x, y, w, h = cv2.boundingRect(contour)
                # Detect red if only size of w and h > 50
                if w > 50 and h > 50:
                    imageFrame = cv2.rectangle(imageFrame, (x, y),
                                               (x + w, y + h),
                                               (0, 0, 255), 2)
                    # Display a red text to inform about red color
                    cv2.putText(imageFrame, "Red Colour", (x, y),
                                cv2.FONT_HERSHEY_SIMPLEX, 1.0,
                                (0, 0, 255))
                    # Publishing response as  a Json to the topic
                    data_set = {"robot": data, "color": "red"}
                    json_dump = json.dumps(data_set)
                    result = client.publish(topic_to_write, json_dump)
                    status = result[0]
                    if status == 0:
                        print(f"Send {json_dump}to topic `{topic_to_write}`")
                        # Going back to etat 0 awaiting a new order
                        etat = 0

                    else:
                        print(f"Failed to send message to topic {topic_to_write}")

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
                    result = client.publish(topic_to_write, json_dump)
                    status = result[0]
                    if status == 0:
                        print(f"Send {json_dump}to topic `{topic_to_write}`")
                        # Going back to etat 0 awaiting a new order
                        etat = 0

                    else:
                        print(f"Failed to send message to topic {topic_to_write}")

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
                    result = client.publish(topic_to_write, json_dump)
                    status = result[0]
                    # Going back to etat 0 awaiting a new order
                    if status == 0:
                        print(f"Send {json_dump}to topic `{topic_to_write}`")
                        # Retrour à l'état  0
                        etat = 0

                    else:
                        print(f"Failed to send message to topic {topic_to_write}")
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
                    result = client.publish(topic_to_write, json_dump)
                    status = result[0]
                    if status == 0:
                        print(f"Send {json_dump}to topic `{topic_to_write}`")
                        # Going back to etat 0 awaiting a new order
                        etat = 0

                    else:
                        print(f"Failed to send message to topic {topic_to_write}")
        # Program Termination
        cv2.imshow("Color Detection", imageFrame)
        cv2.moveWindow("Color Detection", 800, -20)
        key = cv2.waitKey(1) & 0xFF


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
