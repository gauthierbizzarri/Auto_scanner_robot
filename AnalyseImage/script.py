import sys
import time
import cv2
import imutils
import numpy as np


    # Display barcode and QR code location
def display(im, bbox):
    n = len(bbox)
    for j in range(n):
        cv2.line(im, tuple(bbox[j][0]), tuple(bbox[ (j+1) % n][0]), (255,0,0), 3)
    # Display results
    cv2.imshow("Results", im)

def main():
    cap = cv2.VideoCapture(0)
    time.sleep(2.0)

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
            #display(frame, bbox)
            rectified_image = np.uint8(rectified_image);
            cv2.imshow("Rectified QRCode", rectified_image);
        else:
        	pass
    if cv2.waitKey(10) & 0xFF == ord('q'):
    	cap.release()
    	cv2.destroyAllWindows()

if __name__=="__main__":
	main()
	