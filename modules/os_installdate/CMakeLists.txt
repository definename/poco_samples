project(os_installdate)

include(PCHSupport)
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