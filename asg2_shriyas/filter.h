#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED


typedef struct{
int rarr[3];
int carr[3];
}FLTR;

FLTR *sfilter(int count);
void FilterFree(FLTR **gp);

#endif // FILTER_H_INCLUDED
