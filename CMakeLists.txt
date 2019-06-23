cmake_minimum_required( VERSION 3.13 )
project( OpenGLProject )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

add_subdirectory( GameCommon )
add_subdirectory( Logger )
add_subdirectory( GameView )
add_subdirectory( OpenglExperimentProject )
