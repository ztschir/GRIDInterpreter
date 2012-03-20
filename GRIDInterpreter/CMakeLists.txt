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
target_link_libraries(GRIDInterpreter 
"${PROJECT_SOURCE_DIR}/lib/libmysqlcppconn.so"
"/usr/lib64/libstdc++.so.5"
)


