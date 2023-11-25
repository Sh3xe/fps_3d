cmake_minimum_required( VERSION 3.21.2 )
 
project( glad LANGUAGES C )

add_library( glad STATIC source/glad.c )

target_include_directories( glad PUBLIC include )