project( GameView )

file(GLOB HEADERS
	include/*.h
	include/*.hpp
)

file(GLOB SOURCES
	source/*.cpp
)

file(GLOB SHADERS
	shaders/*.vs
	shaders/*.fs
)

file(GLOB TEXTURES
	textures/*
)


add_library( ${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES} ${SHADERS} ${TEXTURES} )
source_group( "Header Files" FILES ${HEADERS} )
source_group( "Source Files" FILES ${SOURCES} )
source_group( "Shader Files" FILES ${SHADERS} )
source_group( "Texture Files" FILES ${TEXTURES} )

find_package( OpenGL REQUIRED )
find_package( GLM REQUIRED )
find_package( GLEW REQUIRED )
find_package( SDL2 REQUIRED )

message( STATUS SDL2_LIBRARIES = ${SDL2_LIBRARIES} )
message( STATUS SDL2_INCLUDE_DIR = ${SDL2_INCLUDE_DIR} )
message( STATUS GLM_LIBRARIES = ${GLM_LIBRARIES} )
message( STATUS GLEW_LIBRARIES = ${GLEW_LIBRARIES} )
message( STATUS GLM_INCLUDE_DIR = ${GLM_INCLUDE_DIR} )
message( STATUS GLEW_INCLUDE_DIR = ${GLEW_INCLUDE_DIR} )

add_compile_definitions( GAMEVIEW_EXPORTS )

include_directories(
		${GLM_INCLUDE_DIR}
		${GLEW_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}
		${SDL2_INCLUDE_DIR})

target_link_libraries( ${PROJECT_NAME} PUBLIC
		${GLM_LIBRARIES}
		${GLEW_LIBRARIES}
		${SDL2_LIBRARIES}
		GameCommon
		Logger
		)

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release
)

file( COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/bin/debug/textures )
file( COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/bin/release/textures )
file( COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/OpenglExperimentProject/textures )