#ifndef PGM_H
#define PGM_H

typedef struct{
char *magic;
int rows;
int cols;
int maxc;
float *gpix;
}PGM;

PGM *pgm_allocation(int r,int c);
PGM *PGMread(const char *file);
int PGMwrite(PGM *img,const char *file);
void PGMfree(PGM **img);


#endif // PGM_H_INCLUDED
