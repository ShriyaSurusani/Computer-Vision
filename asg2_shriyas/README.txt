1. Course Number: 6820, Section Number: 003


2. Name: Shriya Reddy Surusani


3. Brief solution description:
	-The purpose of this program is to perform edge detection using sobel filters.
	-Output has 4 images, 2 before normalization and 2 after normalization.
	-Both horizontal and vertical filters are initialised in 'filters.c', where 'rarr[]' will be the 1x3 matrix for both the filters and 'carr[]' will be 3x1 matrix for both the filters.
	-Main program fetches the PGM image from disc and passes it on to PGMread function where it opens the file in 'read' mode, the image header is then read character by character, it is checked weather the input image header is that of pgm image, once satisfied it checks for the comments then scans the rows and columns from the header.
	-Using the rows and columns, memory is allocated to the PGM struct. Rows and colums are sent as arguments to pgm_allocation function where the memory is dynamincally allocated for magic number and pixels.For the returned PGM struct, with allocated memory, each pixel is read in a linear fashion [i.e. (0,0)(0,1)...(0,c)(1,0)(1,1)...(1,c)...]. Once done, the processed PGM struct image is returned to main.
	-In the main file the returned PGM struct is stored in 'gimg' which is then passed as argument along with the horizontal filter to 'PGMconv' function. In 'PGMconv' 2 loops are used. The first is to convolve along the rows using 'gp-rarr[]' (padding is done for boundary pixels using ternary condition) and the second is to convolve along the cols using 'gp-carr[]'(condition for padding is changed here). The result after 1st loop is the input for the second loop. The returned value is stored in 'dximg'
	-In main, 'gimg' is passed as an argument along with vertical filter to 'PGMconv' function which returns vertical edges and is stored in 'dyimg'.
	-Both of the returned vertical and horizontal edge detected images are sent to PGMwrite. PGMwrite function opens the destination PGM file in 'write' mode whose returned value is stored in 'out', using which the header of the file is written to the destination PGM image. Then, using the for loops. each pixel is written. The output is how the images look before normalization.
	-To get the normalised output, these images are passed as arguments to PGMnormalize. In PGMnormalize, after finding the minimum and maximum pixel value of the image. (pixel value - minimum)/(maximum - minimum) is used to normalize.
	-The returned images are then sent to PGMwrite so that the whole image pixels are written to the destination.
	-Once done, memory is freed. 
	

4. Lessons learned: 
	i)Getting the convolution logic:
		-Initially both my horizontal and vertical output images where same. Going through the filter initialization, everything seemed okay. I then printed a block of the image values of 3*3 size right after every for loop I used to check if the calculated results where what expected. Changing the condition for the ternary operation fixed the my logic and which resulted in expected output.

	ii)Getting normalization logic:
	 	-Initially got the same image after normalization. To check if the normalization actually worked, I've printed the pixel values to have a quick look only to realise there are negative values too. My first fix was applying modulus for the expression to remove the negatives. Thought output changed, it was darker than expected and was more like a quick fix. Later, I found the minimum pixel value of the convoluted image to use the expression (Pixel value - min)/ (max - min) for a better visual output.
	 	
	 

