cmake_minimum_required(VERSION 3.10)


if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()


project("GS1"
	VERSION 0.0.1)


# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES Catch2/2.6.0@catchorg/stable
                BASIC_SETUP)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)


option(GS1_ENABLE_COVERAGE "Generate coverage for codecov.io" OFF)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})


add_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(tests)
enable_testing ()
# add_test (NAME TestAll COMMAND tests/010-TestCase)

target_include_directories(
	${PROJECT_NAME}
	INTERFACE	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(GS1_ENABLE_COVERAGE)
    find_package(codecov)
endif()




add_definitions("-std=c++11")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
# target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)


install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)


configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/CMake/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION
	${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


install(
	EXPORT ${PROJECT_NAME}_Targets
	FILE ${PROJECT_NAME}Targets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


install(
	FILES	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)


install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION include)


if(GS1_ENABLE_COVERAGE)
    coverage_evaluate()
endif()


