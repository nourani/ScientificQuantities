# ScientificQuantities
cmake_minimum_required(VERSION 2.8)

# project name
project(ScientificQuantities)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++11 support.")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(SQTest
	SQTest.cpp
)

add_executable(constexpr_test
    constexpr_test.cpp
)


###############################################################################
## 								Install
# Binaries and libs
install(TARGETS SQTest constexpr_test
	RUNTIME DESTINATION bin
#	LIBRARY DESTINATION lib
#	ARCHIVE DESTINATION lib
)
# Header files
install(FILES ScientificQuantities.hpp
	DESTINATION include 
)
