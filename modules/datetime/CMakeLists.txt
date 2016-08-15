project(datetime)
include(CRTLinkage)

set(VERSION_PRODUCT_NAME "${PROJECT_NAME}")
set(VERSION_FILE_DESC "${PROJECT_NAME} binary")

configure_file(src/res/Version.h.cmake Version.h @ONLY)
configure_file(src/res/Version.rc.cmake Version.rc @ONLY)
configure_file(src/res/NullConsole.rc.cmake NullConsole.rc @ONLY)

set(PROJECT_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	include/Resource.h
	)

set(PROJECT_RESOURCES
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
	src/res/NullConsole.ico
	)

set(PROJECT_SOURCES
	src/Main.cpp
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
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
		PROPERTIES GENERATED 1
		)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_CURRENT_BINARY_DIR}
		${Poco_INCLUDE_DIRS}
		)
target_link_libraries(${PROJECT_NAME}
	${Poco_LIBRARIES}
	# crypt32.lib
	# Ws2_32.lib
	Iphlpapi.lib
	)
# add_dependencies(${PROJECT_NAME}
	# )
add_definitions(
	-DUNICODE
	-D_UNICODE
	-DWIN32_LEAN_AND_MEAN
	)

add_precompiled_headers(${PROJECT_NAME} "src/")
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${PROPERTY_FOLDER})
# set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)