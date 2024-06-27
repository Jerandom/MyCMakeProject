# CMakeList.txt : CMake project for MyCMakeTest, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.18.1)

# set the project name
set(PROJECT_NAME "MyCMakeTest")
project (${PROJECT_NAME})

###################################################### GOOGLE TEST DOWNLOAD ######################################################
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
set(gTest_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/)

# Link directories
link_directories(${LIB_PATH})
link_directories(${gTest_PATH})

# Create a variable to store library names
set(MY_LIBRARIES 
    gtest
    gtest_main
    "MyCMakeLibrary.lib")

# Define the DLL to be installed
set(MY_DLLs 
    "${gTest_PATH}gtest.dll"
    "${gTest_PATH}gtest_main.dll"
    "${LIB_PATH}/MyCMakeLibrary.dll")

# add preprocessor definitions
add_definitions(-DDLL_EXPORT)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../MyCMakeLibrary/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../MyCPlusPlusCmakeProject/inc)

###################################################### TEST SETUP START ######################################################
# Add seperate _test source
file(GLOB_RECURSE CMakeTestSources 
    "_Test/*.cpp")

# Add a test executable
add_executable(${PROJECT_NAME} ${CMakeTestSources})

# Link the test executable with GoogleTest and your main executable
target_link_libraries(${PROJECT_NAME} ${MY_LIBRARIES})

# Add tests to CTest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

###################################################### TEST SETUP END ######################################################

# install GoogleTest
install(TARGETS gtest gtest_main
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/)

# Install GoogleTest headers
install(DIRECTORY ${googletest_SOURCE_DIR}/googletest/include/gtest
    DESTINATION .)

# Install Project Targets
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

# Install specific DLL files to the same directory
install(FILES ${MY_DLLs}
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
