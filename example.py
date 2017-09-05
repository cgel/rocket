'''
Created on 05.04.2016

@author: fehlfarbe
'''
import sys
import cv2
import numpy as np
import aruco

if __name__ == '__main__':

    detector = aruco.MarkerDetector()

    # load video
    #cap = cv2.VideoCapture('example.mp4')
    cap = cv2.VideoCapture(1)
    ret, frame = cap.read(1)
    
    if not ret:
        print("can't open video!")
        sys.exit(-1)

    while ret:
        markers = detector.detect(frame)

        for marker in markers:
            # print marker ID and point positions
            print("Marker: {:d}".format(marker.id))
            for i, point in enumerate(marker):
                print("\t{:d} {}".format(i, str(point)))
            marker.draw(frame, np.array([255, 255, 255]), 2)

            print("detected ids: {}".format(", ".join(str(m.id) for m in markers)))

        # show frame
        cv2.imshow("frame", frame)
        cv2.waitKey(100)
        
        # read next frame
        ret, frame = cap.read()
