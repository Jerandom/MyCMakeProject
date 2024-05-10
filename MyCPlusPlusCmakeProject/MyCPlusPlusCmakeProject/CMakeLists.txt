# CMakeList.txt : CMake project for MyCPlusPlusCmakeProject, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.18.1)

# set the project name
set(PROJECT_NAME "MyCPlusPlusCmakeProject")
project(${PROJECT_NAME} VERSION 1.0.0
	LANGUAGES CXX
    DESCRIPTION "A simple C++ project")

# Enable CTest
enable_testing()

# Define the library path
set(LIB_PATH ${CMAKE_SOURCE_DIR}/MyCMakeLibrary/lib/${CMAKE_BUILD_TYPE}/)

# Link directories
link_directories(${LIB_PATH})

# Create a variable to store library names
set(MY_LIBRARIES 
    "MyCMakeLibrary.lib")

# Define the DLL to be installed
set(MY_DLLs 
    "${LIB_PATH}/MyCMakeLibrary.dll")

# warning level 4
add_compile_options(/W4)

# add preprocessor definitions
add_definitions(-DDLL_EXPORT)

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)

# Add source to this project's executable using a wildcard
file(GLOB_RECURSE CMakeProjectSources 
    "inc/*.h" 
    "src/*.cpp" 
    "Main/*.cpp")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${CMakeProjectSources})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${MY_LIBRARIES})

# Add tests
file(GLOB_RECURSE TestSources 
    "MyCPlusPlusCmakeProject.cpp")

# Create a test executable
add_executable(MyTests ${TestSources})

# Register tests with CTest
add_test(NAME TestSuite COMMAND MyTests)

# Install compiled targets
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

# Install specific DLL files to the same directory
install(FILES ${MY_DLLs}
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/)

install(DIRECTORY inc DESTINATION .)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()


