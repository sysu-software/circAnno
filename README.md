# circAnno<BR>
A tool for annotating circRNAs with known gene annotations<BR>
<BR>
Overview:<BR>
---------<BR>
circAnno is A tool for annotating circRNAs with known gene information<BR>
<BR>
Usage:<BR>
---------<BR>
Usage:  circAnno [options] <annotation file, bed12> <circRNA file, bed> <BR>
File format for bed is bed6 or bed12<BR>
[options]<BR>
-v/--verbose                   : verbose information<BR>
-V/--version                   : circAnno version<BR>
-h/--help                      : help informations<BR>
-m/--match                     : only output the circRNAs with matched splice sites from known transcripts[default,output all circRNAs] <BR>
-i/--min-len                   : minimum length of circRNA transcript[default=50]<BR>
-x/--max-len                   : maximum length of circRNA transcript[default=300000]<BR>
-o/--output <string>           : output file<BR>
<BR>
<BR>
Installation:<BR>
---------<BR>
Download circAnno.tar.gz from http://starbase.sysu.edu.cn/circAnno/; unpack it, and make:<BR>
tar -xvf circAnno.tar.gz <BR>
cd circAnno<BR>
make<BR>
The newly compiled binary (circAnno) is in the circAnno /bin directory.<BR>
<BR>
At this point you should have everything to run a built-in test data set<BR>
cd test_data<BR>
./run_test.sh<BR>
<BR>
System requirements:<BR>
---------<BR>
Operating system: circAnno is designed to run on POSIX-compatible platforms, including UNIX, Linux and Mac OS/X. <BR>
We have tested  most extensively on Linux and MacOS/X because these are the machines we develop on.<BR>
Compiler: The source code is compiled with  the C++ compiler g++. We test the code using the g++ compilers.<BR>
Libraries and other installation requirements: circAnno includes one software library: the kent library package from UCSC Genome Browser. <BR>
All will automatically compile during circAnno installation process. By default, circAnno does not require any additional libraries to be installed by you.<BR>
<BR>
Prerequisites<BR>
---------:<BR>
Annotation file<BR>
You can use Table Browser to get the bed12 file for genome annotation(e.g. GENCODE)<BR>
http://genome.ucsc.edu/cgi-bin/hgTables<BR>
e.g. You can save the output files in genome: hg19.gencode.bed12<BR>
<BR>
run circAnno:<BR>
---------<BR>
bin/circAnno ./test_data/test_genes.bed12 ./test_data/test_circRNAs.bed6 >./test_data/test_circAnno_candidates.txt<BR>
<BR>
Output:<BR>
---------<BR>
# output is bed12 format<BR>
chrX	139865339	139866824	circSeeker-1:ENST00000625883.1|CDR1-AS|ENSG00000281508.1|CDR1-AS-001|antisense:match	9	+	139865339	139866824	255	1	1485,	0,<BR>
<BR>
Acknowledgements:<BR>
---------<BR>
Thanks a lot to everyone who contributed to the public code used by circAnno.<BR>
<BR>
Contact :<BR>
---------<BR>
/*******************************************************************************<BR>
 *	circAnno - A tool for annotating circRNAs with known gene annotations<BR>
 *<BR>
 *	Author : Jian-Hua Yang <yangjh7@mail.sysu.edu.cn><BR>
 * <BR>
 *	School of Life Sciences, Sun Yat-Sen University<BR>
 *  <BR>
 *******************************************************************************/<BR>
