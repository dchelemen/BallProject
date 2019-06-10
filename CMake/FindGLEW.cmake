
# Additional modules
include(FindPackageHandleStandardArgs)

# Dependencies
# GLEW depends on OpenGL
find_package( OpenGL REQUIRED )

set( OGL_PACK_PATH T:/OGLPack )

find_package(OpenGL)

# Find include files
find_path(
	GLEW_INCLUDE_DIR
	NAMES GL/glew.h
	PATHS
	${OGL_PACK_PATH}/include
	DOC "The directory where GL/glew.h resides")

# Use glew32s.lib for static library
# Define additional compiler definitions
if (GLEW_USE_STATIC_LIBS)
	set(GLEW_LIBRARY_NAME glew32s)
	set(GLEW_DEFINITIONS -DGLEW_STATIC)
else()
	set(GLEW_LIBRARY_NAME glew32)
endif()

# Find library files
find_library(
	GLEW_LIBRARY
	NAMES ${GLEW_LIBRARY_NAME}
	PATHS
	${OGL_PACK_PATH}/lib/x64
	DOC "The GLEW library")

unset(GLEW_LIBRARY_NAME)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_DIR GLEW_LIBRARY)

# Define GLEW_LIBRARIES and GLEW_INCLUDE_DIRS
if (GLEW_FOUND)
	set(GLEW_LIBRARIES ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)
