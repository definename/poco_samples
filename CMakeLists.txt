cmake_minimum_required(VERSION 3.13.1)

project(poco_samples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(BUILD_WITH_OPENSSL "Build project with openssl support" ON)
option(BUILD_WITH_POCO "Build project with poco suppport" ON)
option(BUILD_WITH_POCOpro "Build project with pocopro support" OFF)
option(BUILD_WITH_EMULATOR "Build with emulator support" OFF)

###########################################################
# Product version #########################################

set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_BUILD "0")
set(REVISION_COUNT "0")

find_package(Git)
if(GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-list HEAD --count
		OUTPUT_VARIABLE DESCRIBE_BUILD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_STRIP_TRAILING_WHITESPACE)
		string(REGEX MATCH "[0-9]+" REVISION_COUNT ${DESCRIBE_BUILD})
endif()

set(VERSION_REVISION "${REVISION_COUNT}")
set(VERSION_FILE_REVISION "${REVISION_COUNT}")

set(VERSION_COMPANY_NAME "Carrot Farm")
set(VERSION_COPYRIGHT "Copyright (C) 2018 ${VERSION_COMPANY_NAME}")

include(PCHSupport)

# Where to put all the ARCHIVE targets when built.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Where to put all the RUNTIME target files when built.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(ExternalProject)
# External directory path
set(EXTERNAL_PATH ${CMAKE_SOURCE_DIR}/external)
# Patch directory path
set(PATCH_PATH ${EXTERNAL_PATH}/patches)
# External install directory path
set(EXTERNAL_INSTALL_PATH ${CMAKE_BINARY_DIR}/external)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

###########################################################
# OpenSSL #################################################

if(BUILD_WITH_OPENSSL)
	set(OPENSSL_USE_STATIC_LIBS ON)
	set(OPENSSL_MSVC_STATIC_RT ON)

	if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
		set(OPENSSL_ROOT_DIR ${EXTERNAL_PATH}/OpenSSL/vc15-x64)
	else()
		set(OPENSSL_ROOT_DIR ${EXTERNAL_PATH}/OpenSSL/vc15-x86)
	endif()

	find_package(OpenSSL 1.0.2 EXACT REQUIRED)
endif()

###########################################################
# POCO ####################################################

if(BUILD_WITH_POCO)
	set(POCO_ROOT ${EXTERNAL_INSTALL_PATH}/Poco)
	ExternalProject_Add(
		Poco
		URL "${EXTERNAL_PATH}/poco-1.9.0-all.zip"
		URL_MD5 5def0eda47befd893722495c08b00e16
		CMAKE_ARGS
			-DENABLE_ENCODINGS:BOOL=ON
			-DENABLE_ENCODINGS_COMPILER:BOOL=OFF
			-DENABLE_XML:BOOL=ON
			-DENABLE_JSON:BOOL=ON
			-DENABLE_MONGODB:BOOL=OFF
			-DENABLE_REDIS:BOOL=ON
			-DENABLE_PDF:BOOL=OFF
			-DENABLE_UTIL:BOOL=ON
			-DENABLE_NET:BOOL=ON
			-DENABLE_NETSSL:BOOL=ON
			-DENABLE_NETSSL_WIN:BOOL=OFF
			-DENABLE_CRYPTO:BOOL=ON
			-DENABLE_DATA:BOOL=OFF
			-DENABLE_DATA_SQLITE:BOOL=OFF
			-DENABLE_DATA_MYSQL:BOOL=OFF
			-DENABLE_DATA_ODBC:BOOL=OFF
			-DENABLE_SEVENZIP:BOOL=OFF
			-DENABLE_ZIP:BOOL=OFF
			-DENABLE_APACHECONNECTOR=OFF
			-DENABLE_CPPPARSER:BOOL=OFF
			-DENABLE_POCODOC:BOOL=OFF
			-DENABLE_PAGECOMPILER:BOOL=OFF
			-DENABLE_PAGECOMPILER_FILE2PAGE:BOOL=OFF
			-DFORCE_OPENSSL:BOOL=OFF
			-DENABLE_TESTS:BOLL=OFF
			-DPOCO_STATIC:BOOL=ON
			-DPOCO_UNBUNDLED:BOOL=OFF
			-DPOCO_MT:BOOL=ON
			-DENABLE_MSVC_MP:BOOL=ON
			-DCMAKE_INSTALL_PREFIX:PATH=${POCO_ROOT}
			-DOPENSSL_ROOT_DIR:PATH=${OPENSSL_ROOT_DIR}
			-DOPENSSL_USE_STATIC_LIBS:BOOL=${OPENSSL_USE_STATIC_LIBS}
			-DOPENSSL_MSVC_STATIC_RT:BOOL=${OPENSSL_MSVC_STATIC_RT}
		PATCH_COMMAND
			${CMAKE_COMMAND} -P ${PATCH_PATH}/poco-1.9.0-all.patches/patch.cmake ${CMAKE_SOURCE_DIR}
		)

	set(Poco_INCLUDE_DIRS ${POCO_ROOT}/include)
	set(Poco_LIBRARIES
		${POCO_ROOT}/lib/PocoFoundation.lib
		${POCO_ROOT}/lib/PocoJSON.lib
		${POCO_ROOT}/lib/PocoCrypto.lib
		${POCO_ROOT}/lib/PocoNet.lib
		${POCO_ROOT}/lib/PocoUtil.lib
		${POCO_ROOT}/lib/PocoNetSSL.lib
		${POCO_ROOT}/lib/PocoXML.lib
		)
	SET_PROPERTY(TARGET Poco PROPERTY FOLDER "External")
