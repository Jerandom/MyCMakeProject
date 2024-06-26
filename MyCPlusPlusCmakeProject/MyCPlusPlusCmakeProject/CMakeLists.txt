# CMakeList.txt : CMake project for MyCPlusPlusCmakeProject, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.18.1)

# set the project name
set(PROJECT_NAME "MyCPlusPlusCmakeProject")
project(${PROJECT_NAME} VERSION 1.0.0
	LANGUAGES CXX
    DESCRIPTION "A simple C++ project")

###################################################### GOOGLE TEST START ######################################################
# Include GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip)

# Use GoogleTest
FetchContent_MakeAvailable(googletest)

# Build GoogleTest as a DLL
set(BUILD_GTEST ON CACHE BOOL "Builds the googletest library")
set(BUILD_GMOCK OFF CACHE BOOL "Do not build googlemock")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

enable_testing()

###################################################### GOOGLE TEST END ######################################################

# Define the library path
set(LIB_PATH ${CMAKE_BINARY_DIR}/MyCMakeLibrary)
set(gTest_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Link directories
link_directories(${LIB_PATH})
link_directories(${gTest_PATH})

# Create a variable to store library names
set(MY_LIBRARIES 
    "gtest.lib"
    "gtest_main.lib"
    "MyCMakeLibrary.lib")

# Define the DLL to be installed
set(MY_DLLs 
    "${gTest_PATH}/gtest.dll"
    "${gTest_PATH}/gtest_main.dll"
    "${LIB_PATH}/MyCMakeLibrary.dll")

# add preprocessor definitions
add_definitions(-DDLL_EXPORT)

# include directories
include_directories(
    ${googletest_SOURCE_DIR}/googletest/include/gtest
    ${CMAKE_SOURCE_DIR}/MyCMakeLibrary/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/)

# Add source to this project's executable using a wildcard
file(GLOB_RECURSE CMakeProjectSources 
    "inc/*.h" 
    "src/*.cpp" 
    "Main/*.cpp"
    "_Test/*.cpp")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${CMakeProjectSources})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${MY_LIBRARIES})

# Add tests to CTest
add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_test)

# Install Project Targets
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

# Install specific DLL files to the same directory
install(FILES ${MY_DLLs}
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

# Install project headers
install(DIRECTORY inc 
    DESTINATION .)

# install GoogleTest
install(TARGETS gtest gtest_main
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/)

# Install GoogleTest headers
install(DIRECTORY ${googletest_SOURCE_DIR}/googletest/include/gtest
    DESTINATION .)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()


