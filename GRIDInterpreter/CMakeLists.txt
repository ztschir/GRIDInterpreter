cmake_minimum_required(VERSION 2.6)
project(GRIDInterpreter)

set(CMAKE_CXX_FLAGS "-g -Wall")


include_directories(./ ./lib/cppconn ./lib)
link_directories(./)
link_directories("${PROJECT_SOURCE_DIR}/lib")

set(MYSQLCONNECTORCPP_ROOT_DIR 
        "./lib/" 
        CACHE 
        PATH 
        "Where to start looking for this component.") 


find_path(MYSQLCONNECTORCPP_INCLUDE_DIR 
        mysql_connection.h 
        HINTS 
        ${MYSQLCONNECTORCPP_ROOT_DIR} 
        PATH_SUFFIXES 
        include) 
                
find_library(MYSQLCONNECTORCPP_LIBRARY 
        NAMES 
        mysqlcppconn 
        mysqlcppconn-static 
        HINTS 
        ${MYSQLCONNECTORCPP_ROOT_DIR} 
        PATH_SUFFIXES 
        lib64 
        lib)  

mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR MYSQLCONNECTORCPP_LIBRARY) 

include(FindPackageHandleStandardArgs) 
find_package_handle_standard_args(MysqlConnectorCpp 
        DEFAULT_MSG 
        MYSQLCONNECTORCPP_INCLUDE_DIR 
        MYSQLCONNECTORCPP_LIBRARY) 

if(MYSQLCONNECTORCPP_FOUND) 
        set(MYSQLCONNECTORCPP_INCLUDE_DIRS "./lib") # Add any dependencies here 
        set(MYSQLCONNECTORCPP_LIBRARIES "./lib") # Add any dependencies here 
        mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR) 
endif() 

file(GLOB GRIDInterpreter_SOURCE_DIR
    "*.h"
    "*.cpp"
)

file(GLOB GRIDInterpreter_LIB_HEADERS
    "lib/*.h"
)

add_executable(GRIDInterpreter ${GRIDInterpreter_SOURCE_DIR})




