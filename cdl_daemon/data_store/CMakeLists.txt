cmake_minimum_required(VERSION 2.8)

project(data_store_manager CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})

set(SRCS
	${SRC_DIR}/store_manager.cpp
	${SRC_DIR}/configuration/configuration.cpp
	${SRC_DIR}/data_store_handler/data_store_json_handler.cpp
	${SRC_DIR}/file_manager/file_info_db_handler.cpp
	${SRC_DIR}/file_manager/file_info_db_query_generator.cpp
	${SRC_DIR}/file_manager/file_manager.cpp
	${SRC_DIR}/storage_manager/storage_manager.cpp )

include_directories(
	${SRC_DIR}
	${SRC_DIR}/configuration
	${SRC_DIR}/data_store_handler
	${SRC_DIR}/file_manager
	${SRC_DIR}/storage_manager )

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
install(FILES ${SRC_DIR}/store_manager.hpp DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
