import getopt
import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import csv

#Capturing the video from disc
cap=cv2.VideoCapture('Input.mp4')

#Getting the size
size=(int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)), \
	int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
	
#Codecc information
fourcc=cv2.VideoWriter_fourcc(*'mp4v')
fps=30.0
out=cv2.VideoWriter('output.mov',fourcc,fps,size,True)

#CHECKERBOARD = (6,9)

ox = 9
oy = 6

#3D points in real space
objpoints = []

#2D points in image plain
imgpoints = []

objp = np.zeros((6*9,3), np.float32)
objp[:,:2] = np.mgrid[0:9,0:6].T.reshape(-1,2)

while(cap.isOpened()):
	#Frame by frame capture
	ret, frame=cap.read()
	
	if (ret==True):
		#Calibration Code
		#objp = np.zeros((6*9,3), np.float32)
		#objp[:,:,] = np.mgrid[0:9,0:6].T.reshape(-1,2)
		
		gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
		dim = (300, 250)
		
		resized = cv2.resize(gray, dim, interpolation = cv2.INTER_AREA)
		
		ret, corners = cv2.findChessboardCorners(gray, (ox, oy), None)
		
		
		if(ret==True):
			objpoints.append(objp)
			imgpoints.append(corners)
			
			#cv2.drawChessboardCorners(frame, (ox, oy), corners, ret)
		
		ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, resized.shape[::-1],None,None)
		
		retPnP, rvecs, tvecs = cv2.solvePnP(objp, corners, mtx, dist)
		rvecs = -rvecs.T
		tvecs = -tvecs.T
		
		frame = cv2.drawFrameAxes(frame, mtx, dist, rvecs[0], tvecs[0], 8)
		
		print("Camera Matrix:")
		print(mtx)
		print("Distortion Coeff:")
		print(dist) 
		
		
		#backtorgb = cv2.cvtColor(gray,cv2.COLOR_GRAY2RGB)
		
		
		with open ("Camera_Matrix", "w") as csv_file:
			writer = csv.writer(csv_file, delimiter=",")
			for d in mtx:
				writer.writerow(d)
		
		with open ("Distortion_Coeff", "w") as csv_file2:
			writer2 = csv.writer(csv_file2, delimiter=",")
			for f in dist:
				writer2.writerow(f)
	
	
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
