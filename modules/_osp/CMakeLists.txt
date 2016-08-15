set(PROPERTY_FOLDER "_osp")
set(BUNDLE_DESTINATION_DIR bundles)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CustomBundleContainer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/com.my.CustomBundleProvider)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/com.my.CustomBundleConsumer)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/RemotingClientContainer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/RemotingServerContainer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/com.my.RemotingClientBundle)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/com.my.RemotingServerBundle)