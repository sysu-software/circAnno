/*******************************************************************************
 *	circAnno - A tool for annotating circRNAs with known gene annotations
 *
 *	Author : Jian-Hua Yang <yangjh7@mail.sysu.edu.cn>
 * 
 *	School of Life Sciences, Sun Yat-Sen University
 *  
 *******************************************************************************/

Overview:
---------
circAnno is A tool for annotating circRNAs with known gene information

Usage:
---------
Usage:  circAnno [options] <annotation file, bed12> <circRNA file, bed> 
File format for bed is bed6 or bed12
[options]
-v/--verbose                   : verbose information
-V/--version                   : circAnno version
-h/--help                      : help informations
-m/--match                     : only output the circRNAs with matched splice sites from known transcripts[default,output all circRNAs] 
-i/--min-len                   : minimum length of circRNA transcript[default=50]
-x/--max-len                   : maximum length of circRNA transcript[default=300000]
-o/--output <string>           : output file


Installation:
---------
Download circAnno.tar.gz from http://starbase.sysu.edu.cn/circAnno/; unpack it, and make:
tar -xvf circAnno.tar.gz 
cd circAnno
make
The newly compiled binary (circAnno) is in the circAnno /bin directory.

At this point you should have everything to run a built-in test data set
cd test_data
./run_test.sh

System requirements:
---------
Operating system: circAnno is designed to run on POSIX-compatible platforms, including UNIX, Linux and Mac OS/X. We have tested  most extensively on Linux and MacOS/X because these are the machines we develop on.
Compiler: The source code is compiled with  the C++ compiler g++. We test the code using the g++ compilers.
Libraries and other installation requirements: circAnno includes one software library: the BamTools library package. All will automatically compile during circAnno installation process. By default, circAnno does not require any additional libraries to be installed by you.

Prerequisites
---------:
Annotation file
You can use Table Browser to get the bed12 file for genome annotation(e.g. GENCODE)
http://genome.ucsc.edu/cgi-bin/hgTables
e.g. You can save the output files in genome: hg19.gencode.bed12

run circAnno:
---------
bin/circAnno test_circRNAs.bed6 test_genes.bed12 >circAnno_circRNAs.bed12

Output:
---------
chrX	139865339	139866824	circSeeker-1:ENST00000625883.1|CDR1-AS|ENSG00000281508.1|CDR1-AS-001|antisense:match	9	+	139865339	139866824	255	1	1485,	0,

Acknowledgements:
---------
Thanks a lot to everyone who contributed to the public code used by circAnno.

Contact :
---------
JianHua, Yang<yangjh7@mail.sysu.edu.cn or lsp03yjh@gmail.com>
last modified time: /01/2017/

