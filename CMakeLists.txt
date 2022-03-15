# ScientificQuantities
cmake_minimum_required(VERSION 2.8)

# project name
project(ScientificQuantities)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++11 support.")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR} )

set(SQ_VERSION_MAJOR 0)
set(SQ_VERSION_MINOR 1)
set(SQ_VERSION_PATCH 0)
set(SQ_VERSION ${SQ_VERSION_MAJOR}.${SQ_VERSION_MINOR}.${SQ_VERSION_PATCH})

# Should tests be compiled or not
# By default this is on, unless we are in Release mode
set(ENABLE_TESTING "ON" CACHE BOOL "Turns on unit testing")

include_directories(include)

# Used for unit tests
if(${ENABLE_TESTING})
  add_executable(test_all
	  test/test.cpp
  )

  add_executable(test_constexpr
      test/test_constexpr.cpp
  )
endif()

###############################################################################
#               Packaging
#SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX})
SET(CPACK_DEBIAN_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}_${ADASLOC_VERSION}-${BUILD_NUMBER}_amd64")
SET(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Navid Nourani-Vatani <Navid@Nourani.dk>")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A template based C++11 class for definition and conversion of scientific quantities.")
SET(CPACK_PACKAGE_DESCRIPTION "A template based C++11 class for definition and conversion of scientific quantities.

The base class is based on SI unit. From these we derive the Derived SI units. All the BASE and DERIVED using are implemented.")
SET(CPACK_PACKAGE_VERSION ${SQ_VERSION})
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_MODULE_PATH}/LICENSE.txt")
SET(CPACK_SYSTEM_NAME "${BUILD_SYSTEM_NAME}")
SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
INCLUDE(CPack)

###############################################################################
## 								Install
# Binaries and libs
#install(
#  TARGETS test_all test_constexpr
#  ARCHIVE DESTINATION lib
#  LIBRARY DESTINATION lib
#  INCLUDES DESTINATION include
#  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
#	      GROUP_EXECUTE GROUP_READ
#	      WORLD_EXECUTE WORLD_READ
#)

# Header files
install(
  DIRECTORY "include/"
  DESTINATION include/${CMAKE_PROJECT_NAME}
  PATTERN "*.hpp"
)

