cmake_minimum_required(VERSION 3.13)
project(libGUI3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function" )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#################################
# Specify the CMake module path #
#################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

############
# External #
############
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseCxxTools.cmake)

######################
# Add subdirectories #
######################
ADD_SUBDIRECTORY(libGUI)
ADD_SUBDIRECTORY(libGUI3D)

