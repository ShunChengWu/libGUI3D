ADD_EXECUTABLE(TEST_GUI simple_window.cpp)
TARGET_LINK_LIBRARIES(TEST_GUI PUBLIC GUI)

ADD_EXECUTABLE(TEST_GUI_fixed fixed_window.cpp)
TARGET_LINK_LIBRARIES(TEST_GUI_fixed PUBLIC GUI)
