cmake_minimum_required( VERSION 3.21.2 )

project( stb_image LANGUAGES C )

add_library( stb_image STATIC source/stb_image.c )

target_include_directories( stb_image PUBLIC include )