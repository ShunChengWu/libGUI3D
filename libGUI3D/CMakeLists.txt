# GUI3D #
#########
find_package(GLM REQUIRED)
FIND_PACKAGE(FreeType2 REQUIRED)
FIND_PACKAGE(Eigen3)

SET(sources
        src/GUI3D.cpp
        src/glUtils.cpp
        src/projection_control.cpp
        src/PointsRenderer.cpp
        src/ImageDrawer.cpp
        src/TrajectoryDrawer.cpp
        src/CameraDrawer.cpp
        src/meshDrawer.cpp
        src/BoxDrawer.cpp
        src/BBoxDrawer.cpp
        src/EllipsoidDrawer.cpp
        )
SET(headers
        include/GUI3D/GUI3D.h
        include/GUI3D/glShader.hpp
        include/GUI3D/glCamera.hpp
        include/GUI3D/glUtils.hpp
        include/GUI3D/PointsRenderer.h
        include/GUI3D/ImageDrawer.h
        include/GUI3D/TrajectoryDrawer.h
        include/GUI3D/CameraDrawer.h
        include/GUI3D/meshDrawer.h
        include/GUI3D/BoxDrawer.h
        include/GUI3D/BBoxDrawer.h
        include/GUI3D/EllipsoidDrawer.h
        )

ADD_LIBRARY(GUI3D ${sources} ${headers})
target_link_libraries(GUI3D
        PUBLIC GUI
        )
TARGET_INCLUDE_DIRECTORIES(GUI3D
        PUBLIC ${glm_INCLUDE_DIRS}
        PUBLIC include/GUI3D/stb
        PUBLIC ./include
        )
IF(FreeType2_FOUND)
    message("FreeType2_LIBRARIES: " ${FreeType2_LIBRARIES})
    TARGET_INCLUDE_DIRECTORIES(GUI3D PUBLIC ${FreeType2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(GUI3D PUBLIC ${FreeType2_LIBRARIES} )
    TARGET_LINK_LIBRARIES(GUI3D PUBLIC freetype)
    target_compile_definitions(GUI3D PUBLIC -DCOMPILE_WITH_FREETYPE)
ENDIF()

IF(EIGEN3_INCLUDE_DIR)
    TARGET_COMPILE_DEFINITIONS(GUI3D PUBLIC -DCOMPILE_WITH_EIGEN)
    TARGET_INCLUDE_DIRECTORIES(GUI3D PUBLIC ${EIGEN3_INCLUDE_DIR})
ENDIF()

TARGET_COMPILE_DEFINITIONS(GUI3D PUBLIC GUI_FOLDER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")