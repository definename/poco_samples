cmake_minimum_required(VERSION 3.2.1)

project("stream_factory")

include(PCHSupport)
include(CRTLinkage)

# Source files
set(STREAM_SOURCES
	src/main.cpp
	)
set(STREAM_HEADES
	# ADD HEADERS HERE
	)
	
set(MISC
	src/pch.h
	src/pch.cpp
	)
	
add_definitions(
	-DWIN32_LEAN_AND_MEAN
	-D_CRT_SECURE_NO_WARNINGS
	-DUNICODE
	-D_UNICODE
	)

add_executable(${PROJECT_NAME}
	${STREAM_SOURCES}
	${STREAM_HEADES}
	${MISC}
	)

add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(include
	${POCO_INCLUDE_DIR}
	)

target_link_libraries(${PROJECT_NAME}
	${POCO_LIBRARIES}
	Ws2_32.lib
	Iphlpapi.lib
	)

add_dependencies(${PROJECT_NAME}
	Poco
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)	
