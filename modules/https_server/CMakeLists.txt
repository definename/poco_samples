cmake_minimum_required(VERSION 3.10.0)

project("https_server")

set(HTTPS_SERVER_SOURCES
	src/HandlerFactory.cpp
	src/HTTPSServer.cpp
	src/RedirectHandlerFactory.cpp
	src/RedirectRequestHandler.cpp
	src/RequestHandler.cpp
	src/main.cpp
	)
set(HTTPS_SERVER_HEADES
	include/HandlerFactory.h
	include/HTTPSServer.h
	include/RedirectHandlerFactory.h
	include/RedirectRequestHandler.h
	include/RequestHandler.h
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
	${HTTPS_SERVER_SOURCES}
	${HTTPS_SERVER_HEADES}
	${MISC}
	)
	
add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(
	include
	${POCO_INCLUDE_DIRS}
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

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)