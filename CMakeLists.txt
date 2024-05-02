cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME N_Body)
project(${PROJECT_NAME})

set(SOURCES #
    # Breakout/src/main.cpp
    Nbody/src/Core/entry_point.cpp
    Nbody/src/Core/application.cpp
    Nbody/src/Core/window.cpp
    Nbody/src/Core/log.cpp
    Nbody/src/Events/event.cpp
    Nbody/src/Events/event_dispatcher.h
    Nbody/src/Events/window_events.cpp
    Nbody/src/Events/mouse_events.cpp
    Nbody/src/Events/key_events.cpp
    # Breakout/src/Core/resources.cpp
    # Breakout/src/Renderer/renderer.cpp
    # Breakout/src/Renderer/shader.cpp
    # Breakout/src/Renderer/texture.cpp
    # Breakout/src/Renderer/vertex_array.cpp
    # Breakout/src/Renderer/vertex_buffer.cpp
    Nbody/vendor/stb/stb_image.cpp
    Nbody/src/Platform/Linux/GLFW/window_glfw.cpp
)

set(HEADERS #
    Nbody/vendor/glad/include/glad/glad.h
    Nbody/vendor/stb/stb_image.h
    Nbody/src/Core/log.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

add_subdirectory(Nbody/vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Nbody
        ${CMAKE_SOURCE_DIR}/Nbody/src/Core
        ${CMAKE_SOURCE_DIR}/Nbody/src/Renderer
        ${CMAKE_SOURCE_DIR}/Nbody/vendor/
        ${CMAKE_SOURCE_DIR}/Nbody/vendor/glm
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(Nbody/vendor/GLFW)
target_link_libraries(${PROJECT_NAME} glfw)
add_subdirectory(Nbody/vendor/spdlog)
target_link_libraries(${PROJECT_NAME} spdlog)
