cmake_minimum_required(VERSION 3.18)
project(c-programming-cookbook)

add_compile_options(-Wall -Werror -pedantic)

add_executable(ascii ascii.c)
add_executable(fixed_point_arith fixed_point_arith.c)
add_executable(fixed_point_mat fixed_point_mat.c)
add_executable(multiarray multiarray.c)
add_executable(multiarray_struct multiarray_struct.c)
add_executable(ndarray ndarray.c)
add_executable(pointers pointers.c)
add_executable(float16 float16.c)
add_executable(types types.c)
add_executable(malloc utils.c malloc.c)
add_executable(signal_handler signal_handler.c)
add_executable(hexbuf hexbuf.c)
add_executable(linked_list linked_list.c)
add_executable(structs structs.c)
add_executable(string string.c)

install(
  TARGETS ascii
          fixed_point_arith
          fixed_point_mat
          multiarray
          multiarray_struct
          ndarray
          pointers
          types
          malloc
          signal_handler
          float16
          hexbuf
          linked_list
          structs
          string
  DESTINATION ${CMAKE_SOURCE_DIR}/dist)
