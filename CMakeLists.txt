#/*============================================================================
#
#  MyProject: A software package for whatever.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

######################################################################
# Set the minimum CMake version.
######################################################################
set(MYPROJECT_CMAKE_MINIMUM_REQUIRED_VERSION 3.7)
cmake_minimum_required(VERSION ${MYPROJECT_CMAKE_MINIMUM_REQUIRED_VERSION})


##################################################################################
# Set some CMake Policies.
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
##################################################################################
set(project_policies )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

project(MyProject VERSION 00.00.1)

######################################################################
# Setting supported build types. Should ONLY be Release or Debug.
######################################################################
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Valid options are Release or Debug" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug")
endif()

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "Debug"))
  message(FATAL_ERROR "Build type \"${CMAKE_BUILD_TYPE}\" is not supported.")
endif()

if(WIN32)
  # Restrict the generated configuration to be what we configured above.
  # No point creating project files for build types that will not compile.
  # Note: it's set to FORCE so that both CMAKE_BUILD_TYPE and CMAKE_CONFIGURATION_TYPES match up.
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "Build configurations to generate." FORCE)
  mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()


######################################################################
# Setup the path to load CMake macros, and extra CMake files.
######################################################################
set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/CMake
    ${CMAKE_BINARY_DIR}
    ${CMAKE_MODULE_PATH}
   )

######################################################################
# Choose C++ standard
######################################################################
set(MYPROJECT_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS 0)
set(CMAKE_CXX_STANDARD ${MYPROJECT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED 1)

######################################################################
# Build options.
######################################################################
option(BUILD_TESTING "Build Unit tests." ON)
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
if(WIN32 AND NOT BUILD_SHARED_LIBS)
  add_definitions(-DMYPROJECT_STATIC)
endif()

######################################################################
# Configure Dart testing support.  This should be done before any
# message(FATAL_ERROR ...) commands are invoked.
######################################################################
include(${CMAKE_ROOT}/Modules/Dart.cmake)
mark_as_advanced(TCL_TCLSH DART_ROOT)
enable_testing()

if(BUILD_TESTING)
  set(BUILDNAME "MyProject" CACHE STRING "Name of build on the dashboard")
  mark_as_advanced(BUILDNAME)

  # Setup file for setting custom ctest vars
  configure_file(CMake/CTestCustom.cmake.in ${CMAKE_BINARY_DIR}/CTestCustom.cmake @ONLY)

  # Setup continuous test script
  configure_file(CMake/CTestContinuous.cmake.in ${CMAKE_BINARY_DIR}/CTestContinuous.cmake @ONLY)

endif(BUILD_TESTING)


######################################################################
# Add Mandatory Requirements
######################################################################
set(ALL_THIRD_PARTY_LIBRARIES)

# Eigen Package for Linear Algebra

find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIR})
add_definitions(-DBUILD_Eigen)

# Boost Libraries

# set(Boost_DEBUG ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_NO_BOOST_CMAKE ON)

if(BUILD_SHARED_LIBS)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_STATIC_RUNTIME OFF)
else()
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_STATIC_RUNTIME ON) 
endif()

find_package(Boost 1.63 EXACT COMPONENTS filesystem system date_time regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(WIN32 AND BUILD_SHARED)
  list(APPEND ALL_COMPILE_OPTIONS -DBOOST_ALL_DYN_LINK)
endif()

list(APPEND ALL_THIRD_PARTY_LIBRARIES ${Boost_LIBRARIES})
add_definitions(-DBUILD_Boost)
set(ADDITIONAL_SEARCH_PATHS "${BOOST_ROOT}/bin;${ADDITIONAL_SEARCH_PATHS}")

# e.g. for OpenCV
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})
# list(APPEND ALL_THIRD_PARTY_LIBRARIES ${OpenCV_LIBS})


######################################################################
# Add Optional Requirements
######################################################################
set(ALL_LIBRARIES myproject ${ALL_THIRD_PARTY_LIBRARIES})
# e.g. for ITK
# find_package(ITK REQUIRED)


######################################################################
# Copy some reference files to output.
######################################################################
configure_file(${CMAKE_SOURCE_DIR}/Documentation/License.dox ${CMAKE_BINARY_DIR}/Doxygen/License.dox)
configure_file(${CMAKE_SOURCE_DIR}/LICENSE.txt ${CMAKE_BINARY_DIR}/LICENSE.txt @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/Documentation/Licenses/Eigen.txt ${CMAKE_BINARY_DIR}/LICENSE_Eigen.txt)
configure_file(${CMAKE_SOURCE_DIR}/Documentation/Licenses/Boost.txt ${CMAKE_BINARY_DIR}/LICENSE_Boost.txt)
configure_file(${CMAKE_SOURCE_DIR}/README.md ${CMAKE_BINARY_DIR}/README.md @ONLY)

######################################################################

# Copy data test files to output

######################################################################
configure_file(${CMAKE_SOURCE_DIR}/Testing/Data/file_input_test.txt ${CMAKE_BINARY_DIR}/Testing/Data/file_input_test.txt)

######################################################################
# Provide support for manually running Doxygen in build folder.
######################################################################
configure_file(${CMAKE_SOURCE_DIR}/Utilities/Doxygen/myprojectdoxygen.pl.in ${CMAKE_BINARY_DIR}/myprojectdoxygen.pl)
configure_file(${CMAKE_SOURCE_DIR}/Utilities/Doxygen/doxygen.config.in ${CMAKE_BINARY_DIR}/doxygen.config)


######################################################################
# MyProject uses KWStyle for checking the coding style
######################################################################
include(${CMAKE_SOURCE_DIR}/Utilities/KWStyle/MyProjectKWStyle.cmake)


######################################################################
# MyProject uses CppCheck for static analysis
######################################################################
include(${CMAKE_SOURCE_DIR}/Utilities/CppCheck/MyProjectCppCheck.cmake)


######################################################################
# Add code folders.
######################################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Code/)
add_subdirectory(Code)
add_subdirectory(Documentation)
if(BUILD_TESTING)
  set(TEMP_DIR ${CMAKE_BINARY_DIR}/Testing/Temporary)
  include_directories(${CMAKE_SOURCE_DIR}/Testing/)
  add_subdirectory(Testing)
endif()
