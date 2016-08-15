<?xml version="1.0"?>
<bundlespec>
  <manifest>
    <name>@BUNDLE_NAME@</name>
    <symbolicName>@BUNDLE_SYMBOLIC_NAME@</symbolicName>
    <version>@BUNDLE_VERSION@</version>
    <vendor>Applied Informatics</vendor>
    <copyright>(c) 2007-2018, Applied Informatics Software Engineering GmbH</copyright>
    <activator>
      <class>@BUNDLE_ACTIVATOR_CLASS@</class>
      <library>@BUNDLE_ACTIVATOR_LIBRARY@</library>
    </activator>
    <lazyStart>false</lazyStart>
    <runLevel>@BUNDLE_RUN_LEVEL@</runLevel>
  </manifest>
  <code>
    @CMAKE_ARCHIVE_OUTPUT_DIRECTORY@/@CMAKE_CONFIGURATION_TYPES@/@BUNDLE_DLL_NAME@.dll,
    @CMAKE_ARCHIVE_OUTPUT_DIRECTORY@/@CMAKE_CONFIGURATION_TYPES@/@BUNDLE_DLL_NAME@.pdb
  </code>
</bundlespec>
