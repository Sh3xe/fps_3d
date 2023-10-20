cmake_minimum_required( VERSION 3.22.1 )
 
project( glad LANGUAGES C )

add_library( glad SHARED source/glad.c )

target_include_directories( glad PUBLIC include )