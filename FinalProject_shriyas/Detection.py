import getopt
import numpy as np
import cv2
import imutils
from imutils.object_detection import non_max_suppression
from imutils import paths

#Initializing HOG descriptor
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

#Capturing the video from disc
cap=cv2.VideoCapture('Input.mp4')

#Getting the size
size=(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), \
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
	
#Codecc information
fourcc=cv2.VideoWriter_fourcc(*'mp4v')
fps=29.9

out=cv2.VideoWriter('Output.mov',fourcc,fps,(400, 200),True)
	
while(cap.isOpened()):

	#Frame by frame capture
	ret, frame=cap.read()
	
	if (ret==True):
		#Re-sizing and making a copy
		frame = imutils.resize(frame, width=min(400, frame.shape[1]))
		orig = frame.copy()
		
		#Detecting people
		(rects, weights) = hog.detectMultiScale(frame, winStride=(4, 4), padding=(8, 8), scale=1.05)
			
		#Drawing original boundery boxes
		for (x, y, w, h) in rects:
			cv2.rectangle(orig, (x, y), (x + w, y + h), (0, 0, 255), 2)

		#Applying non-maxima suppression to the bounding boxes
		rects = np.array([[x, y, x + w, y + h] for (x, y, w, h) in rects])
		pick = non_max_suppression(rects, probs=None, overlapThresh=0.65)

		#Final boundery boxes
		for (xA, yA, xB, yB) in pick:
			cv2.rectangle(frame, (xA, yA), (xB, yB), (0, 255, 0), 2)
	
		#Write frame
		out.write(frame)
			
		#Display the frame
		cv2.imshow('frame',frame)
		if (cv2.waitKey(1) & 0xFF == ord('q')):
			break
			
	else:
		break
		
#Release Capture
cap.release()
out.release()
cv2.destroyAllWindows()  
