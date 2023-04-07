cmake_minimum_required(VERSION 3.20)

project(phy6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
 
add_executable(phy6
	src/main.c
	src/charge.c
	src/loader.c
	src/cJSON.c)

target_link_libraries(phy6 SDL2::Main SDL2::Image SDL2::GFX m)

target_include_directories(phy6
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
