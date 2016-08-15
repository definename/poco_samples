project(TimeServer)
include(CRTLinkage)

set(VERSION_PRODUCT_NAME "${PROJECT_NAME}")
set(VERSION_FILE_DESC "${PROJECT_NAME} binary")

configure_file(src/res/Version.h.cmake Version.h @ONLY)
configure_file(src/res/Version.rc.cmake Version.rc @ONLY)
configure_file(src/res/NullConsole.rc.cmake NullConsole.rc @ONLY)

set(REMOTING_SERVICE_HEADER
	include/TimeService.h
	include/TimeServiceImpl.h
	include/Types.h
	include/ConnectionHandler.h
	include/ScopedLog.h
	)

set(REMOTING_SERVICE_SOURCES
	src/TimeService.cpp
	src/TimeServiceImpl.cpp
	src/WakeUpTask.cpp
	)

set(PROJECT_HEADERS
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	include/Resource.h
	include/WakeUpTask.h
	include/ServerApp.h
	)

set(PROJECT_RESOURCES
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
	src/res/NullConsole.ico
	)

set(PROJECT_SOURCES
	src/ServerApp.cpp
	)

set(MISC
	src/pch.h
	src/pch.cpp
	src/targetver.h
	RemoteGen.xml
	)

set(GEN_REMOTING_HEADERS
	include/TimeServiceServerHelper.h
	include/TimeServiceSkeleton.h
	include/TimeServiceRemoteObject.h
	include/ITimeService.h
	include/LocationDataUnitDeserializer.h
	include/LocationDataUnitSerializer.h
	include/TimeServiceEventDispatcher.h
	include/InternalDeserializer.h
	include/InternalSerializer.h
	include/TEventSerializer.h
	include/TEventDeserializer.h
	)

set(GEN_REMOTING_SOURCES
	src/TimeServiceServerHelper.cpp
	src/TimeServiceSkeleton.cpp
	src/TimeServiceRemoteObject.cpp
	src/ITimeService.cpp
	src/TimeServiceEventDispatcher.cpp
	)

set(GEN_REMOTING_WSDL
	wsdl/TimeService.wsdl
	)

set_source_files_properties(
	${GEN_REMOTING_HEADERS}
	${GEN_REMOTING_SOURCES}
	${REMOTING_SERVICE_HEADER}
	${REMOTING_SERVICE_SOURCES}
		PROPERTIES COMPILE_FLAGS "/Y-"
		)

add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${MISC}
	${REMOTING_SERVICE_HEADER}
	${REMOTING_SERVICE_SOURCES}
	${GEN_REMOTING_HEADERS}
	${GEN_REMOTING_SOURCES}
	${GEN_REMOTING_WSDL}
	)

set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/Version.rc
	${CMAKE_CURRENT_BINARY_DIR}/NullConsole.rc
		PROPERTIES
			GENERATED 1
			)

source_group("Generated Files\\Header Files" FILES ${GEN_REMOTING_HEADERS})
source_group("Generated Files\\Source Files" FILES ${GEN_REMOTING_SOURCES})
source_group("Generated Files\\wsdl" FILES ${GEN_REMOTING_WSDL})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})

include_directories(
	include
	${Poco_INCLUDE_DIRS}
	)
target_link_libraries(${PROJECT_NAME}
	${Poco_LIBRARIES}
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