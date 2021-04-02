#ifndef PPM_H
#define PPM_H

typedef struct{
char *magic;
int rows;
int cols;
int maxc;
float *rpix;
float *gpix;
float *bpix;
}PPM;

PPM *PPMmemoryalloc(int r,int c);
PPM *PPMread(const char *file);
PGM *PPMtoPGM(PPM *cimg);
int PPMwrite(PPM *img,const char *file);
void PPMfree(PPM **img);

#endif // PPM_H_INCLUDED
