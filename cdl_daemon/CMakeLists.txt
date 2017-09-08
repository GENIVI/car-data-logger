cmake_minimum_required(VERSION 2.8)

project(cdl_daemon CXX)

set(CDL_DAEMON_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DATA_COLLECTOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vss_data_collector)
set(DATA_STORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data_store)
set(ONBOARD_PROVIDER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/on_board_provider)
set(OFFBOARD_PROVIDER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/off_board_provider)

set(CLIENTAPI_DIR ${ONBOARD_PROVIDER_DIR}/interface)

add_subdirectory(${ONBOARD_PROVIDER_DIR}/src/libCDLClientSomeIp)

set(SRCS
	# VSSCollector source files
	${DATA_COLLECTOR_DIR}/src/vss_data_collector.cpp
	${DATA_COLLECTOR_DIR}/src/data_config_service/data_config_parser.cpp
	${DATA_COLLECTOR_DIR}/src/vss_json_service/name_to_id_convertor.cpp
	${DATA_COLLECTOR_DIR}/src/vss_json_service/vss_item.cpp
	${DATA_COLLECTOR_DIR}/src/vss_json_service/vss_item_manager.cpp
	${DATA_COLLECTOR_DIR}/src/vss_json_service/vss_json_parser.cpp
	${DATA_COLLECTOR_DIR}/src/vsi_watcher/cycle_data_timer.cpp
	${DATA_COLLECTOR_DIR}/src/vsi_watcher/vsi_watcher.cpp
	# DataStore source files
	${DATA_STORE_DIR}/src/store_manager.cpp
	${DATA_STORE_DIR}/src/configuration/configuration.cpp
	${DATA_STORE_DIR}/src/data_store_handler/data_store_json_handler.cpp
	${DATA_STORE_DIR}/src/file_manager/file_info_db_handler.cpp
	${DATA_STORE_DIR}/src/file_manager/file_info_db_query_generator.cpp
	${DATA_STORE_DIR}/src/file_manager/file_manager.cpp
	${DATA_STORE_DIR}/src/storage_manager/storage_manager.cpp
	# OnBoardProvider source files
	${ONBOARD_PROVIDER_DIR}/src/on_board_provider.cpp
	${ONBOARD_PROVIDER_DIR}/src/data_manager/data_manager.cpp
	${ONBOARD_PROVIDER_DIR}/src/on_board_provider_service/on_board_provider_service.cpp
	${ONBOARD_PROVIDER_DIR}/src/on_board_provider_service/on_board_provider_dbus_service.cpp
	${ONBOARD_PROVIDER_DIR}/src/on_board_provider_service/on_board_provider_someip_service.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIDBusDeployment.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIDBusStubAdapter.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPIStubDefault.cpp
	${CLIENTAPI_DIR}/src-gen/v1/org/genivi/CDL/ClientAPITypesDBusDeployment.cpp
	# OffBoardProvider source files
	${OFFBOARD_PROVIDER_DIR}/src/off_board_provider.cpp
	${OFFBOARD_PROVIDER_DIR}/src/rvi_client/rvi_client.cpp
	${OFFBOARD_PROVIDER_DIR}/src/rvi_data_manager/rvi_data_manager.cpp
        # Common Log source files
	${CDL_DAEMON_DIR}/common/log.cpp
	${CDL_DAEMON_DIR}/common/client_authentication/client_authentication_decryption_handler.cpp
	# CDL Daemon source files
	${CDL_DAEMON_DIR}/cdl_daemon.cpp
        ${CDL_DAEMON_DIR}/main.cpp)

