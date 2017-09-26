#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <getopt.h>
#include<assert.h>
#include<math.h>
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

char version[] = "circAnno version 0.1";
void usage(void);

int main(int argc, char *argv[])
{
  int showVersion = 0;
  int showHelp    = 0;
  char *outfile = NULL;
  char *annofile = NULL;
  char *circfile = NULL;
  FILE *outfp = NULL;
  struct parameterInfo paraInfo;
  int c = 0;

  if (argc == 1)
  {
    usage();
  }

  const char *shortOptions = "vhVRsmo:c:l:i:x:";

  const struct option longOptions[] =
  {
    { "verbose" , no_argument , NULL, 'v' },
    { "help" , no_argument , NULL, 'h' },
    { "version" , no_argument , NULL, 'V' },
    { "split" , no_argument , NULL, 's' },
    { "match" , no_argument , NULL, 'm' },
    { "output" , required_argument , NULL, 'o' },
    { "min-len" , required_argument , NULL, 'i' },
    { "max-len" , required_argument , NULL, 'x' },
    {NULL, 0, NULL, 0} ,  /* Required at end of array. */
  };

  paraInfo.verbose = 0;
  paraInfo.minOverlapLen  = 0;
  paraInfo.split   = 0;
  paraInfo.length  = 100;
  paraInfo.minLen = 50;
  paraInfo.maxLen = 300000;
  paraInfo.match = 0;

  while ((c = getopt_long(argc, argv, shortOptions, longOptions, NULL)) >= 0)
  {
    switch (c)
    {
    case 'v':
      paraInfo.verbose = 1;
      break;
    case 'h':
      showHelp = 1;
      break;
    case 'V':
      showVersion = 1;
      break;
    case 'o':
      outfile = optarg;
      break;
    case 's':
      paraInfo.split = 1;
      break;
    case 'm':
      paraInfo.match = 1;
      break;
    case 'i':
      paraInfo.minLen = atoi(optarg);
      break;
    case 'x':
      paraInfo.maxLen = atoi(optarg);
      break;
    case '?':
      showHelp = 1;
      break;
    default:
      usage();
    }
  }

  if (argc == optind || argc - 2 != optind) usage();
  annofile = argv[optind];
  if (annofile == NULL)
  {
    fprintf(stderr, "ERROR: annotation file is not exist %s\n", argv[optind]);
    usage();
  }
  circfile = argv[optind+1];
  if (circfile == NULL)
  {
    fprintf(stderr, "ERROR: circRNA file is not exist %s\n", argv[optind+1]);
    usage();
  }
  if (outfile == NULL)
  {
    outfp = stdout;
  }
  else
  {
    outfp = (FILE *) fopen(outfile, "w");
    if (outfp == NULL)
    {
      fprintf(stderr, "ERROR: Can't open %s\n", outfile);
      usage();
    }
  }

  // help for version
  if (showVersion)
  {
    fprintf(stderr, "%s", version);
    exit(1);
  }

  if (showHelp)
  {
    usage();
    exit(1);
  }

  fprintf(stderr, "#program start...\n");
  bedIntersect(circfile, annofile, outfp, &paraInfo);
  fclose(outfp);
  fprintf(stderr, "#program end\n");

  return 0;
}

void usage(void)
{
  fprintf(stderr, "%s", "Usage:  circAnno [options] <annotation file, bed12> <circRNA file, bed> \n\
File format for bed is bed6 or bed12\n\
[options]\n\
-v/--verbose                   : verbose information\n\
-V/--version                   : circAnno version\n\
-h/--help                      : help informations\n\
-m/--match                     : only output the circRNAs with matched splice sites from known transcripts[default,output all circRNAs] \n\
-i/--min-len                   : minimum length of circRNA transcript[default=50]\n\
-x/--max-len                   : maximum length of circRNA transcript[default=300000]\n\
-o/--output <string>           : output file\n\
");

  exit(1);
}
