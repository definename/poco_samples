project(libpocoemulator)

include(CRTLinkage)

set(PROJECT_HEADERS
	)
set(PROJECT_RESOURCES
	)
set(PROJECT_SOURCES
	)
set(HTTP_HEADERS
	include/libpocoemulator/Http/Http.hpp
	include/libpocoemulator/Http/HttpClient.h
	include/libpocoemulator/Http/HttpSession.h
	include/libpocoemulator/Http/HttpsSession.h
	include/libpocoemulator/Http/HttpTypes.h
	)
set(HTTP_SOURCES
	src/Http/HttpClient.cpp
	src/Http/HttpSession.cpp
	src/Http/HttpsSession.cpp
	)
set(MISC
	src/pch.h
	src/pch.cpp
	src/targetver.h
	)

add_library(${PROJECT_NAME} STATIC
	${PROJECT_HEADERS}
	${HTTP_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${HTTP_SOURCES}
	${MISC}
	)

source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Header Files\\Http" FILES ${HTTP_HEADERS})
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Source Files\\Http" FILES ${HTTP_SOURCES})
source_group("" FILES ${MISC})

include_directories(
	include
	${Poco_INCLUDE_DIRS}
	${OPENSSL_INCLUDE_DIR}
	)
# target_link_libraries(${PROJECT_NAME}
	# )
add_dependencies(${PROJECT_NAME}
	Poco
	)
add_definitions(
	-DUNICODE
	-D_UNICODE
	-DWIN32_LEAN_AND_MEAN
	)

add_precompiled_headers(${PROJECT_NAME} "src/")
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "_libpocoemulator")
# set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)