include_directories(
	${CDL_DAEMON_DIR}
	# VSSCollector include directories
	${DATA_COLLECTOR_DIR}/src
	${DATA_COLLECTOR_DIR}/src/vss_json_service
	${DATA_COLLECTOR_DIR}/src/data_config_service
	${DATA_COLLECTOR_DIR}/src/vsi_watcher
	# DataStore include directories
	${DATA_STORE_DIR}/src
	${DATA_STORE_DIR}/src/configuration
	${DATA_STORE_DIR}/src/data_store_handler
	${DATA_STORE_DIR}/src/file_manager
	${DATA_STORE_DIR}/src/storage_manager
	# OnBoardProvider include directories
	${ONBOARD_PROVIDER_DIR}/src
	${ONBOARD_PROVIDER_DIR}/src/data_manager
	${ONBOARD_PROVIDER_DIR}/src/on_board_provider_service
	${CLIENTAPI_DIR}/src-gen
	${CLIENTAPI_DIR}/src-gen/v1
	# OffBoardProvider include directories
	${OFFBOARD_PROVIDER_DIR}/src
	${OFFBOARD_PROVIDER_DIR}/src/rvi_client
	${OFFBOARD_PROVIDER_DIR}/src/rvi_data_manager
	# Common
	${CDL_DAEMON_DIR}/common)

add_definitions(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include(FindPkgConfig)

# Common package
find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
link_directories(${Boost_LIBRARY_DIR})

# VSSCollector need library package
pkg_check_modules(VSI REQUIRED vsi )
include_directories(${VSI_INCLUDE_DIRS})
link_directories(${VSI_INCLUDE_DIRS})

# OnBoradProvider need library package
pkg_check_modules(COMMONAPI REQUIRED CommonAPI )
include_directories(${COMMONAPI_INCLUDE_DIRS})
link_directories(${COMMONAPI_INCLUDE_DIRS})

pkg_check_modules(COMMONAPI-DBUS REQUIRED CommonAPI-DBus )
include_directories(${COMMONAPI-DBUS_INCLUDE_DIRS})
link_directories(${COMMONAPI-DBUS_INCLUDE_DIRS})

pkg_check_modules(COMMONAPI-SOMEIP REQUIRED CommonAPI-SomeIP )
include_directories(${COMMONAPI-SOMEIP_INCLUDE_DIRS})
link_directories(${COMMONAPI-SOMEIP_INCLUDE_DIRS})

pkg_check_modules(DBUS-1 REQUIRED dbus-1 )
include_directories(${DBUS-1_INCLUDE_DIRS})
link_directories(${DBUS-1_INCLUDE_DIRS})

# OffBoardProvider need library package
pkg_check_modules(PYTHON REQUIRED python )
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_INCLUDE_DIRS})

# make exec file       
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} CommonAPI)
target_link_libraries(${PROJECT_NAME} CommonAPI-SomeIP)
target_link_libraries(${PROJECT_NAME} CommonAPI-DBus)
#target_link_libraries(${PROJECT_NAME} dbus-1)
target_link_libraries(${PROJECT_NAME} vsi)
target_link_libraries(${PROJECT_NAME} vsi-core)
target_link_libraries(${PROJECT_NAME} sqlite3)
target_link_libraries(${PROJECT_NAME} boost_system)
target_link_libraries(${PROJECT_NAME} boost_thread)
target_link_libraries(${PROJECT_NAME} boost_log)
target_link_libraries(${PROJECT_NAME} boost_filesystem)
target_link_libraries(${PROJECT_NAME} boost_date_time)
target_link_libraries(${PROJECT_NAME} boost_iostreams)
target_link_libraries(${PROJECT_NAME} python2.7)

# install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CDL_DAEMON_DIR}/deploy)
install(DIRECTORY ${CDL_DAEMON_DIR}/configuration_files/ 
                DESTINATION ${CDL_DAEMON_DIR}/deploy 
                FILES_MATCHING 
                PATTERN "*" 
                PATTERN "*.py" EXCLUDE )

install(DIRECTORY ${CDL_DAEMON_DIR}/config/
                DESTINATION ${CDL_DAEMON_DIR}/deploy/config
                FILES_MATCHING
                PATTERN "*" )
