project( Logger )

file(GLOB SOURCES
	include/*.h
	source/*.cpp
)

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    GameCommon
)

add_compile_definitions( LOGGER_EXPORTS )

include_directories( ${CMAKE_SOURCE_DIR} )

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release
)