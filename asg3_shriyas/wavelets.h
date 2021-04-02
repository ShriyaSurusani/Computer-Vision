#ifndef WAVELETS_H_INCLUDED
#define WAVELETS_H_INCLUDED

typedef struct{
int len;
double h[18];
double g[18];
double ht[18];
double gt[18];
}WVLT;

WVLT *wavelet();

#endif // WAVELETS_H_INCLUDED
