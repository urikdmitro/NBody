cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME N_Body)
project(${PROJECT_NAME})

set(SOURCES #
    # Breakout/src/main.cpp
    Nbody/src/Core/entry_point.cpp
    Nbody/src/Core/application.cpp
    Nbody/src/Core/window.cpp
    Nbody/src/Core/log.cpp
    Nbody/src/Core/layer.cpp
    Nbody/src/Core/layer_stack.cpp
    Nbody/src/Events/event.cpp
    Nbody/src/Events/event_dispatcher.h
    Nbody/src/Events/window_events.cpp
    Nbody/src/Events/mouse_events.cpp
    Nbody/src/Events/key_events.cpp
    # Breakout/src/Core/resources.cpp Breakout/src/Renderer/renderer.cpp
    # Breakout/src/Renderer/shader.cpp Breakout/src/Renderer/texture.cpp
    # Breakout/src/Renderer/vertex_array.cpp
    # Breakout/src/Renderer/vertex_buffer.cpp
    Nbody/vendor/stb/stb_image.cpp
    Nbody/src/Platform/Linux/GLFW/window_glfw.cpp)

set(HEADERS #
    Nbody/vendor/glad/include/glad/glad.h Nbody/vendor/stb/stb_image.h
    Nbody/src/Core/log.h)

set(IMGUI_SRC
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/main.cpp
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3.h
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3.cpp
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3_loader.h
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_glfw.h
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_demo.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${IMGUI_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
add_subdirectory(Nbody/vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/Nbody
          ${CMAKE_SOURCE_DIR}/Nbody/src/Core
          ${CMAKE_SOURCE_DIR}/Nbody/src/Renderer
          ${CMAKE_SOURCE_DIR}/Nbody/vendor/
          ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui
          ${CMAKE_SOURCE_DIR}/Nbody/vendor/glm)

set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL
    OFF
    CACHE BOOL "GLFW lib only")

add_subdirectory(Nbody/vendor/GLFW)
target_link_libraries(${PROJECT_NAME} glfw)
add_subdirectory(Nbody/vendor/spdlog)
target_link_libraries(${PROJECT_NAME} spdlog)

# find_package(imgui REQUIRED)

# add_subdirectory(Nbody/vendor/imgui) target_link_libraries(${PROJECT_NAME}
# imgui)
