set(BUNDLE_DESTINATION_DIR ${BUNDLE_DESTINATION_DIR}/remotingServer)
set(BUNDLE_NAME "RemotingServerBundle")
project(com.my.${BUNDLE_NAME})

if(CMAKE_CONFIGURATION_TYPES STREQUAL Debug)
	set(CMAKE_DEBUG_POSTFIX d)
endif()

set(VERSION_PRODUCT_NAME "${PROJECT_NAME}")
set(VERSION_FILE_DESC "${PROJECT_NAME} binary")

###########################################################
# Bundle definition  ######################################

set(BUNDLESPEC_FILENAME ${BUNDLE_NAME}.bndlspec)
set(BUNDLESPEC_FILE ${CMAKE_CURRENT_BINARY_DIR}/${BUNDLESPEC_FILENAME})
set(BUNDLE_DLL_NAME ${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX})
set(BUNDLE_SYMBOLIC_NAME "${PROJECT_NAME}")
set(BUNDLE_VERSION "1.0.1")
set(BUNDLE_ACTIVATOR_CLASS "${BUNDLE_NAME}Activator")
set(BUNDLE_ACTIVATOR_LIBRARY "${PROJECT_NAME}")
# set(BUNDLE_DEPENDENCY_SYMBOLIC_NAME ${CUSTOM_BUNDLE_PROVIDER_NAME})
# set(BUNDLE_DEPENDENCY_VERSION ${CUSTOM_BUNDLE_PROVIDER_VERSION})
set(BUNDLE_RUN_LEVEL "200")

###########################################################
# Remoting definition  ####################################

set(REMOTING_SERVICE_NAME RemotingService)
set(REMOTING_SERVICE_GEN_CFG ${CMAKE_CURRENT_LIST_DIR}/src/res/${REMOTING_SERVICE_NAME}Gen.xml)

set(REMOTING_SERVICE_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/include/I${REMOTING_SERVICE_NAME}.h
	${CMAKE_CURRENT_BINARY_DIR}/include/${REMOTING_SERVICE_NAME}RemoteObject.h
	${CMAKE_CURRENT_BINARY_DIR}/include/${REMOTING_SERVICE_NAME}ServerHelper.h
	${CMAKE_CURRENT_BINARY_DIR}/include/${REMOTING_SERVICE_NAME}Skeleton.h
	)
set(REMOTING_SERVICE_SOURCES
	${CMAKE_CURRENT_BINARY_DIR}/src/I${REMOTING_SERVICE_NAME}.cpp
	${CMAKE_CURRENT_BINARY_DIR}/src/${REMOTING_SERVICE_NAME}RemoteObject.cpp
	${CMAKE_CURRENT_BINARY_DIR}/src/${REMOTING_SERVICE_NAME}ServerHelper.cpp
	${CMAKE_CURRENT_BINARY_DIR}/src/${REMOTING_SERVICE_NAME}Skeleton.cpp
	)
set(REMOTING_SERVICE_OUTPUT
	${REMOTING_SERVICE_HEADERS}
	${REMOTING_SERVICE_SOURCES}
	)
set(REMOTING_SERVICE_INCLUDE_DIRS
	${CMAKE_CURRENT_BINARY_DIR}/include
	)	
set_source_files_properties(${REMOTING_SERVICE_OUTPUT} PROPERTIES COMPILE_FLAGS "/Y-")

###########################################################
# Configuring files  ######################################

configure_file(src/res/${BUNDLESPEC_FILENAME}.cmake ${BUNDLESPEC_FILE} @ONLY)
configure_file(src/res/Version.h.cmake Version.h @ONLY)
configure_file(src/res/Version.rc.cmake Version.rc @ONLY)
configure_file(src/res/NullConsole.rc.cmake NullConsole.rc @ONLY)

set(PROJECT_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	include/Resource.h
	include/${BUNDLE_ACTIVATOR_CLASS}.h
	include/${BUNDLE_NAME}Service.h
	include/${BUNDLE_NAME}ServiceImpl.h
	include/${REMOTING_SERVICE_NAME}.h
	)

set(PROJECT_RESOURCES
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
	src/res/NullConsole.ico
	src/res/${BUNDLESPEC_FILENAME}.cmake
	${REMOTING_SERVICE_GEN_CFG}
	)

set(PROJECT_SOURCES
	src/${BUNDLE_ACTIVATOR_CLASS}.cpp
	src/${BUNDLE_NAME}ServiceImpl.cpp
	src/${REMOTING_SERVICE_NAME}.cpp
	)

set(MISC
	src/pch.h
	src/pch.cpp
	src/targetver.h
	)

set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
	${BUNDLESPEC_FILE}
		PROPERTIES GENERATED 1
		)

source_group("Bundle Specification" FILES ${BUNDLESPEC_FILE})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Header Files\\Generated Files" FILES ${REMOTING_SERVICE_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Source Files\\Generated Files" FILES ${REMOTING_SERVICE_SOURCES})
source_group("" FILES ${MISC})

add_library(${PROJECT_NAME} SHARED
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${MISC}
	${BUNDLESPEC_FILE}
	${REMOTING_SERVICE_HEADERS}
	${REMOTING_SERVICE_SOURCES}
	)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${Poco_INCLUDE_DIRS}
		${REMOTING_SERVICE_INCLUDE_DIRS}
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
	)

add_precompiled_headers(${PROJECT_NAME} "src/")
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER ${PROPERTY_FOLDER})
# set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)

###########################################################
# Build remoting  #########################################

add_custom_command(
	OUTPUT ${REMOTING_SERVICE_OUTPUT}
	COMMAND ${Poco_REMOTE_GEN_TOOL} ${REMOTING_SERVICE_GEN_CFG} /define=POCO_ROOT=${POCO_ROOT} /define=OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR} /define=SOURCE_DIR=${CMAKE_CURRENT_LIST_DIR}
	DEPENDS ${Poco_REMOTE_GEN_TOOL} ${REMOTING_SERVICE_GEN_CFG}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Running POCO ${Poco_REMOTE_GEN_TOOL} tool on ${REMOTING_SERVICE_GEN_CFG}"
	VERBATIM
	)

###########################################################
# Build bundle  ###########################################

add_custom_command(
	TARGET ${PROJECT_NAME}
	POST_BUILD
	COMMAND ${Poco_BUNDLE_CREATOR} ARGS
		${BUNDLESPEC_FILE} /output-dir=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/${BUNDLE_DESTINATION_DIR}
	COMMENT "Generating ${PROJECT_NAME} bundle file in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}"
	VERBATIM
	)