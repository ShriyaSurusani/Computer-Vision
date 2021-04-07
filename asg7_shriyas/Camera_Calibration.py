import getopt
import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import csv
import cv2.aruco as aruco


#Capturing the video from disc
cap=cv2.VideoCapture('Input.mp4')

#Getting the size
size=(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), \
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
	
#Codecc information
fourcc=cv2.VideoWriter_fourcc(*'mp4v')
fps=30.0
out=cv2.VideoWriter('output.mov',fourcc,fps,size,True)

#Reading Camera Matrix and Distortion Coefficients 
cameraMatrix = np.loadtxt("Camera_Matrix", delimiter=",",usecols=range(3))
distortion_Coeff = np.loadtxt("Distortion_Coeff", delimiter =",",usecols=range(5))

#Axis points of the rectangle
axis = np.float32([[0,0,0], [0,80,0], [00,80,0],[80,0,0]])  #[0,0,-80], [0,80,-80],[80,80,-80],[80,0,-80]])

while(cap.isOpened()):
	#Frame by frame capture
	ret, frame=cap.read()
	
	if (ret==True):
		#Aruco marker detection
		arucoDict = aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)
		arucoParams = cv2.aruco.DetectorParameters_create()
		corners, ids, rejected = cv2.aruco.detectMarkers(frame, arucoDict, parameters=arucoParams)
		frame = aruco.drawDetectedMarkers(frame, corners, ids)
		
		#Pose Estimation
		rvecs, tvecs, _objPpoints = aruco.estimatePoseSingleMarkers(corners, 50, cameraMatrix, distortion_Coeff)
		frame = aruco.drawAxis(frame, cameraMatrix, distortion_Coeff, rvecs, tvecs, 40)
		
		#Argumenting aruco with rectangle
		
		#tl = corners[0][0][0], corners[0][0][1]
		#tr = corners[0][1][0], corners[0][1][1]
		#br = corners[0][2][0], corners[0][2][1]
		#bl = corners[0][3][0], corners[0][3][1]
		
		w = 600
		h = 600
		
		imgpts, J = cv2.projectPoints(axis, rvecs, tvecs, cameraMatrix, distortion_Coeff)
		imgpts = np.int32(imgpts).reshape(-1,2)
		frame = cv2.drawContours(frame, [imgpts[:4]], -1,(0,255,255), -3)
		
		
		print("rvecs:")
		print(rvecs)
		print("tvecs:")
		print(tvecs)
		print("corners:")
		print(corners)
		
		#for i,j in zip(range(4,4), range(4,8)):
			#frame = cv2.line(frame, tuple(imgpts[i], tuple(imgpts[j]),(255),3)
			
		#frame = cv2.drawContours(frame, [imgpts[4:], -1, (0,0,255), 3)
		
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
