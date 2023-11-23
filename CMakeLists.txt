cmake_minimum_required(VERSION 3.25.1)
set(CMAKE_CXX_STANDARD 20)

project(2D-Space-Shooter)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable("${PROJECT_NAME}" "${SOURCES}")

find_package(SDL3 3.0.0 REQUIRED)
find_package(SDL3_image 3.0.0 REQUIRED)
find_package(SDL3_mixer 3.0.0 REQUIRED)
find_package(SDL3_ttf 3.0.0 REQUIRED)
find_package(FlatBuffers 23.5.26 REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} SDL3_mixer::SDL3_mixer)
target_link_libraries(${PROJECT_NAME} SDL3_ttf::SDL3_ttf)
target_link_libraries(${PROJECT_NAME} flatbuffers::flatbuffers)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
