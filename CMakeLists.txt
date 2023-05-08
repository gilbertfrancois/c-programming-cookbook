cmake_minimum_required(VERSION 3.25)
project(sudoku)

add_compile_options(-Wall -Werror) 

add_executable(ascii ascii.c)
add_executable(multiarray multiarray.c)
add_executable(multiarray_struct multiarray_struct.c)
add_executable(pointers pointers.c)
add_executable(types types.c)
