set( OGL_PACK_PATH T:/OGLPack )

include(FindPackageHandleStandardArgs)

# Search for the SDL2 include directory
find_path(SDL2_INCLUDE_DIR
  NAMES SDL.h
  PATHS ${OGL_PACK_PATH}/include
  DOC "Where the SDL2 headers can be found"
)

# SDL-2.0 is the name used by FreeBSD ports...
# don't confuse it for the version number.
find_library(SDL2_LIBRARY
  NAMES SDL2
  PATHS ${OGL_PACK_PATH}/lib/x64
  DOC "Where the SDL2 Library can be found"
)

find_library(SDL2Main_LIBRARY
  NAMES SDL2main
  PATHS ${OGL_PACK_PATH}/lib/x64
  DOC "Where the SDL2 Library can be found"
)

find_library(SDL2test_LIBRARY
  NAMES SDL2test
  PATHS ${OGL_PACK_PATH}/lib/x64
  DOC "Where the SDL2 Library can be found"
)

find_library(SDL2_image_LIBRARY
  NAMES SDL2_image
  PATHS ${OGL_PACK_PATH}/lib/x64
  DOC "Where the SDL2 Library can be found"
)

set( SDL2_LIBRARY ${SDL2_LIBRARY} )

find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_INCLUDE_DIR SDL2_LIBRARY )

# Define GLM_INCLUDE_DIRS
if (SDL2_FOUND)
	set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
	set(SDL2_LIBRARIES ${SDL2_LIBRARY} )
endif()

mark_as_advanced( SDL2_INCLUDE_DIR SDL2_LIBRARY SDL2Main_LIBRARY )