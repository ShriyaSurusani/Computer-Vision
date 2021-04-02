#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"
#include "filter.h"


int main()
{
	
    PGM *gimg=NULL, *cimg=NULL;
    PGM *dximg=NULL, *dyimg=NULL;
    PGM *ndximg=NULL, *ndyimg=NULL;
    PGM *mdximg=NULL, *mdyimg=NULL;
    FLTR *gxp=sfilter(0);
    FLTR *gyp=sfilter(1);

    //Read PGM image
    gimg=PGMread("converted.pgm");
    cimg=PGMcopy(gimg);
    
    //Convolution 
    dximg=PGMconv(gimg,gxp);
    dyimg=PGMconv(gimg,gyp); 
    
    //Writing PGM image before normalizing
    PGMwrite(dximg,"Horizontal.pgm");
    PGMwrite(dyimg,"Vertical.pgm");
    
    //Writing PGM image after normalization
    ndximg=PGMcopy(dximg);
    mdximg=PGMnormalize(ndximg);
    PGMwrite(mdximg,"Normalize_horizontal.pgm");
    
    ndyimg=PGMcopy(dyimg);
    mdyimg=PGMnormalize(ndyimg);
    PGMwrite(mdyimg,"Normalized_vertical.pgm");

    //Freeing image
    PGMfree(&gimg);
    PGMfree(&dximg);
    PGMfree(&dyimg);
    FilterFree(&gxp);
    FilterFree(&gyp);

    return 0;
}
