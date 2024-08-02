cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OKengine")

# Add source to this project's executable.
file(GLOB_RECURSE SRC__SOURCES "src/*.cpp" "src/*.c" "src/*.h")
file(GLOB_RECURSE SRC_RENDER_SOURCES "src/Render/*.cpp" "src/Render/*.h" "src/Render/*.c")
add_executable(OKengine ${SRC__SOURCES} ${SRC_RENDER__SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OKengine PROPERTY CXX_STANDARD 20)
endif()

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

# Manually specify the paths to lib
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib")

include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})

target_include_directories(OKengine PRIVATE
    ${Vulkan_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(OKengine Vulkan::Vulkan)
target_link_libraries(OKengine OpenGL::GL)
target_link_libraries(OKengine "${LIBRARY_DIR}/glfw3.lib")
target_link_libraries(OKengine "${LIBRARY_DIR}/assimp-vc143-mt.lib")

# Copy DLLs to the output directory

add_custom_command(TARGET OKengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${LIBRARY_DIR}/assimp-vc143-mt.dll"
    $<TARGET_FILE_DIR:OKengine>)
