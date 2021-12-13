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
        #TESTING IF THERE IS A SCANNED DATA AND IF THE DATA IS CORRECT 
        if len(data)>0 and data ==ID_ROBOT:
           topic = "field/camera/{}/scan".format(id_camera)
           data_set = {"robot": data}
           json_dump = json.dumps(data_set)
           result = client.publish(topic, json_dump)
           status = result[0]
           proceed_color_detection=False
           if status == 0:
                print(f"Send {json_dump}to topic `{topic}`")
                proceed_color_detection=True
           if proceed_color_detection:
            # Start a while loop
            while(1):
                  
                # Reading the video from the
                # webcam in image frames
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
                blue_upper = np.array([140, 255, 255], np.uint8)
                blue_mask = cv2.inRange(hsvFrame, blue_lower, blue_upper)
                
                #yellow
                yellow_lower = np.array([22, 93, 0],np.uint8)
                yellow_upper = np.array([45, 255, 255],np.uint8)
                yellow_mask = cv2.inRange(hsvFrame, yellow_lower, yellow_upper)
              
                # Morphological Transform, Dilation
                # for each color and bitwise_and operator
                # between imageFrame and mask determines
                # to detect only that particular color
                kernal = np.ones((5, 5), "uint8")
                  
                # For red color
                red_mask = cv2.dilate(red_mask, kernal)
                res_red = cv2.bitwise_and(imageFrame, imageFrame, 
                                          mask = red_mask)
                  
                # For green color
                green_mask = cv2.dilate(green_mask, kernal)
                res_green = cv2.bitwise_and(imageFrame, imageFrame,
                                            mask = green_mask)
                  
                # For blue color
                blue_mask = cv2.dilate(blue_mask, kernal)
                res_blue = cv2.bitwise_and(imageFrame, imageFrame,
                                           mask = blue_mask)

                 # For yellow color
                yellow_mask = cv2.dilate(yellow_mask, kernal)
                res_yell = cv2.bitwise_and(imageFrame, imageFrame,
                                           mask = yellow_mask)



               
                # Creating contour to track red color
                contours, hierarchy = cv2.findContours(red_mask,
                                                       cv2.RETR_TREE,
                                                       cv2.CHAIN_APPROX_SIMPLE)

                response = []
                  
                for pic, contour in enumerate(contours):
                    area = cv2.contourArea(contour)
                    if(area > 300):
                        x, y, w, h = cv2.boundingRect(contour)
                        if w > 100 and h > 100 : 
                            imageFrame = cv2.rectangle(imageFrame, (x, y), 
                                                       (x + w, y + h), 
                                                       (0, 0, 255), 2)
                              
                            cv2.putText(imageFrame, "Red Colour", (x, y),
                                        cv2.FONT_HERSHEY_SIMPLEX, 1.0,
                                        (0, 0, 255))
                            response.append(True)
                            response.append("RED")
              
                # Creating contour to track green color
                contours, hierarchy = cv2.findContours(green_mask,
                                                       cv2.RETR_TREE,
                                                       cv2.CHAIN_APPROX_SIMPLE)
                  
                for pic, contour in enumerate(contours):
                    area = cv2.contourArea(contour)
                    if(area > 300):
                        x, y, w, h = cv2.boundingRect(contour)
                        if w > 100 and h > 100 : 
                            imageFrame = cv2.rectangle(imageFrame, (x, y), 
                                                   (x + w, y + h),
                                                   (0, 255, 0), 2)
                          
                            cv2.putText(imageFrame, "Green Colour", (x, y),
                                    cv2.FONT_HERSHEY_SIMPLEX, 
                                    1.0, (0, 255, 0))
                            response.append(True)
                            response.append("GREEN")
              
                # Creating contour to track blue color
                contours, hierarchy = cv2.findContours(blue_mask,
                                                       cv2.RETR_TREE,
                                                       cv2.CHAIN_APPROX_SIMPLE)
                for pic, contour in enumerate(contours):
                    area = cv2.contourArea(contour)
                    if(area > 300):
                        x, y, w, h = cv2.boundingRect(contour)
                        if w > 100 and h > 100 : 
                            imageFrame = cv2.rectangle(imageFrame, (x, y),
                                                       (x + w, y + h),
                                                       (255, 0, 0), 2)
                              
                            cv2.putText(imageFrame, "Blue Colour", (x, y),
                                        cv2.FONT_HERSHEY_SIMPLEX,
                                        1.0, (255, 0, 0))
                            response.append(True)
                            response.append("BLUE")

                # Creating contour to track yellow color
                contours, hierarchy = cv2.findContours(yellow_mask,
                                                       cv2.RETR_TREE,
                                                       cv2.CHAIN_APPROX_SIMPLE)
                  
                for pic, contour in enumerate(contours):
                    area = cv2.contourArea(contour)
                    if(area > 300):
                        x, y, w, h = cv2.boundingRect(contour)
                        if w > 100 and h > 100 : 
                            imageFrame = cv2.rectangle(imageFrame, (x, y), 
                                                       (x + w, y + h), 
                                                       (0, 255, 255), 2)
                              
                            cv2.putText(imageFrame, "Yellow Colour", (x, y),
                                        cv2.FONT_HERSHEY_SIMPLEX, 1.0,
                                        (0, 255, 255))
                            response.append(True)
                            response.append("YELLOW")
                # Program Termination
                cv2.imshow("Multiple Color Detection in Real-TIme", imageFrame)
                if cv2.waitKey(10) & 0xFF == ord('q'):
                    webcam.release()
                    cv2.destroyAllWindows()
                    break




    # Display barcode and QR code location
def display(im, bbox):
    n = len(bbox)
    for j in range(n):
        cv2.line(im, tuple(bbox[j][0]), tuple(bbox[ (j+1) % n][0]), (255,0,0), 3)
    # Display results
    cv2.imshow("Results", im)


if __name__ == '__main__':
    run()