#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#include "pgm.h"
#include "wavelets.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	int level;
	PGM *gimg=NULL, *cimg=NULL;
	PGM *dimg=NULL, *cdimg=NULL;
	PGM *ndimg=NULL, *fndimg=NULL;
	PGM *copydimg=NULL, *rimg=NULL;
	
	printf(" Enter pyramid level (Range=[0,8]): \n");
	scanf("%d", &level);

    //Read PGM image
    gimg=PGMread("converted.pgm");
    
    //Copy PGM image and decomposing
    cimg=PGMcopy(gimg);
    dimg=PGMdwt(cimg, level);
    
    //Writing dwt image before normalizing
    PGMwrite(dimg,"Decomposed.pgm");
    
    //Writing dwt image after normalizing
    ndimg=PGMcopy(dimg);
    fndimg=PGMnormalize(ndimg);
    PGMwrite(fndimg,"Normalized_decomposedIMG.pgm");
    
    //Reconstruction
    copydimg=PGMcopy(dimg);
    rimg=PGMidwt(copydimg, level);
    
    //Writing reconstructed image before normalizing
    PGMwrite(rimg,"Reconstructed.pgm");
    
    //Writing reconstructed image after normalizing
    cdimg = PGMnormalize(rimg);
    PGMwrite(cdimg,"Normalized_Reconstructed.pgm");
    
    //Freeing image
    PGMfree(&gimg);
    PGMfree(&dimg);
    PGMfree(&fndimg);
    PGMfree(&rimg);
    PGMfree(&cdimg);

    return 0;
}

