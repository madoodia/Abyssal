# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

set(SOURCES
    main.cpp
    oglWindow.cpp
    shader.cpp
    stb_image.cpp
)

add_executable($ENV{TARGET_NAME} ${SOURCES})

# Qt5
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
target_link_libraries($ENV{TARGET_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries($ENV{TARGET_NAME} ${OPENGL_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED) # if you install GLEW on linux
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries($ENV{TARGET_NAME} ${GLEW_LIBRARIES})

# STB_IMAGE
include_directories($ENV{STB_LOCATION})

# GLM
include_directories($ENV{GLM_LOCATION})
