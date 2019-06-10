# Additional modules
include(FindPackageHandleStandardArgs)

set( OGL_PACK_PATH T:/OGLPack )

# Find include files
find_path(
	GLM_INCLUDE_DIR
	NAMES glm/glm.hpp glm/vec3.hpp glm/mat4x4.hpp
	PATHS
	${OGL_PACK_PATH}/include
	DOC "The directory where glm/glm.hpp resides")


# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)