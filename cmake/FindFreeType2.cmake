#
# Try to find FreeType2 library and include path.
# Once done this will define
#
# FreeType2_FOUND
# FreeType2_INCLUDE_DIRS
# FreeType2_LIBRARIES
#

SET(NAME FreeType2)
SET(URL "https://github.com/aseprite/freetype2.git")
SET(${NAME}_INSTALL_DIR  ${CMAKE_BINARY_DIR}/external/${NAME})
#SET(${NAME}_FOUND 0)
IF(NOT ${NAME}_FOUND)
  find_package(Git)
  IF(EXISTS ${${NAME}_INSTALL_DIR})
    file(REMOVE_RECURSE ${${NAME}_INSTALL_DIR})
  ENDIF()
  file(MAKE_DIRECTORY ${${NAME}_INSTALL_DIR})


  SET(WORK_DIR ${CMAKE_BINARY_DIR}/external)
  MESSAGE(STATUS "clone ${NAME} from ${URL} to ${WORK_DIR}")
  execute_process(
          COMMAND ${GIT_EXECUTABLE} clone ${URL} ${NAME}
          WORKING_DIRECTORY ${WORK_DIR}
  )

  IF(EXISTS ${${NAME}_INSTALL_DIR}/build)
    file(REMOVE_RECURSE ${${NAME}_INSTALL_DIR}/build)
  ENDIF()
  file(MAKE_DIRECTORY ${${NAME}_INSTALL_DIR}/build)

  SET(WORK_DIR ${CMAKE_BINARY_DIR}/build)
  MESSAGE(STATUS "build ${NAME} on ${WORK_DIR}")
  execute_process(
          COMMAND cmake -DCMAKE_INSTALL_PREFIX=${${NAME}_INSTALL_DIR}/bin ..
          WORKING_DIRECTORY ${${NAME}_INSTALL_DIR}/build
  )
  MESSAGE(STATUS "install ${NAME}")
  execute_process(
          COMMAND make install
          WORKING_DIRECTORY ${${NAME}_INSTALL_DIR}/build
  )

  SET(${NAME}_FOUND 1 CACHE STRING " ")
  #SET(${NAME}_INCLUDE_DIR ${${NAME}_INSTALL_DIR}/build/include CACHE STRING " ")
ENDIF()

FIND_PACKAGE(freetype REQUIRED
        PATHS
        ${${NAME}_INSTALL_DIR}/bin/lib/cmake
        ${${NAME}_INSTALL_DIR}/bin/lib/cmake/freetype
        NO_DEFAULT_PATH
)

if(FreeType2_FOUND)
  message(STATUS "Found FreeType2: ${FreeType2_INCLUDE_DIR}")
else(FreeType2_FOUND)
  if (NOT FreeType2_FIND_QUIETLY)
    message(FATAL_ERROR "could NOT find FreeType2")
  endif (NOT FreeType2_FIND_QUIETLY)
endif(FreeType2_FOUND)