cmake_minimum_required(VERSION 3.23)
project(TP_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP_3 main.c)

file(COPY "graphe.txt" DESTINATION ${CMAKE_BINARY_DIR})