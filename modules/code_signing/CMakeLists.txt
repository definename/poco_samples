project(code_signing)

include(CRTLinkage)

set(PROJECT_HEADES
	)

set(PROJECT_SOURCES
	src/main.cpp
	)

set(MISC
	src/pch.h
	src/pch.cpp
	)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("" FILES ${MISC})

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADES}
	${MISC}
	)

include_directories(
	include
	${Poco_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	${Poco_LIBRARIES}
	crypt32.lib
	Ws2_32.lib
	Iphlpapi.lib
	)

add_dependencies(${PROJECT_NAME}
	Poco
	)

add_definitions(
	-DWIN32_LEAN_AND_MEAN
	-D_CRT_SECURE_NO_WARNINGS
	-DUNICODE
	-D_UNICODE
	)

add_precompiled_headers(${PROJECT_NAME} "src/")