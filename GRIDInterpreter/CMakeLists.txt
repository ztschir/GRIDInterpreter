cmake_minimum_required(VERSION 2.6)
project(GRIDInterpreter)

set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/lib/cppconn")
link_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/lib/cppconn")

file(GLOB GRIDInterpreter_SOURCE_DIR
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(GRIDInterpreter ${GRIDInterpreter_SOURCE_DIR})

find_library(MYSQL_LIBRARY libmysqlcppconn PATHS /usr/lib64 DOC "libmysqlcppconn library")
if(NOT MYSQL_LIBRARY)
    message(FATAL_ERROR "Library libmysqlcppconn required, but not found!")
endif(NOT MYSQL_LIBRARY)

find_library(STD_LIBRARY libstdc++.so.5 PATHS /usr/lib64 DOC "libstdc++.so.5 library")
if(NOT STD_LIBRARY)
    message(FATAL_ERROR "Library libstdc++.so.5 required, but not found!")
endif(NOT STD_LIBRARY)


target_link_libraries(GRIDInterpreter 
"/usr/lib64/libmysqlcppconn.so"
"/usr/lib64/libstdc++.so.5"
)


