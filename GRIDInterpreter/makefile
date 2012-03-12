CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= GRIDInterpreter.cpp TableColumnValues.cpp TableColumns.cpp ConfigFileReader.cpp DataFileReader.cpp Importer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=GRIDInterpreter

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $(OBJECTS) -o $@
    
.cpp.o:
    $(CC) $(CFLAGS) $< -o $@