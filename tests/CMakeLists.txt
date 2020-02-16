
include_directories (
	${TEST_SOURCE_DIR}
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/cmake-codecov/cmake" ${CMAKE_MODULE_PATH})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable (general general.cpp)

set_property(TARGET general PROPERTY CXX_STANDARD 11)

add_test(test1 ${CMAKE_CURRENT_BINARY_DIR}/bin/general)

if(METRIC_ENABLE_COVERAGE)
    find_package(codecov)
    add_coverage(general)
endif()


