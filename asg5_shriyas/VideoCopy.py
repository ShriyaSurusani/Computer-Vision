import getopt
import numpy as np
import cv2

#Loading the cascades
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
nose_cascade = cv2.CascadeClassifier('haarcascade_mcs_nose.xml')
mouth_cascade = cv2.CascadeClassifier('haarcascade_mcs_mouth.xml')

#Capturing the video from disc
cap=cv2.VideoCapture('Input2.mp4')

#Getting the size
size=(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), \
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
	
#Codecc information
fourcc=cv2.VideoWriter_fourcc(*'mp4v')
fps=12.0
out=cv2.VideoWriter('Output.mov',fourcc,fps,(1152, 648),True)
	
while(cap.isOpened()):

	#Frame by frame capture
	ret, frame=cap.read()
	
	if (ret==True):
		#grey = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		frame = cv2.resize(frame, None, fx=1.5, fy=1.5, interpolation=cv2.INTER_AREA)
		
		#Detection of face and other features
		face = face_cascade.detectMultiScale(frame, 1.1, 5)
		for (x,y,w,h) in face:
			cv2.rectangle(frame, (x,y), (x+w, y+h), (255,0,0), 2)
			range_color = frame[y:y+h, x:x+w]
			
	
			#Eyes detection
			eyes = eye_cascade.detectMultiScale(range_color,1.3,5)
			for (ex,ey,ew,eh) in eyes:
				eh = int(eh - 0.15*eh)
				cv2.rectangle(range_color, (ex, ey), (ex+ew, ey+eh), (0,255,0), 2)
			
			#Nose detection
			nose = nose_cascade.detectMultiScale(range_color,1.3,5)
			for (nx,ny,nw,nh) in nose:
				cv2.rectangle(range_color, (nx,ny), (nx+nw, ny+nh), (0,0,255), 2)
			
			#Mouth detection
			mouth = mouth_cascade.detectMultiScale(range_color,1.7, 11)
			for (mx,my,mw,mh) in mouth:
				#mx = int(mx + 0.3*mw)			
				my = int(my - 0.15*mh)
				cv2.rectangle(range_color, (mx,my), (mx+mw, my+mh), (255,255,255), 2)
		
	
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
