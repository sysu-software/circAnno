UTILITIES_DIR = ../thirdUtils

INCLUDES = -I$(UTILITIES_DIR)/kent/src/inc

SOURCES = bedFile.cpp bioUtils.cpp faiFile.cpp

OBJECTS= $(SOURCES:.cpp=.o)

biolib.a: $(OBJECTS) $(SOURCES)
	ar rcus libbiotools.a $(OBJECTS)

$(OBJECTS): $(SOURCES)
	@$(CXX) -c $(*D)/$(*F).cpp $(INCLUDES) -o $(*F).o

clean:
	rm -f *.o
