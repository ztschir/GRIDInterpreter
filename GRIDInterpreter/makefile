CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= GRIDInterpreter.cpp TableColumnValues.cpp TableColumns.cpp ConfigFileReader.cpp DataFileReader.cpp
LIBRARIES= ./lib/
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=GRIDInterpreter

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $(OBJECTS) -L $(LIBRARIES) -o $@
    
.cpp.o:
    $(CC) $(CFLAGS) $< -o $@