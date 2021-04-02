#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED

typedef struct{
char *magic;
int rows;
int cols;
double maxc;
double *gpix;
}PGM;

PGM *pgm_allocation(int r,int c);
PGM *PGMread(const char *file);
PGM *PGMdwt(PGM *img,int l);
PGM *PGMidwt(PGM *img,int l);
PGM *PGMcopy(PGM *img);
PGM *PGMnormalize(PGM *img);
int PGMwrite(PGM *img,const char *file);
void PGMfree(PGM **img);


#endif // PGM_H_INCLUDED
