cmake_minimum_required(VERSION 3.2.1)

project(host_entry)

include(PCHSupport)
include(CRTLinkage)

# Source files
set(PROJECT_SOURCES
	src/main.cpp
	)
set(PROJECT_HEADES
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
	${PROJECT_SOURCES}
	${PROJECT_HEADES}
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
