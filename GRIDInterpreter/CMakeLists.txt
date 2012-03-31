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

find_library(MYSQL_LIBRARY libmysqlcppconn.so PATHS /usr/lib64 DOC "libmysqlcppconn.so library")
if(NOT MYSQL_LIBRARY)
    message(FATAL_ERROR "Library libmysqlcppconn.so required, but not found! Copy library into /usr/lib64.")
endif(NOT MYSQL_LIBRARY)


target_link_libraries(GRIDInterpreter 
"/usr/lib64/libmysqlcppconn.so"
"/usr/lib64/libstdc++.so.5"
)


