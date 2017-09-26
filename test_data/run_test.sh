#!/usr/bin/env bash

echo ">>> runing the circAnno to annotate the circRNAs"
../bin/circAnno test_genes.bed12 test_circRNAs.bed6 >test_circAnno_candidates.txt 2>circAnno.log.txt
