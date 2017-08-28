cmake_minimum_required(VERSION 2.8)

project(vss_data_collector CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PREFIX ${CMAKE_INSTALL_PREFIX})

set(SRCS
	${SRC_DIR}/vss_data_collector.cpp
	${SRC_DIR}/data_config_service/data_config_parser.cpp
	${SRC_DIR}/vss_json_service/name_to_id_convertor.cpp
	${SRC_DIR}/vss_json_service/vss_item.cpp
	${SRC_DIR}/vss_json_service/vss_item_manager.cpp
	${SRC_DIR}/vss_json_service/vss_json_parser.cpp
	${SRC_DIR}/vsi_watcher/cycle_data_timer.cpp
	${SRC_DIR}/vsi_watcher/vsi_watcher.cpp )

include_directories(
	${SRC_DIR}
	${SRC_DIR}/vss_json_service
	${SRC_DIR}/data_config_service
	${SRC_DIR}/vsi_watcher )

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
install(FILES ${SRC_DIR}/vss_data_collector.hpp DESTINATION ${PREFIX}/include/${PROJECT_NAME})
install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${PREFIX}/lib/pkgconfig)
