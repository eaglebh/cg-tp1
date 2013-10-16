cmake_minimum_required(VERSION 2.8)
project(tp1)

find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} shader.vert shader.frag)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} X11 Xxf86vm Xrandr pthread Xi)
