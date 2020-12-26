
include_directories (
	${TEST_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/include
)

add_executable (general general.cpp)

set_property(TARGET general PROPERTY CXX_STANDARD 11)

add_test(NAME test1 COMMAND general)

if(GS1_ENABLE_COVERAGE)
    find_package(codecov)
    add_coverage(general)
endif()


