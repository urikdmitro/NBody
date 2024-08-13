cmake_minimum_required(VERSION 3.29)

set(PROJECT_NAME N_Body)
project(${PROJECT_NAME})

find_package(
  OpenMP
  COMPONENTS CXX
  REQUIRED)

find_package(OpenCLHeaders REQUIRED)
find_package(OpenCLICDLoader REQUIRED)
find_package(OpenCLHeadersCpp REQUIRED)

set(SOURCES #
    # Breakout/src/main.cpp
    Nbody/src/Engine/Core/entry_point.cpp
    Nbody/src/Engine/Core/application.cpp
    Nbody/src/Engine/Core/window.cpp
    Nbody/src/Engine/Core/log.cpp
    Nbody/src/Engine/Core/layer.cpp
    Nbody/src/Engine/Core/layer_stack.cpp
    Nbody/src/Engine/Core/imgui_layer.cpp
    Nbody/src/Program/draw_layer.cpp
    Nbody/src/Program/mesh.cpp
    Nbody/src/Program/sequential_simulation.cpp
    Nbody/src/Program/openmp_simulation.cpp
    Nbody/src/Program/simulation_test.cpp
    Nbody/src/Program/simulation_utils.cpp
    Nbody/src/Program/OpenCLSimulation/opencl_simulation.cpp
    # Nbody/src/Core/input.cpp
    Nbody/src/Engine/Events/event.cpp
    Nbody/src/Engine/Events/event_dispatcher.h
    Nbody/src/Engine/Events/window_events.cpp
    Nbody/src/Engine/Events/mouse_events.cpp
    Nbody/src/Engine/Events/key_events.cpp
    Nbody/src/Engine/Renderer/graphics_context.cpp
    Nbody/src/Engine/Renderer/renderer_command.cpp
    Nbody/src/Engine/Renderer/renderer_api.cpp
    Nbody/src/Engine/Renderer/renderer.cpp
    Nbody/src/Engine/Renderer/vertex_buffer.cpp
    Nbody/src/Engine/Renderer/index_buffer.cpp
    Nbody/src/Engine/Renderer/vertex_array.cpp
    Nbody/src/Engine/Renderer/texture.cpp
    Nbody/src/Engine/Renderer/shader.cpp
    Nbody/src/Engine/Renderer/camera.cpp
    Nbody/src/Engine/Renderer/camera_controller.cpp
    Nbody/vendor/stb/stb_image.cpp
    Nbody/src/Engine/Platform/Linux/GLFW/window_glfw.cpp
    Nbody/src/Engine/Platform/Linux/GLFW/input_glfw.cpp
    Nbody/src/Engine/Platform/OpenGL/imgui_impl_opengl3.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_graphics_context.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_renderer_api.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_vertex_buffer.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_vertex_array.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_index_buffer.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_texture.cpp
    Nbody/src/Engine/Platform/OpenGL/opengl_shader.cpp
    #
)

set(HEADERS #
    Nbody/vendor/glad/include/glad/glad.h
    Nbody/vendor/stb/stb_image.h
    Nbody/src/Engine/Core/log.h
    Nbody/src/Engine/Core/application.h
    Nbody/src/Engine/Core/window.h
    Nbody/src/Engine/Core/log.h
    Nbody/src/Engine/Core/layer.h
    Nbody/src/Engine/Core/layer_stack.h
    Nbody/src/Engine/Core/imgui_layer.h
    Nbody/src/Program/draw_layer.h
    Nbody/src/Program/gui_main.h
    Nbody/src/Program/mesh.h
    Nbody/src/Program/sequential_simulation.h
    Nbody/src/Program/openmp_simulation.h
    Nbody/src/Program/simulation_utils.h
    Nbody/src/Program/OpenCLSimulation/opencl_simulation.h
    Nbody/src/Engine/Events/event.h
    Nbody/src/Engine/Events/event_dispatcher.h
    Nbody/src/Engine/Events/window_events.h
    Nbody/src/Engine/Events/mouse_events.h
    Nbody/src/Engine/Events/key_events.h
    Nbody/src/Engine/Renderer/graphics_context.h
    Nbody/src/Engine/Renderer/renderer_command.h
    Nbody/src/Engine/Renderer/renderer_api.h
    Nbody/src/Engine/Renderer/renderer.h
    Nbody/src/Engine/Renderer/vertex_buffer.h
    Nbody/src/Engine/Renderer/index_buffer.h
    Nbody/src/Engine/Renderer/vertex_array.h
    Nbody/src/Engine/Renderer/texture.h
    Nbody/src/Engine/Renderer/shader.h
    Nbody/src/Engine/Renderer/camera.h
    Nbody/src/Engine/Renderer/camera_controller.h
    Nbody/src/Engine/Platform/Linux/GLFW/window_glfw.h
    Nbody/src/Engine/Platform/OpenGL/imgui_impl_opengl3.h
    Nbody/src/Engine/Platform/OpenGL/opengl_graphics_context.h
    Nbody/src/Engine/Platform/OpenGL/opengl_renderer_api.h
    Nbody/src/Engine/Platform/OpenGL/opengl_vertex_buffer.h
    Nbody/src/Engine/Platform/OpenGL/opengl_vertex_array.h
    Nbody/src/Engine/Platform/OpenGL/opengl_index_buffer.h
    Nbody/src/Engine/Platform/OpenGL/opengl_texture.h)

set(IMGUI_SRC
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/main.cpp
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3.h
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3.cpp
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_opengl3_loader.h
    # ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/vendor/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/Nbody/src/Engine/Platform/OpenGL/imgui_impl_opengl3.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${IMGUI_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
add_subdirectory(Nbody/vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)

# target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)
# target_link_libraries(${PROJECT_NAME} OpenCL::Headers)
target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)

target_link_libraries(${PROJECT_NAME} OpenCL::Headers OpenCL::OpenCL
                      OpenCL::HeadersCpp)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}/Nbody
          ${CMAKE_SOURCE_DIR}/Nbody/src/
          ${CMAKE_SOURCE_DIR}/Nbody/src/Engine
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
