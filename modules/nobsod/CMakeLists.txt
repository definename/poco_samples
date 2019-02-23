project(nobsod)

include(CRTLinkage)

set(VERSION_PRODUCT_NAME "${PROJECT_NAME}")
set(VERSION_FILE_DESC "${PROJECT_NAME} binary")

configure_file(src/res/Version.h.cmake Version.h @ONLY)
configure_file(src/res/Version.rc.cmake Version.rc @ONLY)
configure_file(src/res/NullServer.rc.cmake NullServer.rc @ONLY)

set(CONFIG_FILE_NAME NoBSoD.properties)
set(CONFIG_FILE_SRC ${CMAKE_CURRENT_LIST_DIR}/src/res/${CONFIG_FILE_NAME})
set(CONFIG_FILE_DEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${CONFIG_FILE_NAME})

set(PROJECT_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	include/Resource.h
	include/NoBSoD.h
	include/PnpUtilService.h
	include/Service.h
	include/ServiceNotification.h
	)
set(PROJECT_RESOURCES
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullServer.rc
	src/res/NullServer.ico
	src/res/${CONFIG_FILE_NAME}
	)
set(PROJECT_SOURCES
	src/NoBSoD.cpp
	src/Service.cpp
	src/PnpUtilService.cpp
	)
set(MISC
	src/pch.h
	src/pch.cpp
	src/targetver.h
	)

add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${MISC}
	)

set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullServer.rc
		PROPERTIES
			GENERATED 1
			)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})

include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}
	${Poco_INCLUDE_DIRS}
	${OPENSSL_INCLUDE_DIR}
	)
target_link_libraries(${PROJECT_NAME}
	${Poco_LIBRARIES}
	${OPENSSL_LIBRARIES}
	crypt32.lib
	Ws2_32.lib
	Iphlpapi.lib
	)
add_dependencies(${PROJECT_NAME}
	Poco
	)
add_definitions(
	-DUNICODE
	-D_UNICODE
	-DWIN32_LEAN_AND_MEAN
	)

add_precompiled_headers(${PROJECT_NAME} "src/")
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${PROPERTY_FOLDER})
# set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)

add_custom_command(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CONFIG_FILE_SRC}
		${CONFIG_FILE_DEST}
	COMMENT "Copying ${CONFIG_FILE_SRC} to ${CONFIG_FILE_DEST}"
	VERBATIM
	)