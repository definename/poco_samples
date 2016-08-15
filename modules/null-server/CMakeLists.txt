project(null-server)

set(VERSION_PRODUCT_NAME "${PROJECT_NAME}")
set(VERSION_FILE_DESC "${PROJECT_NAME} binary")

configure_file(src/res/Version.h.cmake Version.h @ONLY)
configure_file(src/res/Version.rc.cmake Version.rc @ONLY)
configure_file(src/res/NullServer.rc.cmake NullServer.rc @ONLY)

set(PROJECT_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	include/Resource.h
	include/NullServer.h
	)
set(PROJECT_RESOURCES
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullServer.rc
	src/res/NullServer.ico
	)
set(PROJECT_SOURCES
	src/NullServer.cpp
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
	${POCO_INCLUDE_DIRS}
	${OPENSSL_INCLUDE_DIR}
	)
target_link_libraries(${PROJECT_NAME}
	${POCO_LIBRARIES}
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