1. Course Number: 6820, Section Number: 003


2. Name: Shriya Reddy Surusani


3. Brief solution description: 
	-The purpose of this program is to convert a PPM image to PGM image
	-Main program fetches the PPM image from disc and passes it on to PPMread function where it opens the file in 'read' mode, the image header is then read character by character, it is checked weather the input image header is that of ppm image, once satisfied it checks for the comments then scans the rows and columns from the header. 
	-Using the rows and columns, memory is allocated to the PPM struct. Rows and colums are sent as arguments to PPMmemoryalloc function where the memory is dynamincally allocated for magic number and pixels.For the returned PPM struct, with allocated memory, each pixel is read in a linear fashion [i.e. (0,0)(0,1)...(0,c)(1,0)(1,1)...(1,c)...] 3 colours[Red,Green,Blue) are read from each pixel on every iteration of the loop. Once done, the processed PPM struct image is returned to main.
	-In the main file the returned PPM struct is stored in 'cimg' which is then passed as argument to PPMtoPGM function. Here 'gimg' of PGM struct is also declared and allocated memory. RGB colour values from each pixel of 'cimg' is averaged to convert it into one grey pixel of 'gimg' (Here, average method algorithm is used). The returned image is stored in 'gimg' of main function.
	-'gimg' along with the destination PGM image name is passed as arguments to PGMwrite function. PGMwrite function opens the destination PGM file in 'write' mode whose returned value is stored in 'out', using which the header of the file is written to the destination PGM image. Then, using the for loops. each grey pixel is written.
	-Once the whole image pixels are written to the destination. The image is closed and the memory is freed.
	
	
4. Lessons learned: 
	i)Was getting "Segmentation error (Core dumped)" while runtime.
		- Tried identifing were the error was by inserting printf statements after each function to check if that function is executed as intended by the program. Found the problem to be in my funtions for freeing the memory for both ppm and pgm. Fixed it by freeing each field of the object first that was dynamically allocated then finally freed the object.
	
	ii)Function to convert PPM to PGM was returning "undefined reference to <funtion name>" error
		- Declared the function in PPM header since PPM source file includes both pgm.h and ppm.h
		
	iii)Initially, the converted image was all grey
		- Went through my conversion of PPMtoPGM function to check if there was anything wrong with the formula used. But later while goind through the code all over, realised that I just 'fread' for only 'rpix' and not for 'gpix' and 'bpix'. Once I 'fread' them the issue got resolved.
		
	iv)Should have used error messages which would have saved a lot of debugging time.
	
	
	
	

