#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <getopt.h>
extern "C" {
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "binRange.h"
#include "basicBed.h"
}

#include <map>
#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <vector>

using namespace std;

#include "circAnno.h"

struct hash *
readBed12(char *fileName, parameterInfo *paraInfo)
/* Read bed and return it as a hash keyed by chromName
 * with binKeeper values. */
{
  char   *row[12];
  struct lineFile *lf = lineFileOpen(fileName, TRUE);
  struct binKeeper *bk;
  struct hash *hash = newHash(0);
  struct hashEl *hel;
  struct bed *bed;
  while (lineFileRow(lf, row))
  {
    hel = hashLookup(hash, row[0]);
    if (hel == NULL)
    {
      bk = binKeeperNew(0, 511 * 1024 * 1024);
      hel = hashAdd(hash, row[0], bk);
    }
    bk = (binKeeper *)hel->val;
    bed = (struct bed *)bedLoad12(row);
    /*if (strcmp(bed->name,"chr22_46412480")==0) {
        fprintf(stderr, "chrom: %s name %s cov %s\n", bed->chrom, bed->name, bed->cov);
      }*/
    if (bed->chromStart > bed->chromEnd)
    {
      fprintf(stderr, "start after end line %d of %s, Exit!!!\n", lf->lineIx, lf->fileName);
      exit(1);
    }
    binKeeperAdd(bk, bed->chromStart, bed->chromEnd, bed);
  }
  lineFileClose(&lf);
  return hash;
}

void bedIntersect(char *aFile, char *bFile, FILE *outfp, parameterInfo *paraInfo)
/* bedIntersect - Intersect Bed and bed files. */
{
  struct hash *bHash = NULL;
  struct lineFile *lf = lineFileOpen(aFile, TRUE);
  char *row[100];
  char *name;
  char *chrom;
  char strand;
  int start, end, i, wordCount, blockCount, chromStart, chromEnd, score, itemRgb, geneLen;
  struct binKeeper *bk;
  struct bed *bed12;
  if (paraInfo->verbose)
  {
    fprintf(stderr, "load annotation information...\n");
  }
  bHash = readBed12(bFile, paraInfo);

  if (paraInfo->verbose)
  {
    fprintf(stderr, "annotate circRNA...\n");
  }

  while ((wordCount = lineFileChop(lf, row)) != 0)
  {
    chrom = row[0];
    start = lineFileNeedNum(lf, row, 1);
    end = lineFileNeedNum(lf, row, 2);
    name = row[3];
    score =  lineFileNeedNum(lf, row, 4);
    strand = row[5][0];
    geneLen = 0;
    if (paraInfo->verbose)
    {
      //fprintf(stderr, "chrom %s start %d end %d name: %s\n", name, start, end, row[3]);
    }
    if (start > end)
    {
      fprintf(stderr, "start after end line %d of %s, Exit!!!\n", lf->lineIx, lf->fileName);
      exit(1);
    }
    bk = (binKeeper *)hashFindVal(bHash, chrom);
    if (bk != NULL)
    {
      struct binElement *hitList = NULL, *hit;
      int hitTag = 0;
      char *overlapName = NULL;
      hitList = binKeeperFind(bk, start, end);
      for (hit = hitList; hit != NULL; hit = hit->next)
      {
        int blockStart = -1;
        int blockEnd = -1;
        int s = max(start, hit->start);
        int e = min(end, hit->end);
        int overlap = e - s;
        bed12 = (struct bed *)hit->val;
        if (overlap > paraInfo->minOverlapLen && strand == bed12->strand[0])
        {
          overlapName = bed12->name;
          blockCount = bed12->blockCount;
          for (i = 0; i < blockCount; i++)
          {
            chromStart = bed12->chromStart + bed12->chromStarts[i];
            chromEnd = chromStart + bed12->blockSizes[i];
            if (chromStart == start)
            {
              blockStart = i;
            }
            if (chromEnd == end)
            {
              blockEnd = i;
            }
          }
        } // overlap
        if (blockStart >= 0 && blockEnd >= blockStart)
        {
          hitTag = 1;
          blockCount = blockEnd - blockStart + 1;
          itemRgb = 255;
          for (i = blockStart; i <= blockEnd; i++)
          {
            geneLen += bed12->blockSizes[i];
          }
          if (geneLen < paraInfo->minLen)
          {
            fprintf(stderr, "Warning: The length(%d nt) of %s is less than %d nt, skip it!\n", geneLen, name, paraInfo->minLen);
            continue;
          }
          if (geneLen > paraInfo->maxLen)
          {
            fprintf(stderr, "Warning: The length(%d nt) of %s is large than %d nt, skip it!\n", geneLen, name, paraInfo->maxLen);
            continue;
          }
          fprintf(outfp, "%s\t%d\t%d\t%s:%s:match\t%d\t%c\t%d\t%d\t%d\t%d\t", chrom, start, end, name, bed12->name, score, strand, start, end, itemRgb, blockCount);
          for (i = blockStart; i <= blockEnd; i++)
          {
            fprintf(outfp, "%d,", bed12->blockSizes[i]);
          }
          fprintf(outfp, "\t");
          for (i = blockStart; i <= blockEnd; i++) // fetch sequences of all exons into circSeq
          {
            chromStart = bed12->chromStart + bed12->chromStarts[i];
            chromEnd = chromStart + bed12->blockSizes[i];
            int newStart =  chromStart - start;
            fprintf(outfp, "%d,", newStart);
          }
          fprintf(outfp, "\n");
          break; // exist loop
        } // match output
      } // for hit end
      slFreeList(&hitList); // free hit list
      // for overlap or intergenic circRNAs
      if (hitTag == 0 && paraInfo->match == 0)
      {
        blockCount = 1;
        itemRgb = 0;
        geneLen = end - start;
        if (geneLen < paraInfo->minLen)
        {
          fprintf(stderr, "Warning: The length(%d nt) of %s is less than %d nt, skip it!\n", geneLen, name, paraInfo->minLen);
          continue;
        }
        if (geneLen > paraInfo->maxLen)
        {
          fprintf(stderr, "Warning: The length(%d nt) of %s is large than %d nt, skip it!\n", geneLen, name, paraInfo->maxLen);
          continue;
        }
        if (overlapName != NULL)
        {
          fprintf(outfp, "%s\t%d\t%d\t%s:%s:overlap\t%d\t%c\t%d\t%d\t%d\t%d\t%d,\t\%d,\n", chrom, start, end, name, overlapName, score, strand, start, end, itemRgb, blockCount, end - start, 0);
        }
        else
        {
          fprintf(outfp, "%s\t%d\t%d\t%s:novel:intergenic\t%d\t%c\t%d\t%d\t%d\t%d\t%d,\t\%d,\n", chrom, start, end, name, score, strand, start, end, itemRgb, blockCount, end - start, 0);
        }
      } // if hitTag=0
    } // if bk end
    fflush(outfp);
  }// while end
  lineFileClose(&lf);
}
