#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pgm.h"
#include "ppm.h"


int main()
{
    PGM *gimg=NULL;
    PPM *cimg=NULL;

    printf("Fetching PPM file\n");
    cimg=PPMread("test.ppm");
    
    printf("Starting conversion\n");
    gimg=PPMtoPGM(cimg);
    
    printf("Starting PGM write process\n");
    PGMwrite(gimg,"converted.pgm");

    PGMfree(&gimg);
    PPMfree(&cimg);
    return 0;
}


