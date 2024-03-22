# CMakeList.txt : CMake project for MyCMakeProject, include source and define
# project specific logic here.
#

# Add source to this project's library using a wildcard
file(GLOB_RECURSE CMakeLibrarySources "inc/*.h" "src/*.cpp")


# Add the SingletonClass.cpp file for explicit template instantiation
list(APPEND CMakeLibrarySources "${CMAKE_CURRENT_SOURCE_DIR}/src/Singleton/SingletonClass.cpp")

# Generate a definition based on Cmake File Path
set(File_Path "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inc/MainAPI/CmakeInput.h.in ${CMAKE_CURRENT_SOURCE_DIR}/inc/MainAPI/CmakeInput.h @ONLY)

# Add source to this project's library.
add_library (CMakeLibrary SHARED ${CMakeLibrarySources})

# set to c++ 20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeLibrary PROPERTY CXX_STANDARD 20)
endif()

# set the include directories so can find .h files
target_include_directories(CMakeLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")

# set the output directories for lib folder inside the library
set_target_properties(CMakeLibrary PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/")

# set the output directories for bin folder for whole project
set_target_properties(CMakeLibrary PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
