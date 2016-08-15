project(converter)

include(PCHSupport)
include(CRTLinkage)

set(PROJECT_SOURCES
	src/main.cpp
	)

set(PROJECT_HEADERS	
	)

set(MISC
	src/pch.h
	src/pch.cpp
	)

add_definitions(
	-DUNICODE
	-D_UNICODE
	-DPOCO_STATIC
	)

add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_SOURCES}
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