include ../../thirdUtils/kent/src/inc/common.mk
CXXC=g++
L+=-lm -lz
CFLAGS = -O3 -g
HG_DEFS = -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_GNU_SOURCE
HG_WARN=-Wformat -Wimplicit -Wreturn-type
UTILITIES_DIR = ../../thirdUtils
BIN_DIR = ../../bin
BIO_DIR = ../../bioUtils
INCLUDES = -I$(UTILITIES_DIR)/kent/src/inc \
           -I$(BIO_DIR)
BIO_LIBS   = -L$(BIO_DIR)/ -lbiotools \
             $(UTILITIES_DIR)/kent/src/lib/$(MACHTYPE)/jkweb.a \

all:
	make ../../thirdUtils/kent/src/lib
	make circAnno

circAnno: circAnno.o circAnnoMain.o
	$(CXXC) $(CFLAGS) ${HG_DEFS} ${HG_WARN} $(INCLUDES) -o ${BIN_DIR}/circAnno circAnno.o \
	circAnnoMain.o $(BIO_LIBS) $(L)

circAnno.o: circAnno.cpp circAnno.h
	$(CXXC) $(CFLAGS) ${HG_DEFS} ${HG_WARN}  $(INCLUDES) -c circAnno.cpp $(INCLUDE) $(L)

circAnnoMain.o: circAnnoMain.cpp circAnno.h
	$(CXXC) $(CFLAGS) ${HG_DEFS} ${HG_WARN} $(INCLUDES) -c circAnnoMain.cpp
	
clean:
	rm -f *.o
