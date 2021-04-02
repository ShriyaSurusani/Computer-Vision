#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include "filter.h"

typedef struct{
char *magic;
int rows;
int cols;
int maxc;
float *gpix;
}PGM;

PGM *pgm_allocation(int r,int c);
PGM *PGMread(const char *file);
PGM *PGMconv(PGM *img,FLTR *gp);
PGM *PGMcopy(PGM *img);
PGM *PGMnormalize(PGM *img);
int PGMwrite(PGM *img,const char *file);
void PGMfree(PGM **img);

#endif // PGM_H_INCLUDED
