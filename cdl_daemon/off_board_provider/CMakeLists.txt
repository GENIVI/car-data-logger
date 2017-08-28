cmake_minimum_required(VERSION 2.8)

project(off_board_provider CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})

set(SRCS
	${SRC_DIR}/off_board_provider.cpp
	${SRC_DIR}/rvi_client/rvi_client.cpp
	${SRC_DIR}/rvi_data_manager/rvi_data_manager.cpp)

include_directories(
	${SRC_DIR}
	${SRC_DIR}/rvi_client
	${SRC_DIR}/rvi_data_manager )

add_definitions(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
link_directories(${Boost_LIBRARY_DIR})

pkg_check_modules(PYTHON REQUIRED python )
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SRCS})

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
	
install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/lib)
install(FILES ${SRC_DIR}/off_board_provider.hpp DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
