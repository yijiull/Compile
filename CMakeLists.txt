cmake_minimum_required( VERSION 3.10 )

set (CMAKE_CXX_STANDARD 11)
project ( by )
aux_source_directory(. DIRS)
add_executable( main ${DIRS})