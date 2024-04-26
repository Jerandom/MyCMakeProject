# CMakeList.txt : CMake project for MyCMakeProject, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.18.1)

# set the project name
set(PROJECT_NAME "MyCMakeLibrary")
project (${PROJECT_NAME})

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("BUILD_TARGET: ${PLATFORM}")

# warning level 4
add_compile_options(/W4)

# Generate a definition based on Cmake File Path
set(File_Path "${CMAKE_SOURCE_DIR}/MyCPlusPlusCmakeProject/bin/output/")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/inc/MainAPI/CmakeInput.h.in ${CMAKE_CURRENT_SOURCE_DIR}/inc/MainAPI/CmakeInput.h @ONLY)

# add preprocessor definitions
add_definitions(-DDLL_EXPORT)

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)

# Add source to this project's library using a wildcard
file(GLOB_RECURSE CMakeLibrarySources 
    "inc/*.h" 
    "src/*.cpp" 
    "UnitTest/*.cpp")

# add the library
add_library (${PROJECT_NAME} SHARED ${CMakeLibrarySources})

#add_executable (${PROJECT_NAME}_test
#    "UnitTest/MyCmakeLibTest.cpp"
#    "UnitTest/MyCmakeLibTest.h")


#target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})

# Install compiled targets
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/)


install(DIRECTORY inc DESTINATION .)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()