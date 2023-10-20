cmake_minimum_required( VERSION 3.22.1 )

project( stb_image LANGUAGES C )

add_library( stb_image SHARED source/stb_image.c )

target_include_directories( stb_image PUBLIC include )