cmake_minimum_required(VERSION 2.6)
project(GRIDInterpreter)

set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(${GRIDInterpreter_SOURCE_DIR})
link_directories(${GRIDInterpreter_BINARY_DIR})

#the one C file
add_executable(cdemo cdemo.c)
target_link_libraries(cdemo m) #link the math library

#these are all compiled the same way
set(PROGRAMS GRIDInterpreter TableColumnValues TableColumns ConfigFileReader DataFileReader Importer)

foreach(program ${PROGRAMS})
  add_executable(${program} ${program}.cpp)
  target_link_libraries(${program} ${CORELIBS})
endforeach(program)

#building just a library. 
ADD_LIBRARY(mysqlcppconn SHARED libmysqlcppconn.so)