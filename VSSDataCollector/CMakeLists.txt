cmake_minimum_required(VERSION 2.8)

project(VSSDataCollector CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})

set(SRCS
	${SRC_DIR}/vssdatacollector.cpp
	${SRC_DIR}/DataConfigService/dataconfigparser.cpp
	${SRC_DIR}/VssJsonService/nametoidconvertor.cpp
	${SRC_DIR}/VssJsonService/vssitem.cpp
	${SRC_DIR}/VssJsonService/vssitemmanager.cpp
	${SRC_DIR}/VssJsonService/vssjsonparser.cpp
	${SRC_DIR}/VSIWatcher/cycledatatimer.cpp
	${SRC_DIR}/VSIWatcher/vsiwatcher.cpp )

include_directories(
	${SRC_DIR}
	${SRC_DIR}/VssJsonService
	${SRC_DIR}/DataConfigService
	${SRC_DIR}/VSIWatcher )

add_definitions(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)

find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
link_directories(${Boost_LIBRARY_DIR})

pkg_check_modules(VSI REQUIRED vsi )
include_directories(${VSI_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SRCS})

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
	
install(TARGETS ${PROJECT_NAME} DESTINATION ${PREFIX}/lib)
install(FILES ${SRC_DIR}/vssdatacollector.h DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
