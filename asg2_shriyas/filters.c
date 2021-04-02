#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "filter.h"

//To free filter memory
void FilterFree(FLTR **gp)
{
    free(*gp);
    (*gp)=NULL;
    printf("Freed Filter memory\n");
}

//Initializing Sobel filter
FLTR *sfilter(int count)
{
    FLTR *dx, *dy;
    	 if(count==0)
    	 {

	            dx=(FLTR *)malloc(sizeof(FLTR));
	            
	  	    dx->rarr[0]=1;
	  	    dx->rarr[1]=0;
	  	    dx->rarr[2]=-1;
	    	    dx->carr[0]=1;
	    	    dx->carr[1]=2;
	    	    dx->carr[2]=1;
	    	    
	    	    return dx;
	  }

	 
 	 if(count==1)
	  {
	  	    dy=(FLTR *)malloc(sizeof(FLTR));
	  	    
	  	    dy->rarr[0]=1;
	  	    dy->rarr[1]=2;
	  	    dy->rarr[2]=1;
	    	    dy->carr[0]=1;
	    	    dy->carr[1]=0;
	    	    dy->carr[2]=-1;
	    	    
	  	    return dy;
	  	    
	  } 
	  
      printf("Initialized sobel filter \n");
	    	    
}	    	    
	    	   
