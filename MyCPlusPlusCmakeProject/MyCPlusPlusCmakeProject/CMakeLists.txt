# CMakeList.txt : CMake project for MyCPlusPlusCmakeProject, include source and define
# project specific logic here.
#

# Add source to this project's executable using a wildcard
file(GLOB MyCMakeProjectSources "inc/*.h" "src/*.cpp" "Main/*.cpp")

# Add source to this project's executable.
add_executable (MyCMakeProject ${MyCMakeProjectSources} "inc/CMakeClass.h" "src/CMakeClass.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MyCMakeProject PROPERTY CXX_STANDARD 20)
endif()

# set the include directories so can find .h files
target_include_directories(MyCMakeProject PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/" 
												 "${CMAKE_SOURCE_DIR}/MyCMakeLibrary/inc/")

target_link_libraries(MyCMakeProject PRIVATE "${CMAKE_SOURCE_DIR}/MyCMakeLibrary/lib/CMakeLibrary.lib")

# set the output directories
set_target_properties(MyCMakeProject PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
