/* bed head file */

#ifndef BED_CONSERVATION_H
#define BED_CONSERVATION_H

typedef struct parameterInfo
{
	int 	 verbose;
	int    split;
	int    length;
	int    minLen;
	int    maxLen;
	int    minOverlapLen;
	int    match;
} parameterInfo;

struct hash *readBed12(char *fileName, parameterInfo *paraInfo);

void bedIntersect(char *aFile, char *bFile, FILE *outfp, parameterInfo *paraInfo);


#endif /* End BED_CONSERVATION_H */