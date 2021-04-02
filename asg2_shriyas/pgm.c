#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"
#include "filter.h"


//Memory allocation for PGM file
PGM *pgm_allocation(int r,int c)
    {
        PGM *img=NULL;
        img=(PGM *)malloc(sizeof(PGM));

        img->rows=r;
        img->cols=c;
        img->maxc=255;
        img->magic=(char *)malloc(3*sizeof(char));
        strcpy(img->magic,"P5");
        img->gpix=(float *)malloc((r*c)*sizeof(float));
        printf("Allocated PGM memory \n");

        return img;
    }

//To free PGM memory
void PGMfree(PGM **img)
{
    if((*img)->magic)
    {
        free((*img)->magic);
    }
    if((*img)->gpix)
    {
        free((*img)->gpix);
    }
    free(*img);
    (*img)=NULL;
    printf("Freed PGM memory\n");
}


//Reading PGM image
PGM *PGMread(const char *file)
{
    PGM *img=NULL;
    FILE *in=NULL;

    unsigned char gpix;

    int i,j;
    int rows,cols,maxc;
    char c;

    in=fopen(file,"r");
    if(((c=fgetc(in))=='P')&&((c=fgetc(in))=='5')&&((c=fgetc(in))=='\n'))
    {
        if((c=fgetc(in))=='#')
        {
            do{
                c=fgetc(in);
            } while(c!='\n');
        }
        else
        {
            ungetc(c,in);
	}

        fscanf(in,"%u %u",&cols,&rows);
        fscanf(in,"%u",&maxc);

        img= pgm_allocation(rows,cols);

        if(img)
        {
            for(i=0;i<rows;i++)
            {
                for(j=0;j<cols;j++)
                {
                    fread(&gpix,sizeof(unsigned char),1,in);
                    img->gpix[i*img->cols+j]=gpix;
                    //img->gpix[i*img->cols+j]=(float)gpix/(float)maxc;
                }
            }
        }
        printf("Read PGM image \n");
    }
    else
    {
    	printf("Not a proper format \n");
    }
    return img;
}

//Convolution
PGM *PGMconv(PGM *img,FLTR *gp)
{
	int i,j,m;
	PGM *gimg=NULL, *finalimg=NULL;
	gimg=pgm_allocation(img->rows,img->cols);
	finalimg=pgm_allocation(img->rows,img->cols);
	
	/* Checking the logic on Block of 3x3 image 

	for(m=0;m<3;m++)
	{
		printf(" rarr %d \n",gp->rarr[m]);
	}
	
	for(m=0;m<3;m++)
	{
		printf("carr %d \n",gp->carr[m]);
	}
	printf("Main \n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
		printf("%f-",img->gpix[i*3+j]);
		}
	}
	printf("Intermediatte \n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(m=0;m<3;m++)
			{
				gimg->gpix[i*3+j] += gp->rarr[m] * (j-m >= 0? img->gpix[i*3 + (j-m)] : 0.0);
			}
			printf("%f-",gimg->gpix[i*3+j]);
		}
	}
	printf("final \n");
	for(i=0;i<3;i++)
	{ 
		for(j=0;j<3;j++)
		{	
			for(m=0;m<3;m++)	
			{
				finalimg->gpix[i*3+j] += gp->carr[m] * (i-m >=  0? gimg->gpix[(i*3 + j)-m*3] : 0.0);
			}
			printf("%f-",finalimg->gpix[i*3+j]);
		}
	} */
	
	for(i=0;i<img->rows;i++)
	{
		for(j=0;j<img->cols;j++)
		{
			for(m=0;m<3;m++)
			{
				gimg->gpix[i*img->cols+j] += gp->rarr[m] * (j-m >= 0? img->gpix[i*img->cols + (j-m)] : 0.0);
			}
			//printf("%f-",gimg->gpix[i*img->cols+j]);
		}
	}
	
	for(i=0;i<gimg->rows;i++)
	{ 
		for(j=0;j<gimg->cols;j++)
		{	
			for(m=0;m<3;m++)	
			{
				finalimg->gpix[i*gimg->cols+j] += gp->carr[m] * (i-m >=  0? gimg->gpix[(i*gimg->cols + j)-m*gimg->cols] : 0.0);
			}

			//printf("%f-",finalimg->gpix[i*img->cols+j]);

		}

	} 
	
	
	printf("Convoluted \n");
	return finalimg;
}	


//Copying PGM image
PGM *PGMcopy(PGM *img)
{
    int i,j;
    PGM *gcopy=NULL;
    
    gcopy = pgm_allocation(img->rows,img->cols);
    
    gcopy->magic = img->magic;
    gcopy->rows = img->rows;
    gcopy->cols = img->cols;
    gcopy->maxc = img->maxc;
    
    for(i=0;i<img->rows;i++)
    {
        for(j=0;j<img->cols;j++)
        {
           gcopy->gpix[i*img->cols+j] = img->gpix[i*img->cols+j];
        }
    }
    
    printf("Copied the file \n");
    return gcopy;
}

//Normalizing
PGM *PGMnormalize(PGM *img)
{
    int i,j;
    PGM *gimg=NULL;
    float grey;
    float max= 0.0;
    gimg=pgm_allocation(img->rows,img->cols);
    
   /* Used mod to remove negative values initially

    for(i=0;i<img->rows;i++)
    {
    	for(j=0;j<img->cols;j++)
    	{ 
    		if(max<=img->gpix[i*img->cols+j])
    		{
    		max= fabsf(img->gpix[i*img->cols+j]);
    		}
    	}
    } */
    
    for(i=0;i<img->rows;i++)
    {
    	for(j=0;j<img->cols;j++)
    	{ 
    		if(max<=img->gpix[i*img->cols+j])
    		{
    		max= img->gpix[i*img->cols+j];
    		}
    	}
    }
    float min = max;
    for(i=0;i<img->rows;i++)
    {
    	for(j=0;j<img->cols;j++)
    	{ 
    		if(min>=img->gpix[i*img->cols+j])
    		{
    		min= img->gpix[i*img->cols+j];
    		}
    	}
    }
    
    
    
    for(i=0;i<img->rows;i++)
    {
    	for(j=0;j<img->cols;j++)
    	{
    		grey = ((img->gpix[i*img->cols+j]) - (min)) / (max - min);
    		gimg->gpix[i*gimg->cols+j] = grey;
    		
    		
    	}
    }
    printf("max value is %f \n",max);
    printf("min value is %f \n",min);
    printf("Normalized \n");
    
    return gimg;
}


//Writing PGM image
int PGMwrite(PGM *img,const char *file)
{
    int i,j;
    FILE *out;
    unsigned char grey;

    out=fopen(file,"w");

    fprintf(out,"%s\n",img->magic);
    fprintf(out,"%d %d\n",img->rows,img->cols);
    fprintf(out,"%d\n",img->maxc);

    for(i=0;i<img->rows;i++)
    {
        for(j=0;j<img->cols;j++)
        {
            grey = (unsigned char)(img->gpix[i*img->cols+j]*(float)img->maxc);
            fwrite(&grey,sizeof(unsigned char),1,out);
        }
    }
    printf("Wrote PGM file\n");
    fflush(out);
    fclose(out);
    return(0);
}
