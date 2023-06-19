cmake_minimum_required(VERSION 3.18)
project(c-programming-cookbook)

add_compile_options(-Wall -Werror) 

add_executable(ascii ascii.c)
add_executable(multiarray multiarray.c)
add_executable(multiarray_struct multiarray_struct.c)
add_executable(ndarray ndarray.c)
add_executable(pointers pointers.c)
add_executable(types types.c)
add_executable(malloc utils.c malloc.c)
add_executable(rotating_cube rotating_cube.c)
add_executable(cube cube.c)
