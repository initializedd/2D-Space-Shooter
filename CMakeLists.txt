cmake_minimum_required(VERSION 3.25.1)
set(CMAKE_CXX_STANDARD 20)

project(2D-Space-Shooter)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable("${PROJECT_NAME}" "${SOURCES}")

find_package(SDL2 2.26.5 REQUIRED)
find_package(SDL2_image 2.6.3 REQUIRED)
find_package(SDL2_mixer 2.6.3 REQUIRED)
find_package(SDL2_ttf 2.20.2 REQUIRED)
find_package(FlatBuffers 23.5.26 REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2main)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image-static)
target_link_libraries(${PROJECT_NAME} SDL2_mixer::SDL2_mixer-static)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf-static)
target_link_libraries(${PROJECT_NAME} flatbuffers::flatbuffers)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)