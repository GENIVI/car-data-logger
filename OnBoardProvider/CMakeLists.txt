cmake_minimum_required(VERSION 2.8)

project(OnBoardProvider CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})
set(CLIENTAPI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)

add_subdirectory(src/libCDLClientSomeIp)

set(SRCS
	${SRC_DIR}/onboardprovider.cpp
	${SRC_DIR}/DataManager/datamanager.cpp
	${SRC_DIR}/OnBoardProviderService/onboardproviderservice.cpp
	${SRC_DIR}/OnBoardProviderService/onboardproviderdbusservice.cpp
	${SRC_DIR}/OnBoardProviderService/onboardprovidersomeipservice.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIDBusDeployment.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIDBusStubAdapter.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIStubDefault.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPITypesDBusDeployment.cpp)

include_directories(${SRC_DIR}
	${SRC_DIR}/DataManager
	${SRC_DIR}/OnBoardProviderService
	${CLIENTAPI_DIR}/src-gen
	${CLIENTAPI_DIR}/src-gen/v1 )

add_definitions(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
link_directories(${Boost_LIBRARY_DIR})

pkg_check_modules(COMMONAPI REQUIRED CommonAPI )
include_directories(${COMMONAPI_INCLUDE_DIRS})

pkg_check_modules(COMMONAPI-DBUS REQUIRED CommonAPI-DBus )
include_directories(${COMMONAPI-DBUS_INCLUDE_DIRS})

pkg_check_modules(COMMONAPI-SOMEIP REQUIRED CommonAPI-SomeIP )
include_directories(${COMMONAPI-SOMEIP_INCLUDE_DIRS})

pkg_check_modules(DBUS-1 REQUIRED dbus-1 )
include_directories(${DBUS-1_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SRCS})

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
	
install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/lib)
install(FILES ${SRC_DIR}/onboardprovider.h DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
