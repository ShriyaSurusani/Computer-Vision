import getopt
import numpy as np
import cv2

#Capturing the video from disc
cap=cv2.VideoCapture('Input.mp4')

#Getting the size
size=(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), \
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
	
#Codecc information
fourcc=cv2.VideoWriter_fourcc(*'mp4v')
fps=60.0
out=cv2.VideoWriter('output.mov',fourcc,fps,size,True)
	
while(cap.isOpened()):
	#Frame by frame capture
	ret, frame=cap.read()
	
	if (ret==True):
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
