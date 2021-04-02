#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"

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


