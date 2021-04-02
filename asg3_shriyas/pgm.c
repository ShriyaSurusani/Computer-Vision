#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"
#include "wavelets.h"


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
        img->gpix=(double *)malloc((r*c)*sizeof(double));
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

//Decomposition function
PGM *PGMdwt(PGM *img,int level)
{
	int i,j,m,l;
	PGM *gimg=NULL, *finalimg=NULL;
	PGM *dgimg=NULL, *cdgimg=NULL;
	gimg=pgm_allocation(img->rows,img->cols);
	dgimg=pgm_allocation(img->rows,img->cols);
	cdgimg=pgm_allocation(img->rows,img->cols);
	finalimg=pgm_allocation(img->rows,img->cols);
	
	WVLT *wp;
	wp=wavelet();
	
	int ro, co;
	int c=0,d=0,e=0,f=0;
	
	ro = img->rows;
	co = img->cols;
	
	printf("Level at the start of loop %d \n",  level);
	printf("Start of decomposition \n");
	for(l=0;l<=level;l++)
	{
		//printf("ro is %d and co is %d \n", ro , co);
		for(i=0;i<ro;i++)
		{
			c=0;		    	
			//printf("Loop 1 \n");
			for(j=0;j<co;j+=2)
			{
				gimg->gpix[i*512+c] = (wp->h[0] * img->gpix[i*512+j]) + wp->h[1] * (img->gpix[i*512+(j+1)]);
				++c;
			}
		 
		}
	
		for(i=0;i<ro;i++)
		{
			d = co/2;
			//printf("Loop 2 \n");
			for(j=0;j<co;j+=2) 
			{
				    	
				gimg->gpix[i*512+d] = (wp->g[0] * img->gpix[i*512+j]) + (wp->g[1] * img->gpix[i*512+(j+1)]);    
				
				++d;
			
			}
		} 
	
		/*if(l==0)
		{
			dgimg=PGMnormalize(gimg);
			PGMwrite(dgimg,"intermidiate.pgm");
		} */

		 e=0;
		for(i=0;i<ro;i+=2)
		{ 
		
			for(j=0;j<co;j++)
			{	
			
				cdgimg->gpix[e*512+j] = (wp->h[0] * gimg->gpix[i*512+j]) + (wp->h[1] * gimg->gpix[(i+1) * 512+j]);
				
			} ++e;
		}
		f = ro/2;
		for(i=0;i<ro;i+=2)
		{ 
			for(j=0;j<co;j++)
			{	
 
				cdgimg->gpix[f*512+j] = (wp->g[0] * gimg->gpix[i*512+j]) + (wp->g[1] * gimg->gpix[(i+1) * 512+j]);

			} ++f;

		} 
		printf("Level at the end of loop %d \n",  l);
		printf(" Level loop \n");
		ro = ro/2;
		co = co/2;
		img = PGMcopy(cdgimg);
		gimg = PGMcopy(cdgimg);
	
	
		/*if(l==0)
		{
		finalimg=PGMnormalize(img);
		PGMwrite(finalimg,"test.pgm");
		} */
	}
	
	printf("Decomposed \n");
	return cdgimg;
}	

