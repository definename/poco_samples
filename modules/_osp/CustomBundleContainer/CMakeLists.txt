project(CustomBundleContainer)

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
	src/CustomBundleContainer.cpp
	)

set(MISC
	src/pch.h
	src/pch.cpp
	src/targetver.h
	)

set(CONFIG_FILENAME CustomBundleContainer.properties)
set(CONFIG_FILE ${CMAKE_CURRENT_LIST_DIR}/src/res/${CONFIG_FILENAME})

set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
		PROPERTIES GENERATED 1
		)

source_group("Configuration Files" FILES ${CONFIG_FILE})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})

add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${MISC}
	${CONFIG_FILE}
	)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${Poco_INCLUDE_DIRS}
	)
target_link_libraries(${PROJECT_NAME}
	${Poco_SHARED_LIBRARIES}
	# crypt32.lib
	Ws2_32.lib
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

add_custom_command(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CONFIG_FILE}
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${CONFIG_FILENAME}
	COMMENT "Copying config file to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}"
	VERBATIM
	)