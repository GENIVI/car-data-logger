cmake_minimum_required(VERSION 2.8)

project(DataStoreManager CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})

set(SRCS
	${SRC_DIR}/storemanager.cpp
	${SRC_DIR}/Configuration/configuration.cpp
        ${SRC_DIR}/DataStoreHandler/datastoreJSONhandler.cpp
	${SRC_DIR}/FileManager/fileinfodbhandler.cpp
	${SRC_DIR}/FileManager/fileinfodbquerygenerator.cpp
	${SRC_DIR}/FileManager/filemanager.cpp
        ${SRC_DIR}/StorageManager/storagemanager.cpp )

include_directories(${SRC_DIR}
	${SRC_DIR}/Configuration
	${SRC_DIR}/DataStoreHandler
        ${SRC_DIR}/FileManager
	${SRC_DIR}/StorageManager )

add_definitions(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
link_directories(${Boost_LIBRARY_DIR})

add_library(${PROJECT_NAME} SHARED ${SRCS})

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
	
install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/lib)
install(FILES ${SRC_DIR}/storemanager.h DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${SRC_DIR}/DataStoreHandler/datastoreJSONhandler.h DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