//Recontruction function
PGM *PGMidwt(PGM *img,int level)
{
	int i,j,m,l,w;
	PGM *gimg=NULL, *finalimg=NULL;
	PGM *dgimg=NULL, *cdgimg=NULL;
	PGM *xgimg=NULL, *ygimg=NULL;
	PGM *zgimg=NULL;
	
	gimg=pgm_allocation(img->rows,img->cols);
	dgimg=pgm_allocation(img->rows,img->cols);
	cdgimg=pgm_allocation(img->rows,img->cols);
	finalimg=pgm_allocation(img->rows,img->cols);
	xgimg=pgm_allocation(img->rows,img->cols);
	ygimg=pgm_allocation(img->rows,img->cols);
	zgimg=pgm_allocation(img->rows,img->cols);
	
	WVLT *wp;
	wp=wavelet();
	
	double ro, co;
	int c=0,d=0,e=0,f=0;
	
	ro = img->rows;
	co = img->cols;
	
	for(l=level;l>=0;l--)
	{	
		ro = img->rows;
		co = img->cols;
		for(w=0;w<l;w++)
		{
		ro = ro/2;
		co = co/2;
		} 
		
		//Swapping rows
		c=0;
		for(i=0;i<ro/2;i++)
		{ 
		
			for(j=0;j<co;j++)
			{	
				gimg->gpix[c*512+j] = img->gpix[i*512+j];
			
			} c= c+2;
		}
		d= 1;	
		for(i=ro/2;i<ro;i++)
		{
			for(j=0;j<co;j++)
			{

				gimg->gpix[d*512+j] = img->gpix[i*512+j];
				
				
			} d= d+2;
		}
		
		//Calculating using ht and gt filters
		e=0;
		for(i=0;i<ro;i+=2)
		{
			for(j=0;j<co;j++)
			{
				finalimg->gpix[e*512+j] = (wp->ht[0] * gimg->gpix[i*512+j]) + (wp->ht[1] * (gimg->gpix[(i+1) * 512+j]));
			} ++e;
		}
		
		f=ro/2;
		for(i=0;i<ro;i+=2)
		{
			for(j=0;j<co;j++)
			{
				finalimg->gpix[f*512+j] = (wp->gt[0] * gimg->gpix[i*512+j]) + (wp->gt[1] * (gimg->gpix[(i+1) * 512+j]));
			} ++f;
		}
		
		//Swapping rows
		c=0;
		for(i=0;i<ro/2;i++)
		{ 
		
			for(j=0;j<co;j++)
			{	
				dgimg->gpix[c*512+j] = finalimg->gpix[i*512+j];
			
			} c= c+2;
		}
		
		d= 1;
		for(i=ro/2;i<ro;i++)
		{
			for(j=0;j<co;j++)
			{
				dgimg->gpix[d*512+j] = finalimg->gpix[i*512+j];
				
				
			} d= d+2;
		}
		
		//Swapping columns
		for(i=0;i<ro;i++)
		{
			e=0;
			for(j=0;j<co/2;j++)
			{
				xgimg->gpix[i*512+e] = dgimg->gpix[i*512+j];
				e=e+2;
			}
		}
		
		for(i=0;i<ro;i++)
		{
			d=1;
			for(j=co/2;j<co;j++)
			{
				xgimg->gpix[i*512+d] = dgimg->gpix[i*512+j];
				d=d+2;
			}
		}
		
		//Calculating using ht and gt filters
		for(i=0;i<ro;i++)
		{
			e=0;
			for(j=0;j<co;j+=2)
			{
				ygimg->gpix[i*512+e] = (wp->ht[0] * xgimg->gpix[i*512+j]) + (wp->ht[1] * (xgimg->gpix[i*512+(j+1)]));
				++e;
			} 
		}
		
		
		for(i=0;i<ro;i++)
		{
			f=co/2;
			for(j=0;j<co;j+=2)
			{
				ygimg->gpix[i*512+f] = (wp->gt[0] * xgimg->gpix[i*512+j]) + (wp->gt[1] * (xgimg->gpix[i*512+(j+1)]));
				++f;
			} 
		}
			
		//Swapping columns
		for(i=0;i<ro;i++)
		{
			e=0;
			for(j=0;j<co/2;j++)
			{
				zgimg->gpix[i*512+e] = ygimg->gpix[i*512+j];
				e=e+2;
			}
		}
		
		for(i=0;i<ro;i++)
		{
			d=1;
			for(j=co/2;j<co;j++)
			{
				zgimg->gpix[i*512+d] = ygimg->gpix[i*512+j];
				d=d+2;
			}
		}
		
		printf("End of reconstruction loop \n");
		img = PGMcopy(zgimg); 

	}	
	return zgimg;
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
    double grey;
    double max= 0.0;
    gimg=pgm_allocation(img->rows,img->cols);
    
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
    double min = max;
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
    fprintf(out,"%f\n",img->maxc);

    for(i=0;i<img->rows;i++)
    {
        for(j=0;j<img->cols;j++)
        {
            grey = (unsigned char)(img->gpix[i*img->cols+j]*(double)img->maxc);
            fwrite(&grey,sizeof(unsigned char),1,out);
        }
    }
    printf("Wrote PGM file\n");
    fflush(out);
    fclose(out);
    return(0);
}
