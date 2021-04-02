#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"
#include "ppm.h"

//Memory allocation for PPM file
PPM *PPMmemoryalloc(int r,int c)
{
     PPM *img=NULL;
     img=(PPM *)malloc(sizeof(PPM));
        
     img->rows=r;
     img->cols=c;
     img->maxc=255;
     img->magic=(char *)malloc(3*sizeof(char));
     strcpy(img->magic,"P6");
     img->rpix=(float *)malloc((r*c)*sizeof(float));
     img->gpix=(float *)malloc((r*c)*sizeof(float));
     img->bpix=(float *)malloc((r*c)*sizeof(float));
	
     printf("PPM memory allocated \n");
     return img;
}

//To free PPM memory
void PPMfree(PPM **img)
{
    if((*img)->magic)
    {
        free((*img)->magic);
    }
    if((*img)->rpix)
    {
        free((*img)->rpix);
    }
    if((*img)->gpix)
    {
        free((*img)->gpix);
    }
    if((*img)->bpix)
    {
        free((*img)->bpix);
    }
    free((*img));
    (*img)=NULL;
    
    printf("Freed PPM memory \n");
}
//Reading PPM image
PPM *PPMread(const char *file)
{
    PPM *img=NULL;
    FILE *in=NULL;
    
    unsigned char rpix;
    unsigned char gpix;
    unsigned char bpix;
    
    int i,j;
    int rows,cols,maxc;
    char c;

    in=fopen(file,"r");
    if(((c=fgetc(in))=='P')&&((c=fgetc(in))=='6')&&((c=fgetc(in))=='\n'))
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
        
        img= PPMmemoryalloc(rows,cols);

        if(img)
        {
            for(i=0;i<rows;i++)
            {
                for(j=0;j<cols;j++)
                {
                    fread(&rpix,sizeof(unsigned char),1,in);
                    fread(&gpix,sizeof(unsigned char),1,in);
                    fread(&bpix,sizeof(unsigned char),1,in);
                    img->rpix[i*img->cols+j]=(float)rpix/(float)maxc;
                    img->gpix[i*img->cols+j]=(float)gpix/(float)maxc;
                    img->bpix[i*img->cols+j]=(float)bpix/(float)maxc;
                }
            }
        }
        printf("Read PPM image \n");
    }
    else
    {
    	printf("Not a proper format \n");
    }
    return img;
}

//converting to PGM
PGM *PPMtoPGM(PPM *cimg)
{
    int i,j;
    PGM *gimg=NULL;
    float r,g,b,l;

    gimg=pgm_allocation(cimg->rows,cimg->cols);

    for(i=0;i<cimg->rows;i++)
            {
                for(j=0;j<cimg->cols;j++)
                {
                    r=cimg->rpix[i*cimg->cols+j];
                    g=cimg->gpix[i*cimg->cols+j];
                    b=cimg->bpix[i*cimg->cols+j];
                    l=(0.3*r)+(0.3*g)+(0.3*b);
                    gimg->gpix[i*gimg->cols+j] =l;
                }
            } 
    printf("PPM Converted to PGM \n");
    return gimg;
}