endif()

###########################################################
# POCOpro #################################################

if(BUILD_WITH_POCOpro)
	set(POCO_ROOT $ENV{POCO_ROOT})

	if (NOT EXISTS ${POCO_ROOT})
		message(FATAL_ERROR "POCO_ROOT (Remoting) path is not specified. Please install POCOpro and add env var POCO_ROOT")
	endif()

	set(Poco_BINARIES ${POCO_ROOT}/bin)
	set(Poco_BUNDLE_CREATOR ${Poco_BINARIES}/bundle)
	set(Poco_REMOTE_GEN_TOOL RemoteGenNG)

	if (WIN32)
		set(Poco_REMOTE_GEN_COMPILER msvc)
	else()
		set(Poco_REMOTE_GEN_COMPILER gcc)
	endif()

	set(Poco_INCLUDE_DIRS ${POCO_ROOT}/include)

	# POCOpro libraries with static runtime
	set(PocoFoundation_LIB
		debug ${POCO_ROOT}/lib/PocoFoundationmtd.lib
		optimized ${POCO_ROOT}/lib/PocoFoundationmt.lib
		)
	set(PocoXML_LIB
		debug ${POCO_ROOT}/lib/PocoXMLmtd.lib
		optimized ${POCO_ROOT}/lib/PocoXMLmt.lib
		)
	set(PocoNet_LIB
		debug ${POCO_ROOT}/lib/PocoNetmtd.lib
		optimized ${POCO_ROOT}/lib/PocoNetmt.lib
		)
	set(PocoUtil_LIB
		debug ${POCO_ROOT}/lib/PocoUtilmtd.lib
		optimized ${POCO_ROOT}/lib/PocoUtilmt.lib
		)
	set(PocoRemotingNG_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGmtd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNGmt.lib
		)
	set(PocoRemotingNGTCP_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGTCPmtd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNGTCPmt.lib
		)
	set(PocoRemotingNGSOAP_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGSOAPmtd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNGSOAPmt.lib
		)
	set(PocoJSON_LIB
		debug ${POCO_ROOT}/lib/PocoJSONmtd.lib
		optimized ${POCO_ROOT}/lib/PocoJSONmt.lib
		)
	set(PocoLicensing_LIB
		debug ${POCO_ROOT}/lib/PocoLicensingmtd.lib
		optimized ${POCO_ROOT}/lib/PocoLicensingmt.lib
		)
	set(PocoOSP_LIB
		debug ${POCO_ROOT}/lib/PocoOSPd.lib
		optimized ${POCO_ROOT}/lib/PocoOSP.lib
		)
	set(Poco_LIBRARIES
		${PocoFoundation_LIB}
		${PocoXML_LIB}
		${PocoNet_LIB}
		${PocoUtil_LIB}
		${PocoRemotingNG_LIB}
		${PocoRemotingNGTCP_LIB}
		${PocoRemotingNGSOAP_LIB}
		${PocoJSON_LIB}
		${PocoLicensing_LIB}
		${PocoOSP_LIB}
		)

	# POCOpro libraries with dynamic runtime
	set(PocoFoundation_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoFoundationd.lib
		optimized ${POCO_ROOT}/lib/PocoFoundation.lib
		)
	set(PocoXML_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoXMLd.lib
		optimized ${POCO_ROOT}/lib/PocoXML.lib
		)
	set(PocoNet_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoNetd.lib
		optimized ${POCO_ROOT}/lib/PocoNet.lib
		)
	set(PocoUtil_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoUtild.lib
		optimized ${POCO_ROOT}/lib/PocoUtil.lib
		)
	set(PocoRemotingNG_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNG.lib
		)
	set(PocoRemotingNGTCP_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGTCPd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNGTCP.lib
		)
	set(PocoRemotingNGSOAP_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoRemotingNGSOAPd.lib
		optimized ${POCO_ROOT}/lib/PocoRemotingNGSOAP.lib
		)
	set(PocoJSON_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoJSONd.lib
		optimized ${POCO_ROOT}/lib/PocoJSON.lib
		)
	set(PocoLicensing_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoLicensingd.lib
		optimized ${POCO_ROOT}/lib/PocoLicensing.lib
		)
	set(PocoOSP_SHARED_LIB
		debug ${POCO_ROOT}/lib/PocoOSPd.lib
		optimized ${POCO_ROOT}/lib/PocoOSP.lib
		)
	set(Poco_SHARED_LIBRARIES
		${PocoFoundation_SHARED_LIB}
		${PocoXML_SHARED_LIB}
		${PocoNet_SHARED_LIB}
		${PocoUtil_SHARED_LIB}
		${PocoRemotingNG_SHARED_LIB}
		${PocoRemotingNGTCP_SHARED_LIB}
		${PocoRemotingNGSOAP_SHARED_LIB}
		${PocoJSON_SHARED_LIB}
		${PocoLicensing_SHARED_LIB}
		${PocoOSP_SHARED_LIB}
		)

	add_subdirectory(modules/_remoting)
	add_subdirectory(modules/_osp)
