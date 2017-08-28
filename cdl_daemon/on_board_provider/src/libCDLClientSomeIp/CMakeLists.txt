cmake_minimum_required(VERSION 2.8)

set(CLIENTAPI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../interface)

set(SOMEIP_GLUE_SRCS
        ${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPISomeIPDeployment.cpp
        ${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPISomeIPProxy.cpp
        ${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPISomeIPStubAdapter.cpp
        ${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPITypesSomeIPDeployment.cpp )

include_directories(${CLIENTAPI_DIR}/src-gen
                ${CLIENTAPI_DIR}/src-gen/v1 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

pkg_check_modules( COMMONAPI REQUIRED CommonAPI )
include_directories(${COMMONAPI_INCLUDE_DIRS})

add_library( CDLClientSomeIp SHARED ${SOMEIP_GLUE_SRCS} )

install( TARGETS CDLClientSomeIp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../deploy/lib)
