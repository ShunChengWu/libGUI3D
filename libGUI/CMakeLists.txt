# GUI #
#######
INCLUDE(../cmake/UseImGUI.cmake)

SET(sources
        ../../cmake-build-debug/external/gl3w-install/src/gl3w.c
        GUI.cpp
        )
SET(headers
        GUI.h
        )

ADD_LIBRARY(GUI ${sources} ${headers})
target_link_libraries(GUI PUBLIC imgui)



OPTION(BUILD_TEST_GUI "Build a test programe on GUI" False)
IF(BUILD_TEST_GUI)
    ADD_SUBDIRECTORY(TEST)
ENDIF()