endif()

###########################################################
# libpocoemulator #########################################

if (BUILD_WITH_EMULATOR)
	set(libpocoemulator_LIBRARIES libpocoemulator)
	set(libpocoemulator_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/modules/_libpocoemulator/libpocoemulator/include)
	add_subdirectory(modules/_libpocoemulator)
endif()

add_subdirectory(modules/_thread)
# add_subdirectory(modules/_json)
# add_subdirectory(modules/_qt)

# add_subdirectory(modules/timer)
add_subdirectory(modules/nobsod)
add_subdirectory(modules/notification-center)
# add_subdirectory(modules/optional)
# add_subdirectory(modules/basic_event)
# add_subdirectory(modules/memory_managment)
# add_subdirectory(modules/code_signing)
# add_subdirectory(modules/converter)
# add_subdirectory(modules/ftp_client)
# add_subdirectory(modules/host_entry)
# add_subdirectory(modules/http_stream_factory)
# add_subdirectory(modules/https_server)
# add_subdirectory(modules/networkinterface)
# add_subdirectory(modules/os_installdate)
# add_subdirectory(modules/registry)
# add_subdirectory(modules/random)
# add_subdirectory(modules/dell_warranty_request)
# add_subdirectory(modules/null-server)
# add_subdirectory(modules/os-info)
# add_subdirectory(modules/datetime)
